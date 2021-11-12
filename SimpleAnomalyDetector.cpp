
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // define the minimum threshold of which the features to be correlative.
    thresholdLearn = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    int numOfFeatures = ts.getNumOfFeatures();
    int numOfRecords = ts.getNumOfRecords();
    vector<string> featNames = ts.getNameFeatures();
    // create an array from the TimeSeries table.
    float vals[numOfFeatures][numOfRecords];
    for (int i = 0; i < numOfFeatures; i++) {
        for (int j = 0; j < numOfRecords; j++) {
            vals[i][j] = ts.getFeatureDateAtTime(featNames[i], j + 1);
        }
    }
    for (int i = 0; i < numOfFeatures; ++i) {
        float maxPearson = 0;
        float currentPearson;
        int correlateIndex = -1;
        for (int j = i + 1; j < numOfFeatures; ++j) {
            currentPearson = abs(pearson(vals[i], vals[j], numOfRecords));
            if (currentPearson > maxPearson) {
                maxPearson = currentPearson;
                correlateIndex = j;
            }
        }
        if (correlateIndex != -1 && maxPearson > thresholdLearn) {
            correlatedFeatures newCorelated;
            newCorelated.corrlation = maxPearson;
            newCorelated.feature1 = featNames[i];
            newCorelated.feature2 = featNames[correlateIndex];
            // create an array of points of the correlated features.
            Point **arrayPts = arrayPointsGenerator(ts.getOneFeatureData(featNames[i]),
                                                    ts.getOneFeatureData(featNames[correlateIndex]));
            Line l = linear_reg(arrayPts, numOfRecords);
            newCorelated.lin_reg = l;
            // multiply the threshold by 1.1 to avoid marginal values.
            newCorelated.threshold = getThreshold(arrayPts, numOfRecords, l) * 1.1;
            cf.push_back(newCorelated);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> AR;
    int numOfFeatures = ts.getNumOfFeatures();
    int numOfRecords = ts.getNumOfRecords();
    vector<string> featNames = ts.getNameFeatures();
    for (int i = 0; i < numOfRecords; ++i) {
        for (int j = 0; j < cf.size(); ++j) {
            float x = ts.getOneFeatureData(cf.at(j).feature1).at(i);
            float y = ts.getOneFeatureData(cf.at(j).feature2).at(i);
            Point *p = new Point(x, y);
            Point np = *p;
            float distance = dev(np, cf.at(j).lin_reg);
            if (distance > cf.at(j).threshold) {
                string description = cf.at(j).feature1 + "-" + cf.at(j).feature2;
                long timeStep = ts.getOneFeatureData(ts.getNameFeatures().at(0)).at(i);
                AnomalyReport anomalyReport(description, timeStep);
                AR.push_back(anomalyReport);
            }
        }
    }
    return AR;
}

//    int numOfFeatures = ts.getNumOfFeatures();
//    int numOfRecords = ts.getNumOfRecords();
//    vector<string> featNames = ts.getNameFeatures();
//    correlatedFeatures currentCorrelated;
//    // create an array from the TimeSeries table.
//    float vals[numOfFeatures][numOfRecords];
//    for (int i = 0; i < numOfFeatures; i++) {
//        for (int j = 0; j < numOfRecords; j++) {
//            vals[i][j] = ts.getFeatureDateAtTime(featNames[i], j + 1);
//        }
//    }
//    for (int i = 0; i < numOfRecords; ++i) {
//        for (int j = 0; j < numOfFeatures; ++j) {
//            currentCorrelated = getCorreatedFeaturs(featNames[j]);
//            Point corrPoint = new Point(vals[i][j], vals[i][featNames.])
//
//        }
//    }
//    vector<AnomalyReport> vA;
//    int numOfRecords = ts.getNumOfRecords();
//    for (int i = 0; i < cf.size(); ++i) {
//        vector<float> x = ts.getOneFeatureData(cf[i].feature1);
//        vector<float> y = ts.getOneFeatureData(cf[i].feature2);
//        for (int j = 0; j < numOfRecords; ++j) {
//            float distance = abs(y[j] - cf[i].lin_reg.f(x[j]));
//            if(distance > cf[i].threshold) {
//                //AnomalyReport
//            }
//        }
//    }

//long timeStep(int recordIndex, const TimeSeries &ts) {
//    long time = ts.getOneFeatureData(ts.getNameFeatures().at(0)).at(recordIndex);
//    return time;
//}


float SimpleAnomalyDetector::getThreshold(Point **pointsArr, int size, Line rl) {
    float max = 0;
    for (int i = 0; i < size; i++) {
        float distance = abs(pointsArr[i]->y - rl.f(pointsArr[i]->x));
        if (distance > max)
            max = distance;
    }
    return max;
}




