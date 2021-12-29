#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "anomaly_detection_util.h"
using namespace std;

float expectation(float *x, int size) {
    float sum = 0; //Initialization to calculate x1+x2+...xn
    for (int i=0;i <size;i++) {
        sum=sum+x[i];
    }
    return (1/(float)size)*sum;
}

//The function var should return the variance for a final sample of a discrete variable X.
float var(float *x, int size) {
    float sumOfSquares = 0; //Initialization to calculate (x1)^2+(x2)^2+...(xn)^2
    for (int i=0;i <size;i++){
        sumOfSquares = sumOfSquares+(x[i]*x[i]);
    }
    float expectedValue= expectation(x,size);
    float var=((1/(float)(size)) * sumOfSquares)-(expectedValue) * (expectedValue);
    return var;
}

//The cov function should return the common variance of the variables X and Y.
float cov(float *x, float *y, int size) {
    float eX= expectation(x,size);
    float eY= expectation(y,size);
    float sum=0;
    for(int i=0;i<size;i++) {
        sum+=(x[i]-eX)*(y[i]-eY);
    }
    float covariance=((1/(float)(size))*sum);
    return covariance ;
}

// returns the Pearson corrlation coefficient of X and Y
float pearson(float *x, float *y, int size) {
    float c= cov(x,y,size);
    float vx= var(x,size);
    float vy= var(y,size);
    float standardDeviationX= std::sqrt(vx);
    float standardDeviationY= std::sqrt(vy);
    return c/(standardDeviationX*standardDeviationY);
}

// calculates the average of an array of floats
float avg (float* x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + x[i];
    }
    float avg = sum / size;
    return avg;
}


// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {

    // create an array of all the x and y values of the points
    float* x = new float[size];
    float* y = new float[size];

    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }

    // calculate the line equation using linear regression
    float a = (cov(x, y, size)) / (var(x, size));
    float b = avg(y, size) - a * avg(x, size);
    Line line;
    line.a = a;
    line.b = b;
    return line;
}



// returns the deviation between point p and the line
float dev(Point p,Line l) {
    float expectedValue = (l.a * p.x) + l.b;
    float deviation = fabs(expectedValue - p.y);
    return deviation;
}


// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    Line line;

    // calculate the line equation using the points
    line = linear_reg(points, size);

    // calculate deviation
    float deviation = dev(p, line);
    return deviation;
}
