
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

    vector<string> featNames=ts.getFeatures();
    float vals[ts.getNumOfFeatures()][ts.getNumOfRows()];
    for(int i=0;i<featNames.size();i++) {
        for (int j = 0; j < ts.getNumOfFeatures(); j++) {
            vals[i][j] = ts.getFeatureData(featNames[i])[j];
        }
    }

}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

