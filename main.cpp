
#include <iostream>
#include "anomaly_detection_util.h"
#include "map"
#include "vector"
#include "string"
using namespace std;

bool wrong(float val, float expected){
    return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
    map<string, vector<float>> a;
    vector<float> b;
    b.push_back(1.2);
    b.push_back(2.3);
    vector<float> c;
    c.push_back(8.2);
    c.push_back(9.3);
    a.insert({"a", b});
    a.insert({"b", c});
    return 0;
}
