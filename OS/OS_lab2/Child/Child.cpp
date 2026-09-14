#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }

    int size = std::atoi(argv[1]);
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = std::atoi(argv[i + 2]);
    }

    quickSort(arr, 0, size - 1);

    
    std::cout << "Sorted massive: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    int a;
    std::cin >> a;
    return 0;
}