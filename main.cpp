
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
    return 0;
}
