#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\n"
              << duration.count() << "ms";

    return 0;
}
