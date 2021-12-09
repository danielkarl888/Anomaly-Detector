/*
 * Author: 318324563 - Daniel Meir Karl
 */
#include "HybridAnomalyDetector.h"
HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}
/**
 * setCorelated overrides the method from SimpleAnomalyDetector
 * we set coreelated feature with the minCircle if the pearson is less the the threshold and graeter than 0.5
 * @param ts is the timeSeries
 * @param pearson of the two faetures
 * @param feat1 is the name of the 1st feature
 * @param feat2 is the name of the 2nd feature
 * @param ptsArr is an array of points
 */
void
HybridAnomalyDetector::setCorelated(const TimeSeries &ts, float pearson, string feat1, string feat2, Point **ptsArr) {
    // check if we have to set the correlated feature according to the regression line
    SimpleAnomalyDetector::setCorelated(ts,pearson, feat1, feat2,ptsArr);
    if (pearson > 0.5 && pearson < thresholdLearn) {
        correlatedFeatures newCorelated;
        Circle circle = findMinCircle(ptsArr, ts.getNumOfRecords());
        newCorelated.corrlation = pearson;
        newCorelated.feature1 = feat1;
        newCorelated.feature2 = feat2;
        newCorelated.threshold = circle.radius * 1.1;
        newCorelated.regFeatures = false;
        newCorelated.xCenter = circle.center.x;
        newCorelated.yCenter = circle.center.y;
        deletePointsArray(ptsArr, ts.getNumOfRecords());
        cf.push_back(newCorelated);
    }
}