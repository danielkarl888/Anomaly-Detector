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
    return sum/size;
}
// returns the variance of X and Y
float var(float* x, int size) {
    float avg2 = avg(x, size);
    float sum;
    for (int i = 0 ; i <= size; i++) {
        sum += pow(avg2, 2);
    }
    sum /= size;
    return sum - pow(avg2, 2);
}