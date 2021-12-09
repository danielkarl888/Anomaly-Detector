/*
 *
 * Author: 318324563 - Daniel Meir Karl
 */
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
/**
 * struct which represents 2 correlated features with their names, corrlation,
 * line and max threshold between them.
 */
struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
	float corrlation;          // pearson between the features
	Line lin_reg;
	float threshold;
    bool regFeatures;
    float xCenter;
    float yCenter;
};

/**
 * SimpleAnomalyDetector class implements interface TimeSeriesAnomalyDetector
 * The interface has methods of learning a normal data TimeSeries which the correlated features
 * will be generated based on them.
 */
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
	vector<correlatedFeatures> cf;
    float thresholdLearn;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    void setCorrelationThreshold(float threshold){
        this -> thresholdLearn = threshold;
    }
	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

protected:
    Point** arrayPointsGenerator(vector<float> x, vector<float> y) {
        Point** pointsArr=new Point*[x.size()];
        for (int i = 0; i < x.size(); ++i) {
            pointsArr[i] = new Point(x[i], y[i]);
        }
        return pointsArr;
	}
    void deletePointsArray (Point** arrayPoints, int size) {
        for(int i=0;i<size;i++)
            delete arrayPoints[i];
        delete[] arrayPoints;
    }
    float getThreshold(Point **pointsArr, int size, Line rl);
    virtual void setCorelated(const TimeSeries& ts,float pearson,string feat1, string feat2,Point** ptsArr);

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
