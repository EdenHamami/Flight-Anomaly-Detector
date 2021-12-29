#include <vector>
#include <string>
#include <fstream>
#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "HybridAnomalyDetector.h"

void SimpleAnomalyDetector::addToCF(const TimeSeries& ts, string name1, string name2, float correlation){
    correlatedFeatures newFeatures;
    newFeatures.feature1 = name1;
    newFeatures.feature2 = name2;
    newFeatures.corrlation = correlation;

    const auto& vec1 = ts.getData(name1);
    const auto& vec2 = ts.getData(name2);
    Point** points = new Point*[ts.getNumRows()];
    for (int i = 0; i < ts.getNumRows(); i++) {
        points[i] = new Point(vec1[i], vec2[i]);
    }
    const Line line = linear_reg(points, ts.getNumRows());
    newFeatures.lin_reg = line;

    float threshold = 0;
    for (int i = 0; i < ts.getNumRows(); i++) {
        float deviation = abs(dev(*points[i], line));
        if (threshold < deviation) {
            threshold = deviation;
        }
    }
    newFeatures.threshold = threshold;
    cf.push_back(newFeatures);
    for (int i = 0; i < ts.getNumRows(); i++) {
        delete points[i];
    }
    delete[] points;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    for (int i = 0; i < ts.getNumFeatures(); i++) {
        float m = 0;
        float p = 0;
        int c = -1;
        string name1;
        string name2;
        for(int j = i + 1; j < ts.getNumFeatures(); j++){
            name1 = ts.getTitles()[i];
            name2 = ts.getTitles()[j];
            vector<float> data1 = ts.getData(name1);
            vector<float> data2 = ts.getData(name2);
            float *data1Ptr = data1.data();
            float *data2Ptr = data2.data();
            float p= fabs(pearson(data1Ptr, data2Ptr, ts.getNumRows()));
            if(p > m) {
                m = p;
                c = j;
            }

        }
        if((c != -1) && (m > 0.5)) {
            m = (m * 1.1f);
            addToCF(ts, name1, ts.getTitles()[c], m);
        }


    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> anomaly;
    for(int i = 0; i < ts.getNumRows(); i++) {
        for(int j = 0; j < ts.getNumFeatures(); j++) {
            auto title = ts.getTitles()[j];
            correlatedFeatures* correlatedFeature = getCorrelatedFeature(title);
            if (correlatedFeature == nullptr) {
                continue;
            } else {
                const Point p(ts.getData(correlatedFeature->feature1)[i], ts.getData(correlatedFeature->feature2)[i]);
                float deviation = dev(p, correlatedFeature->lin_reg);
                if(checkForAnomaly(correlatedFeature, deviation, p)) {
                    const string description = correlatedFeature->feature1 + "-" + correlatedFeature->feature2;
                    const long timeStep = i + 1;
                    AnomalyReport r(description, timeStep);
                    anomaly.push_back(r);
                }
            }

        }

    }
    return anomaly;

}

bool SimpleAnomalyDetector::checkForAnomaly(correlatedFeatures* correlatedFeature, float deviation, Point p) {
    bool result = (deviation > (correlatedFeature->threshold * 1.15));
    return result;
}


correlatedFeatures* SimpleAnomalyDetector::getCorrelatedFeature(const string title) {
    for (int i = 0; i < cf.size(); i++) {
        correlatedFeatures* feature = cf.data() + i;
        if (feature->feature1.compare(title) == 0) {
            return feature;
        }
    }
    return nullptr;
}

