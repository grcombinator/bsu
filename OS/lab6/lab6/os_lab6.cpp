#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

struct ThreadData {
    std::vector<std::string> v;
    char A = 0, B = 0;
};

std::vector<std::string> workResult;
long long MultElementResult = 1;

std::mutex mtx_start;                        
std::condition_variable_any cv_start;
bool flag_start_ready = false;

std::mutex cs;                               

std::mutex mtx_result_mult;                  
std::condition_variable_any cv_result_mult;
bool flag_mult_ready = false;

void thread_work(ThreadData& data) {
    {
        std::unique_lock<std::mutex> lk(mtx_start);
        cv_start.wait(lk, [] { return flag_start_ready; });
    }

    std::cout << "work is start\n";

    int time;
    std::cout << "Enter sleep time:\n";
    std::cin >> time;

    for (const auto& str : data.v) {
        bool valid = true;
        for (char c : str) {
            if (c < data.A || c > data.B) {
                valid = false;
                break;
            }
        }

        if (valid) {
            std::lock_guard<std::mutex> lock(cs);
            workResult.push_back(str);
            std::cout << "work: добавлен элемент '" << str << "'\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    std::cout << "work is end\n";
}

void thread_mult_element(ThreadData& data) {
    {
        std::unique_lock<std::mutex> lk(mtx_start);
        cv_start.wait(lk, [] { return flag_start_ready; });
    }

    std::cout << "MultElement is start\n";

    for (const auto& str : data.v) {
        MultElementResult *= static_cast<long long>(str.size());
    }

    std::cout << "MultElement is end\n";

    {
        std::lock_guard<std::mutex> lock(mtx_result_mult);
        flag_mult_ready = true;
    }
    cv_result_mult.notify_one();
}

int main() {
    ThreadData data;

    int size;
    std::cout << "Enter size of massive: ";
    std::cin >> size;

    std::cout << "\nEnter " << size << " strings:\n";
    std::string s;
    for (int i = 0; i < size; ++i) {
        std::cin >> s;
        data.v.push_back(s);
    }

    std::cout << "Original array:\n";
    for (const auto& str : data.v) {
        std::cout << str << ' ';
    }
    std::cout << '\n';

    std::thread t_work(thread_work, std::ref(data));
    std::thread t_mult(thread_mult_element, std::ref(data));

    std::cout << "Enter two symbols A and B:\n";
    std::cin >> data.A >> data.B;

    {
        std::lock_guard<std::mutex> lock(mtx_start);
        flag_start_ready = true;
    }
    cv_start.notify_all();  

    {
        std::unique_lock<std::mutex> lock(cs);
        std::cout << "Results from work thread:\n";
        for (const auto& res : workResult) {
            std::cout << res << '\n';
        }
    }

    {
        std::unique_lock<std::mutex> lock(mtx_result_mult);
        cv_result_mult.wait(lock, [] { return flag_mult_ready; });
        std::cout << "Result from MultElement: " << MultElementResult << '\n';
    }

    t_work.join();
    t_mult.join();

    return 0;
}