#include <iostream>
#include <anomaly_detection_util.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    int arr[5] = {10,2,3,4,10};
    *arr = 100;
    std::cout << avg(reinterpret_cast<float *>(arr), 5);

    return 0;
}
