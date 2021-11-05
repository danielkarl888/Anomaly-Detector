
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <string>
using namespace std;

class TimeSeries{

public:
    map<string, vector<float>> table;
	TimeSeries(const char* CSVfileName) {
        ifstream myFile(CSVfileName);
        if(!myFile.is_open()) throw std::runtime_error("Could not open file");
        string line, feature;
        int val;
        if(myFile.good())
        {
            // Extract the first line in the file
            std::getline(myFile, line);

            // Create a stringstream from line
            std::stringstream ss(line);

            // Extract each column name
            while(std::getline(ss, feature, ',')){

                // Initialize and add <feature, float> pairs to the table map
                table.push_back({feature, std::vector<float> {}});
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

                // Add the current float to the 'colIdx' column's values vector
                table.at(colIdx).second.push_back(val);

                // If the next token is a comma, ignore it and move on
                if(ss.peek() == ',') ss.ignore();

                // Increment the column index
                colIdx++;
            }
        }



    }

};



#endif /* TIMESERIES_H_ */
