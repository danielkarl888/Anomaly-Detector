#include <cmath>
#include "anomaly_detection_util.h"
/*
 * Author: 318324563 - Daniel Meir Karl
 */
/**
 * return the average of the array.
 * @param x is an array of numbers
 * @param size of the array.
 * @return the average.
 */
float avg(float* x, int size) {
    float sum = 0;
    for (int i = 0 ; i < size; i++) {
        sum += x[i];
    }
    return sum / size;
}
// returns the variance of X and Y
float var(float* x, int size) {
    float avg2 = avg(x, size);
    float sum = 0;
    // sum all elements in the array in which every element is squared
    for (int i = 0 ; i < size; i++) {
        sum += pow(x[i], 2);
    }
    // divide the summed with the number of elements.
    sum /= size;
    return sum - avg2 * avg2;
}
// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i] * y[i];
    }
    sum /= size;
    return sum - avg(x, size) * avg(y, size);
}
// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    return cov(x, y, size) / (sqrt(var(x,size)) * sqrt(var(y,size)));
}
// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {
    float xPoints[size], yPoints[size];
    for (int i = 0; i < size; ++i) {
        xPoints[i] = points[i]->x;
        yPoints[i] = points[i]->y;
    }
    float aParam = cov(xPoints, yPoints, size) / var(xPoints,size);
    float bParam = avg(yPoints, size) - aParam * avg(xPoints, size);
    return Line(aParam, bParam);
}
// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}
float dev(Point p,Line l) {
    return std::abs(l.f(p.x) - p.y);
}







