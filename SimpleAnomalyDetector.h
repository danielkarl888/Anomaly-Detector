

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

/**
 * SimpleAnomalyDetector class implements interface TimeSeriesAnomalyDetector
 */
class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    vector<correlatedFeatures> cf;
    float thresholdLearn;
public:
    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);
    void setCorrelationThreshold(float threshold){
        this -> thresholdLearn = threshold;
    }
    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    correlatedFeatures getCorreatedFeaturs(string featName) {
        correlatedFeatures correlatedFeatures;
        for (int i = 0; i < cf.size(); ++i) {
            if (featName.compare(cf.data()->feature1) || featName.compare(cf.data()->feature2) ) {
                correlatedFeatures = cf.data()[i];
                return correlatedFeatures;
            }
        }
    }

protected:
    Point** arrayPointsGenerator(vector<float> x, vector<float> y) {
        Point** pointsArr=new Point*[x.size()];
        for (int i = 0; i < x.size(); ++i) {
            pointsArr[i] = new Point(x[i], y[i]);
        }
        return pointsArr;
	}
    float getThreshold(Point **pointsArr, int size, Line rl);

//    long timeStep(int recordIndex, const TimeSeries &ts);
};




#endif /* SIMPLEANOMALYDETECTOR_H_ */
