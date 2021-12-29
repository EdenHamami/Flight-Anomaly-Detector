#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_
#include  <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"


using namespace std;

struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    float centerX;
    float centerY;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
private:
    float topThreshold = 0.9f;
public:
    virtual void addToCF(const TimeSeries& ts, string name1, string name2, float correlation);
    SimpleAnomalyDetector() {}
    virtual ~SimpleAnomalyDetector() {}
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }
    correlatedFeatures* getCorrelatedFeature(const string title);

    float getTopThreshold() const {
        return topThreshold;
    }

    void setTopThreshold(float newThresh) {
        topThreshold = newThresh;
    }

protected:
    vector<correlatedFeatures> cf;

    virtual bool checkForAnomaly(correlatedFeatures* correlatedFeature, float deviation, Point p);
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */