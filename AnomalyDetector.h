/*
 * Author: 318324563 - Daniel Meir Karl
 */

#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include "timeseries.h"
#include "math.h"
using namespace std;


class AnomalyReport{
public:
	const string description;
	const long timeStep;
	AnomalyReport(string description, long timeStep):description(description),timeStep(timeStep){}
};
/**
 * interface for TimeSeries Anomaly Detector.
 * By using the interface we save the open/closed principle for other implementations for Anomaly Detectors.
 * the interface methods of learn normal - offline learning of the TimeSeries and online detection of Anomaly.
 */
class TimeSeriesAnomalyDetector {
public:
	virtual void learnNormal(const TimeSeries& ts)=0;
	virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
	virtual ~TimeSeriesAnomalyDetector(){}
};

#endif /* ANOMALYDETECTOR_H_ */
