/*
 *
 * Author: 318324563 - Daniel Meir Karl
 */
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // define the minimum threshold of which the features to be correlative.
    thresholdLearn = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    int numOfFeatures = ts.getNumOfFeatures();
    int numOfRecords = ts.getNumOfRecords();
    vector<string> featNames=ts.getNameFeatures();
    // create an array from the TimeSeries table.
    float vals[numOfFeatures][numOfRecords];
    for(int i=0;i<numOfFeatures;i++) {
        for (int j = 0; j < numOfRecords; j++) {
            vals[i][j] = ts.getFeatureDateAtTime(featNames[i], j + 1);
        }
    }
    //check every feature in compare with the rest to find the max correlated feature with him.
    for (int i = 0; i < numOfFeatures; ++i) {
        float maxPearson = 0;
        float currentPearson;
        int correlateIndex = -1;
        for (int j = i+1; j < numOfFeatures ; ++j) {
            currentPearson = abs(pearson(vals[i], vals[j], numOfRecords));
            if (currentPearson > maxPearson) {
                maxPearson = currentPearson;
                correlateIndex = j;
            }
        }
        // check if any correlated feature found and if the max Person that found is sufficient high or not
        if (correlateIndex != -1 && maxPearson > thresholdLearn) {
            // generate a new correlatedFeatures and save the data.
            correlatedFeatures newCorelated;
            newCorelated.corrlation = maxPearson;
            newCorelated.feature1 = featNames[i];
            newCorelated.feature2 = featNames[correlateIndex];
            // create an array of points of the correlated features.
            Point** arrayPts = arrayPointsGenerator(ts.getOneFeatureData(featNames[i]),
                                               ts.getOneFeatureData(featNames[correlateIndex]));
            Line l = linear_reg(arrayPts,numOfRecords);
            newCorelated.lin_reg = l;
            // multiply the threshold by 1.1 to avoid marginal values.
            newCorelated.threshold = getThreshold(arrayPts,numOfRecords,l) * 1.1 ;
            deletePointsArray(arrayPts, numOfRecords);
            cf.push_back(newCorelated);
        }
    }
}

/**
 * detect - Online exception detection function.
 * @param ts - Features database.
 * @return - vector<AnomalyReport> - Vector of exception reports
 */
vector <AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> AR;
    int numOfRecords = ts.getNumOfRecords();
    vector<string> featNames = ts.getNameFeatures();
    // Loop running on the records in the database
    for (int i = 0; i < numOfRecords; ++i) {
        // Loop running on the correlative features
        for (int j = 0; j < cf.size(); ++j) {
            // Initialize a correlation point
            float x = ts.getOneFeatureData(cf.at(j).feature1).at(i);
            float y = ts.getOneFeatureData(cf.at(j).feature2).at(i);
            Point *p = new Point(x, y);
            Point np = *p;
            float distance = dev(np, cf.at(j).lin_reg);
            if (distance > cf.at(j).threshold) {
                // Initialize an anomaly report
                string description = cf.at(j).feature1 + "-" + cf.at(j).feature2;
                long timeStep = i + 1;
                AnomalyReport anomalyReport(description, timeStep);
                AR.push_back(anomalyReport);
            }
            delete p;
        }
    }
    return AR;
}
/**
 * @param pointsArr the get the thershold
 * @param size of the array
 * @param rl is the line
 * @return the maximum distance of a certain point from the line which called the threshold.
 */
float SimpleAnomalyDetector::getThreshold(Point **pointsArr, int size, Line rl) {
    float max = 0;
    for(int i = 0; i < size; i++){
        float distance = abs(pointsArr[i]->y - rl.f(pointsArr[i]->x));
        if(distance > max)
            max = distance;
    }
    return max;
}