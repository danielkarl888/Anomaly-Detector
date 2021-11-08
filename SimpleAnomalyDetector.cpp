
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
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
    float maxPearson = 0;
//    for (int i = 0; i < ; ++i) {
//
//    }


}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

