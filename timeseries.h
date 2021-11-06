
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <stdexcept>
using namespace std;

class TimeSeries{

public:
    map<string, vector<float>> table;
    vector<string> features;
    int sizeRow;
	TimeSeries(const char* CSVfileName) {
        ifstream myFile(CSVfileName);
        if(!myFile.is_open()) throw std::runtime_error("Could not open file");
        string line, feature;
        float val;
        if(myFile.good())
        {
            // Extract the first line in the file
            std::getline(myFile, line);

            // Create a stringstream from line
            std::stringstream ss(line);
            sizeRow = 0;
            // Extract each column feature
            while(std::getline(ss, feature, ',')){

                // Initialize and add <feature, float> pairs to the table map
                table.insert({feature, std::vector<float> {}});
                features.push_back(feature);
                sizeRow++;
            }
        }
        // Read data, line by line
        while(std::getline(myFile, line))
        {
            // Create a stringstream of the current line
            std::stringstream ss(line);

            // Keep track of the current column index
            int colIdx = 0;
            // Extract each float
            while(ss >> val){
                table[features[colIdx]].push_back(val);

                // If the next token is a comma, ignore it and move on
                if(ss.peek() == ',') ss.ignore();

                // Increment the column index
                colIdx++;
            }
        }
        myFile.close();
    }
    ~TimeSeries() {

    }
    size_t getSizeRow()const {
        return sizeRow;
    }
    const vector<string>& getFeatures()const {
        return features;
    }
    const vector<float>& getFeatureData(string name)const{
        return table.at(name);
    }

};



#endif /* TIMESERIES_H_ */
