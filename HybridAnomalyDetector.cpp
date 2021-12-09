
#include <HybridAnomalyDetector.h>
#include <minCircle.h>
HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}
void
HybridAnomalyDetector::setCorelated(const TimeSeries &ts, float pearson, string feat1, string feat2, Point **ptsArr) {
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
        cf.push_back(newCorelated);
    }
}