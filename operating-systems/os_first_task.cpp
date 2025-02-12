#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include "os_first_task.h"

int main() {
    int n;
    try {
        std::cin >> n;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            throw std::invalid_argument("Errror: invalid input");
        }
        std::vector<int> result = fibonacci(n);
        for (int i = 0; i < n; i++) {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}