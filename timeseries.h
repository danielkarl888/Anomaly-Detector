/*
 * Author: 318324563 - Daniel Meir Karl
 */
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <string.h>
#include <sstream>
#include <utility>
#include <stdexcept>
using namespace std;

class TimeSeries{
    map<string, vector<float>> table;
    vector<string> features;
    int numOfFeatures;
    int numOfRecords;
public:
    /**
     * constructor.
     * @param CSVfileName with features and values
     * the constructor creates a map when the key is the feature and the value for each key is a vector of the
     * values in which every feature has.
     */
    TimeSeries(const char* CSVfileName) {
        numOfRecords = 0;
        numOfFeatures = 0;
        ifstream myFile(CSVfileName);
        if(!myFile.is_open()) throw runtime_error("Could not open file");
        string line, feature;
        float val;
        if(myFile.good())
        {
            // get first line in the file
            getline(myFile, line);

            // Create a string stream from the line
            stringstream ss(line);
            // get each column feature
            while(getline(ss, feature, ',')){

                // Initialize and add <feature, float> pairs to the table map
                table.insert({feature, std::vector<float> {}});
                features.push_back(feature);
                numOfFeatures++;
            }
        }
        // Read data, line by line
        while(!myFile.eof())
        {

            string line;
            string val;
            myFile>>line;
            stringstream lss(line);
            int i=0;
            while(getline(lss,val,',')){
                table[features[i]].push_back(stof(val));
                i++;

            }
            // count number of row records in the table.
            // Create a string stream of the current line
        }
        myFile.close();
        numOfRecords = table[features[0]].size();
    }
    /**
     * destructor
     */
    ~TimeSeries() {}
    /**
     * @return the number of features the Timeseries has.
     */
    int getNumOfFeatures()const {
        return this->numOfFeatures;
    }
    /**
     *
     * @return the number of rows in the table of the TimeSeries
     */
    int getNumOfRecords()const {
        return this->numOfRecords;
    }
    /**
     * @return a vector of names in the TimeSeries.
     */
    const vector<string>& getNameFeatures()const {
        return features;
    }
    /**
     * get a vector of values for a certain feature.
     * @param name of the feature
     * @return a vector of values for the named feature
     */
    const vector<float>& getOneFeatureData(string name)const{
        return table.at(name);
    }
    /**
     * get a value for a feature in certain time in the TimeSeries.
     * @param name of feature
     * @param time of the value
     * @return value from the feature in certain time in the table.
     */
    float getFeatureDateAtTime(const string name, int time) const {
        return table.at(name).at(time - 1);
	}
	/**
	 * @return the table of which the timeseries is stored.
	 */
	const map<string, vector<float>>& getTable() const {
        return this->table;
    }

};

#endif /* TIMESERIES_H_ */
