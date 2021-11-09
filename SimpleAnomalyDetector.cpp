
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // define the minimum threshold of which the features to be correlative.
    threshold = 0.9;
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
    for (int i = 0; i < numOfFeatures; ++i) {
        float maxPerson = 0;
        float currentPearson;
        int correlateIndex = -1;
        for (int j = i+1; j < numOfFeatures ; ++j) {
            currentPearson = abs(pearson(vals[i], vals[j], numOfRecords));
            if (currentPearson > maxPerson) {
                maxPerson = currentPearson;
                correlateIndex = j;
            }
        }
        if (correlateIndex != -1 && maxPerson > threshold) {
            correlatedFeatures newCorelated;
            newCorelated.corrlation = maxPerson;
            newCorelated.feature1 = featNames[i];
            newCorelated.feature2 = featNames[correlateIndex];
            // create an array of points of the correlated features.
            Point** arrayPts = arrayPointsGenerator(ts.getOneFeatureData(featNames[i]),
                                               ts.getOneFeatureData(featNames[correlateIndex]));
            Line l = linear_reg(arrayPts,numOfRecords);
            newCorelated.lin_reg = l;
            // multiply the threshold by 1.1 to avoid marginal values.
            newCorelated.threshold = getThreshold(arrayPts,numOfRecords,l) * 1.1 ;
            cf.push_back(newCorelated);
        }
    }



}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

float SimpleAnomalyDetector::getThreshold(Point **pointsArr, int size, Line rl) {
    float max = 0;
    for(int i = 0; i < size; i++){
        float distance = abs(pointsArr[i]->y - rl.f(pointsArr[i]->x));
        if(distance > max)
            max = distance;
    }
    return max;
}


