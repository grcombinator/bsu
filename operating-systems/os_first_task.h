#include<vector>
#include <stdexcept>
template <typename T>
std::vector<T> fibonacci(T n) {
    if (n < 0) {
        throw std::invalid_argument("n must be 0 or greater"); 
    }
    std::vector<T> arr(n);
    if (n >= 1) {
        arr[0] = 0;
        if (n >= 2) {
            arr[1] = 1;
        }
        for (T i = 2; i < n; i++) {
            arr[i] = arr[i - 2] + arr[i - 1];
        }
    }
    return arr;
}