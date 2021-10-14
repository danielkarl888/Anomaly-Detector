#include "__clang_cuda_math.h"

/**
 * return the average of the array.
 * @param x is an array of numbers
 * @param size of the array.
 * @return the average.
 */
float avg1(float* x, int size) {
    float sum;
    for (i = 0 ; i < size; i++) {
        sum += x[i];
    }
    return sum/size;
}
// returns the variance of X and Y
float var(float* x, int size) {
    float avg = avg(x, size);
    float sum;
    for (int i = 0 ; i <= size; i++) {
        sum += powif(avg, 2);
    }
    sum /= size;
    return sum - powif(avg, 2);
}


