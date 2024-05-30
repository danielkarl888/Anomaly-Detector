
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

    SimpleAnomalyDetector sh;
    sh.learnNormal(ts);
    sh.detect(TimeSeries("C:\\Users\\Daniel Karl\\Desktop\\maintest.csv"));
    //float x = ts.getFeatureDateInTime("b", 1);
    int num1 = ts.getNumOfFeatures();
    //int num2 = ts.getNumOfRows();
    return 0;
}
