/*
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
        // if the current feature has no correlated feature - continue to the next feature to check
        if (correlateIndex == -1)
        {
            continue;
        }
        Point** arrayPts = arrayPointsGenerator(ts.getOneFeatureData(featNames[i]),
                                                ts.getOneFeatureData(featNames[correlateIndex]));
        string featName1 = featNames[i];
        string featName2 = featNames[correlateIndex];
        setCorelated(ts, maxPearson, featName1,featName2, arrayPts);
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
            float distance;
            // the distance is either between the point and the line or
            // the center point of the min circle and the point
            if (cf.at(j).regFeatures){
                distance = dev(np, cf.at(j).lin_reg);
            } else {
                distance = sqrt(pow((x-cf.at(j).xCenter),2) + pow((y-cf.at(j).yCenter), 2));
            }
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
 * @param pointsArr the get the threshold
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
/**
 * helper method to learnNormal that set the correlated features to the cf vector
 * @param ts is the table of the offline mode
 * @param pearson of the current correlated features
 * @param feat1 name
 * @param feat2 name
 * @param ptsArr of the features
 */
void
SimpleAnomalyDetector::setCorelated(const TimeSeries &ts, float pearson, string feat1, string feat2, Point **ptsArr) {
    if (pearson > thresholdLearn) {
        correlatedFeatures newCorelated;
        newCorelated.regFeatures = true;
        newCorelated.corrlation = pearson;
        newCorelated.feature1 = feat1;
        newCorelated.feature2 = feat2;
        int numOfRecords = ts.getNumOfRecords();
        Line l = linear_reg(ptsArr,numOfRecords);
        newCorelated.lin_reg = l;
        // multiply the threshold by 1.1 to avoid marginal values.
        newCorelated.threshold = getThreshold(ptsArr,numOfRecords,l) * 1.1 ;
        deletePointsArray(ptsArr, numOfRecords);
        cf.push_back(newCorelated);
    }
}