
#include <iostream>
#include "anomaly_detection_util.h"
#include "map"
#include "vector"
#include "string"
#include "timeseries.h"
using namespace std;

bool wrong(float val, float expected){
    return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
    TimeSeries ts("C:\\Users\\Daniel Karl\\Desktop\\test.csv");
    vector<float> ttt = ts.getFeatureData("b");
    vector<string> featNames=ts.getNameFeatures();
    float vals[ts.getNumOfFeatures()][ts.getNumOfRows()];
    for(size_t i=0;i<featNames.size();i++) {
        for (size_t j = 0; j < ts.getNumOfFeatures(); j++) {
            vals[i][j] = ts.getFeatureData(featNames[i])[j];
        }
    }
    float y = pearson(vals[0], vals[1],ts.getNumOfRows());


    //float x = ts.getFeatureDateInTime("b", 1);
    int num1 = ts.getNumOfFeatures();
    int num2 = ts.getNumOfRows();
    return 0;
}
