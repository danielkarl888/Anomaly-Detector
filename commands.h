/*
 * Author: 318324563 - Daniel Meir Karl
 */
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    void readFile(string fileName) {
        ofstream out(fileName);
        string str = "";
        while ((str = read()) != "done") {
            out << str << endl;
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
struct unionReport {
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
struct globalState {
    float threshold;
    vector <AnomalyReport> singleReports;
    vector <unionReport> unionReports;
    int testRecordsSize;

    globalState() {
        threshold = 0.9;
        testRecordsSize = 0;
    }
};

// you may edit this class
class Command {
protected:
    DefaultIO *dio;
public:
    const string description;

    Command(DefaultIO *dio, const string description) : dio(dio), description(description) {}

    virtual void execute(globalState *globalState) = 0;

    virtual ~Command() {}
};

class PrintMenu : public Command {
public:
    PrintMenu(DefaultIO *dio) : Command(dio, "Print the menu") {}

    virtual void execute(globalState *globalState) {
        dio->write("Welcome to the Anomaly Detection Server.\n"
                   "Please choose an option:\n"
                   "1.upload a time series csv file\n"
                   "2.algorithm settings\n"
                   "3.detect anomalies\n"
                   "4.display results\n"
                   "5.upload anomalies and analyze results\n"
                   "6.exit\n");
    }
};

/**
 * class that represents the command of uploading csv file to the server
 */
class UploadFileCSV : public Command {
public:
    UploadFileCSV(DefaultIO *dio) : Command(dio, "upload a time series csv file") {}

    virtual void execute(globalState *sharedState) {
        dio->write("Please upload your local train CSV file.\n");
        dio->readFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};

class ThresholdSettings : public Command {
public:
    ThresholdSettings(DefaultIO *dio) : Command(dio, "algorithm settings") {}

    virtual void execute(globalState *globalState) {
        float newThreshold;
        bool flag = true;
        while (flag) {
            dio->write("The current correlation threshold is ");
            dio->write(globalState->threshold);
            dio->write("\nType a new threshold\n");
            dio->read(&newThreshold);
            if (newThreshold > 0 && newThreshold <= 1) {
                globalState->threshold = newThreshold;
                flag = false;
            } else {
                dio->write("please choose a value between 0 and 1.\n");
            }
        }
    }
};

class Detect : public Command {
public:
    Detect(DefaultIO *dio) : Command(dio, "detect anomalies") {}

    virtual void execute(globalState *globalState) {
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        globalState->testRecordsSize = test.getNumOfRecords();
        HybridAnomalyDetector ad;
        ad.setCorrelationThreshold(globalState->threshold);
        ad.learnNormal(train);
        globalState->singleReports = ad.detect(test);
        unionReport ur;
        ur.startTimeStep = 0;
        ur.endTimeStep = 0;
        ur.description = "";
        ur.tp = false;
        for_each(globalState->singleReports.begin(), globalState->singleReports.end(),
                 [&ur, globalState](AnomalyReport &report) {
                     // check if the current report comes right after the last report
                     if (report.timeStep == ur.endTimeStep + 1 && report.description == ur.description) {
                         ur.endTimeStep++;
                     } else {
                         //push the last union report to the globalState
                         globalState->unionReports.push_back(ur);
                         // create a new union report
                         ur.description = report.description;
                         ur.startTimeStep = report.timeStep;
                         ur.endTimeStep = ur.startTimeStep;
                     }
                 });
        globalState->unionReports.push_back(ur);
        // remove the 1st union report from the vector
        globalState->unionReports.erase(globalState->unionReports.begin());
        dio->write("anomaly detection complete.\n");
    }
};

class PrintAnomalies : public Command {
public:
    PrintAnomalies(DefaultIO *dio) : Command(dio, "display results") {}

    virtual void execute(globalState *globalState) {
        for_each(globalState->singleReports.begin(), globalState->singleReports.end(), [this](AnomalyReport &report) {
            dio->write(report.timeStep);
            dio->write("\t " + report.description + "\n");
        });
        dio->write("Done.\n");
    }
};

class AnalyzeAnomalies : public Command {
public:
    AnalyzeAnomalies(DefaultIO *dio) : Command(dio, "upload anomalies and analyze results") {}

    // return true if and only if the section B intersects section A
    // it is a helper method in order to check if the sequance of anomaly reports intersects the anomaly file.
    bool isIntersect(int startA, int endA, int startB, int endB) {
        return (endA >= startB && endB >= startA);
    }

    /**
     * check if an union report is true-positive or not according to start and end of the anomaly file.
     * union report is true positive if it intersects with one of the reports in the anomaly file.
     * @param globalState of the CLI
     * @param start time of the anomaly report of the anomaly file.
     * @param end time of the anomaly report of the anomaly file
     * @return true if the current union report is true-positive
     */
    bool checkTP(globalState *globalState, int start, int end) {
        for (int i = 0; i < globalState->unionReports.size(); ++i) {
            unionReport ur = globalState->unionReports[i];
            if (isIntersect(start, end, ur.startTimeStep, ur.endTimeStep)) {
                globalState->unionReports[i].tp = true;
                return true;
            }
        }
        return false;
    }

    virtual void execute(globalState *globalState) {
        string str = "";
        int counterTP = 0, sum=0;
        int counterP = 0;
        float N = globalState->testRecordsSize;
        for (int i = 0; i < globalState->unionReports.size(); i++) {
            globalState->unionReports[i].tp = false;
        }
        dio->write("Please upload your local anomalies file.\n");
        while ((str = dio->read()) != "done") {
            int i = 0;
            for (; str[i] != ','; i++) {}
            string startStr = str.substr(0, i);
            string endStr = str.substr(i + 1, str.length());
            int startTimeReport = stoi(startStr);
            int endTimeReport = stoi(endStr);
            if (checkTP(globalState, startTimeReport, endTimeReport)) {
                counterTP++;
            }
            counterP++;
            sum += (endTimeReport - startTimeReport + 1);
        }
        dio->write("Upload complete.\n");
        float counterFP = 0;
        for (int j = 0; j < globalState->unionReports.size(); j++)
            if (!globalState->unionReports[j].tp) {
                counterFP++;
            }
        N -= sum;
        float TPRate = ((int) (1000.0 * counterTP / counterP)) / 1000.0f;
        float FPRate = ((int) (1000.0 * counterFP / N)) / 1000.0f;
        dio->write("True Positive Rate: ");
        dio->write(TPRate);
        dio->write("\nFalse Positive Rate: ");
        dio->write(FPRate);
        dio->write("\n");
    }
};

class Exit : public Command {
public:
    Exit(DefaultIO *dio) : Command(dio, "exit") {}

    virtual void execute(globalState *globalState) {

    }
};


#endif /* COMMANDS_H_ */
