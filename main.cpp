
#include <iostream>
#include "anomaly_detection_util.h"
#include "map"
#include "vector"
#include "string"
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
using namespace std;

bool wrong(float val, float expected){
    return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
    TimeSeries ts("C:\\Users\\Daniel Karl\\Desktop\\test.csv");
//    vector<float> ttt = ts.getOneFeatureData("b");
//    vector<string> featNames=ts.getNameFeatures();
//    float vals[ts.getNumOfFeatures()][ts.getNumOfRows()];
//    for(int i=0;i<featNames.size();i++) {
//        for (size_t j = 0; j < ts.getNumOfFeatures(); j++) {
//            vals[i][j] = ts.getOneFeatureData(featNames[i])[j];
//        }
//    }
//    int numOfFeatures = ts.getNumOfFeatures();
//    int numOfRecords = ts.getNumOfRecords();
//    vector<string> featNames=ts.getNameFeatures();
//    float vals[numOfFeatures][numOfRecords];
//    for(int i=0;i<numOfFeatures;i++) {
//        for (int j = 0; j < numOfRecords; j++) {
//            vals[i][j] = ts.getFeatureDateAtTime(featNames[i], j + 1);
//        }
//    }
//    for (int i = 0; i < numOfFeatures; ++i) {
//        float maxPerson = 0;
//        float currentPearson;
//        int correlateIndex = -1;
//        for (int j = i+1; j < numOfFeatures ; ++j) {
//            currentPearson = abs(pearson(vals[i], vals[j], numOfRecords));
//            if (currentPearson > maxPerson) {
//                maxPerson = currentPearson;
//                correlateIndex = j;
//            }
//        }
//        if (correlateIndex != -1) {
//            correlatedFeatures newCorelated;
//            newCorelated.corrlation = maxPerson;
//            newCorelated.feature1 = featNames[i];
//            newCorelated.feature2 = featNames[correlateIndex];
//            //newCorelated.lin_reg = Line()
//
//        }
//    }
    //float y = pearson(vals[0], vals[1],ts.getNumOfRows());
//    correlatedFeatures x;
//    x.corrlation = 5;

    SimpleAnomalyDetector sh;
    sh.learnNormal(ts);
    //float x = ts.getFeatureDateInTime("b", 1);
    int num1 = ts.getNumOfFeatures();
    //int num2 = ts.getNumOfRows();
    return 0;
}
