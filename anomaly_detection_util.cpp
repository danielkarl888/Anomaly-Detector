#include <cmath>

/**
 * return the average of the array.
 * @param x is an array of numbers
 * @param size of the array.
 * @return the average.
 */
float avg(float* x, int size) {
    float sum;
    for (int i = 0 ; i < size; i++) {
        sum += x[i];
    }
    return sum / size;
}
// returns the variance of X and Y
float var(float* x, int size) {
    // avg is the average of the array.
    float avg2 = avg(x, size);
    float sum;
    // sum all elements in the array in which every element is squared
    for (int i = 0 ; i < size; i++) {
        sum += pow(x[i], 2);
    }
    // divide the summed with the number of elements.
    sum /= size;
    return sum - pow(avg2, 2);
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
    return cov(x, y, size) / (sqrt(var(x,size) * var(y, size)));
}


