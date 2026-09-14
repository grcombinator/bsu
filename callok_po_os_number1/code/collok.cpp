#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdexcept>


std::vector<unsigned long long> factorials(int n) {
    if (n <= 0) {
        throw std::invalid_argument("n должен быть натуральным числом.");
    }
    std::vector<unsigned long long> result;
    result.reserve(n);
    
    unsigned long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
        result.push_back(fact);
    }
    return result;
}


std::vector<int> removeDuplicates(const std::vector<int>& input) {
    std::unordered_set<int> seen;
    std::vector<int> result;

    for (const auto& num : input) {
        if (seen.insert(num).second) { 
            result.push_back(num);
        }
    }
    return result;
}


struct ListNode {
    int value;
    ListNode* next;
    ListNode(int val) : value(val), next(nullptr) {}
};


ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr; 
    return newHead;
}


int main() {
    
    int n;
    std::cout << "Введите натуральное число n для вычисления первых n факториалов: ";
    std::cin >> n;
    try {
        auto factorialsResult = factorials(n);
        std::cout << "Первые " << n << " факториалы: ";
        for (const auto& fact : factorialsResult) {
            std::cout << fact << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;
    std::vector<int> numbers(size);
    std::cout << "Введите " << size << " чисел: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }
    
    auto uniqueNumbers = removeDuplicates(numbers);
    std::cout << "Массив без дубликатов: ";
    for (const auto& num : uniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 3. Разворот связного списка
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    
    std::cout << "Исходный связный список: ";
    for (ListNode* curr = head; curr; curr = curr->next) {
        std::cout << curr->value << " ";
    }
    std::cout << std::endl;

    ListNode* reversedHead = reverseList(head);
    std::cout << "Развернутый связный список: ";
    for (ListNode* curr = reversedHead; curr; curr = curr->next) {
        std::cout << curr->value << " ";
    }
    std::cout << std::endl;

    while (reversedHead) {
        ListNode* temp = reversedHead;
        reversedHead = reversedHead->next;
        delete temp;
    }

    return 0;
}
