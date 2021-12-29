
#include "HybridAnomalyDetector.h"


HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

bool HybridAnomalyDetector::checkForAnomaly(correlatedFeatures* correlatedFeature, float deviation, Point p) {
    bool simple = (correlatedFeature->corrlation >= getTopThreshold() &&
            SimpleAnomalyDetector::checkForAnomaly(correlatedFeature, deviation, p));
    bool hybrid = (correlatedFeature->corrlation > 0.5 && correlatedFeature->corrlation < getTopThreshold() &&
            distance(Point(correlatedFeature->centerX, correlatedFeature->centerY), p) >
            correlatedFeature->threshold);
    return simple || hybrid;
}

void HybridAnomalyDetector::addToCF(const TimeSeries& ts, string name1, string name2, float correlation) {
    if(correlation >= getTopThreshold()) {
        SimpleAnomalyDetector::addToCF(ts, name1, name2, (correlation * 1.1f));
        return;
    }
    if(correlation > 0.5) {
        const auto& vec1 = ts.getData(name1);
        const auto& vec2 = ts.getData(name2);
        Point** points = new Point*[ts.getNumRows()];
        for (int i = 0; i < ts.getNumRows(); i++) {
            points[i] = new Point(vec1[i], vec2[i]);
        }
        correlatedFeatures newFeatures;
        newFeatures.feature1 = name1;
        newFeatures.feature2 = name2;
        newFeatures.corrlation = correlation;

        Circle minCircle = findMinCircle(points, ts.getNumRows());
        newFeatures.threshold = (minCircle.radius * 1.1);
        newFeatures.centerX = minCircle.center.x;
        newFeatures.centerY = minCircle.center.y;
        cf.push_back(newFeatures);
    }
}