
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

class TimeSeries{

public:
    map<string, vector<float>> map;
	TimeSeries(const char* CSVfileName) {
        ifstream myFile(CSVfileName);
        myFile.good()


    }

};



#endif /* TIMESERIES_H_ */
