
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
            numOfFeatures = 0;
            // Extract each column feature
            while(std::getline(ss, feature, ',')){

                // Initialize and add <feature, float> pairs to the table map
                table.insert({feature, std::vector<float> {}});
                features.push_back(feature);
                numOfFeatures++;
            }
        }
        numOfRecords = 0;
        // Read data, line by line
        while(std::getline(myFile, line))
        {
            numOfRecords++;
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
    /**
     * destructor
     */
    ~TimeSeries() {

    }
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
