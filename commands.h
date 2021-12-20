#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
    void readFile(string fileName){
        ofstream out(fileName);
        string str="";
        while((str=read())!="done"){
            out<<str<<endl;
        }
        out.close();
    }


    // you may add additional methods here
};

// you may add here helper classes
/**
 * union consecutive reports into one report.
 * the struct has its start time and his end time and if the report is considered true-positive or not.
 */
struct unionReport{
    string description;
    int startTimeStep;
    int endTimeStep;
    bool tp;
};
/**
 * the global state is the state of the anomaly detector within all the commands.
 * it has the threshold setting of features to be correlatives,
 * anomaly reports and union reports.
 */
struct globalState{
    float threshold;
    vector<AnomalyReport> singleReports;
    vector<unionReport> unionReports;
    int trainRecordsSize;
    globalState(){
        threshold=0.9;
        trainRecordsSize=0;
    }
};
// you may edit this class
class Command{
protected:
	DefaultIO* dio;
public:
    const string description;
    Command(DefaultIO* dio,const string description):dio(dio),description(description){}
	virtual void execute(globalState* sharedState)=0;
	virtual ~Command(){}
};
/**
 * class that represents the command of uploading csv file to the server
 */
class UploadFileCSV:public Command{
public:
    UploadFileCSV(DefaultIO* dio):Command(dio,"upload a time series csv file"){}
    virtual void execute(globalState* sharedState){
        dio->write("Please upload your local train CSV file.\n");
        dio->readFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};
class ThresholdSettings:public Command{
public:
    ThresholdSettings(DefaultIO* dio):Command(dio,"algorithm settings"){}
    virtual void execute(globalState* sharedState){
        float newThreshold;
        bool flag = true;
        while(flag) {
            dio->write("The current correlation threshold is ");
            dio->write(sharedState->threshold);
            dio->write("\nType a new threshold\n");
            dio->read(&newThreshold);
            if(newThreshold > 0 && newThreshold <= 1) {
                sharedState-> threshold =newThreshold;
                flag = false;
            } else {
                dio->write("please choose a value between 0 and 1.\n");
            }
        }
    }
};
class Detect:public Command{
public:
    Detect(DefaultIO* dio):Command(dio,"detect anomalies"){}
    virtual void execute(globalState* globalState) {
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        globalState->trainRecordsSize = test.getNumOfRecords();
        HybridAnomalyDetector ad;
        ad.setCorrelationThreshold(globalState->threshold);
        ad.learnNormal(train);
        globalState-> singleReports = ad.detect(test);
        unionReport ur;
        ur.startTimeStep = 0;
        ur.endTimeStep = 0;
        ur.description = "";
        ur.tp = false;
        for_each(globalState->singleReports.begin(),globalState->singleReports.end(),
                 [&ur,globalState](AnomalyReport& report){
                    // check if the current report is comes right after the last report
                     if(report.timeStep == ur.endTimeStep+1 && report.description == ur.description)
                         ur.endTimeStep++;
                     else {
                         // create a new union report
                         ur.startTimeStep=report.timeStep;
                         ur.endTimeStep=ur.startTimeStep;
                         ur.description=report.description;
                         globalState->unionReports.push_back(ur);
                     }
                 });
        globalState -> unionReports.push_back(ur);
        globalState -> unionReports.erase(globalState->unionReports.begin());
        dio->write("anomaly detection complete.\n");
    }
};



// implement here your command classes



#endif /* COMMANDS_H_ */
