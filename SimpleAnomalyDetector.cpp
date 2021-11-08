
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
            Point** arr = arrayPointsGenerator(ts.getOneFeatureData(featNames[i]),
                                               ts.getOneFeatureData(featNames[correlateIndex]));
            newCorelated.lin_reg = linear_reg(arr,numOfRecords);
            newCorelated.threshold =
            cf.push_back(newCorelated);
        }
    }



}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

