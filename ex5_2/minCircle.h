
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

float distance(Point point1, Point point2);

Circle findMinCircle(Point** points, size_t size);

Circle alg_welzl(vector<Point> P, vector<Point> R, size_t n);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */
