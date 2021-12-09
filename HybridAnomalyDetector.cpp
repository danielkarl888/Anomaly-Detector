//
// Created by Daniel Karl on 09/12/2021.
//
#include <HybridAnomalyDetector.h>
#include <minCircle.h>
void
HybridAnomalyDetector::setCorelated(const TimeSeries &ts, float pearson, string feat1, string feat2, Point **ptsArr) {
    SimpleAnomalyDetector::setCorelated(ts,pearson, feat1, feat2,ptsArr);
    if (pearson > 0.5 && pearson < thresholdLearn) {
        correlatedFeatures newCorelated;
        Circle circle = findMinCircle(ptsArr, ts.getNumOfRecords());
        newCorelated.circle = circle;
        newCorelated.corrlation = pearson;
        newCorelated.feature1 = feat1;
        newCorelated.feature2 = feat2;
        cf.push_back(newCorelated);
    }
}

