/*
 * Author: 318324563 - Daniel Meir Karl
 */
#ifndef PROJECT_KARL_LANDAU5_HYBRIDANOMALYDETECTOR_H
#define PROJECT_KARL_LANDAU5_HYBRIDANOMALYDETECTOR_H
#include "SimpleAnomalyDetector.h"
#include "minCircle.h"
class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    virtual void setCorelated(const TimeSeries& ts,float pearson,string feat1, string feat2,Point** ptsArr);
};
#endif //PROJECT_KARL_LANDAU5_HYBRIDANOMALYDETECTOR_H
