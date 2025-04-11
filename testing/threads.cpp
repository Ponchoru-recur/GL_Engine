#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdio.h>

int counter = 0;
std::mutex mtx;

void foo(int count, std::string name) {
    for (int i = 0; i < count; i++) {
        // std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n"
              << duration.count() << "ms.";

    std::cin >> counter;
    return 0;
}
