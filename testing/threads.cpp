#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdio.h>

int counter = 0;
std::mutex mtx;

void foo() {
    static int n = 0;
    n++;
    printf("%d\n", n);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // Code here
    foo();
    foo();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n"
              << duration.count() << "ms.";

    std::cin >> counter;
    return 0;
}
