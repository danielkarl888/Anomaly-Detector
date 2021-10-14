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
    // avg2 is the average of the array.
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