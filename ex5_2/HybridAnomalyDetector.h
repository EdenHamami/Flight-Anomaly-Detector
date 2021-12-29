

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();

    void addToCF(const TimeSeries &ts, string name1, string name2, float correlation);

    bool checkForAnomaly(correlatedFeatures *correlatedFeature, float deviation, Point p);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
