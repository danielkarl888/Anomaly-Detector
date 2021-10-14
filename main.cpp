#include <iostream>
#include <anomaly_detection_util.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    float arr[5] = {10,2,3,4,10};
    std::cout << var(arr, 5);
    return 0;
}
