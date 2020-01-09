// Copyright 2020 AndreevSemen semen.andreev00@mail.ru (librarians-squad)

#include <iostream>
#include <thread>
#include <vector>

#include <lock_free_stack.hpp>


std::atomic_int counter = 0;

int main() {
    LockFreeStack<int> stack;
    size_t pushPopNum = 1000;

    auto lambda = [&]() {
        for (size_t i = 0; i < pushPopNum; ++i) {
            stack.Push(i);
            ++counter;

            std::this_thread::sleep_for(std::chrono::milliseconds{random()%100});

            int bucket;
            while (stack.TryPop(bucket)) {}
            --counter;
        }
    };

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 100; ++i) {
        threads.emplace_back(std::thread(lambda));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Expected : 0, Really : " << counter << std::endl;

    return 0;
}
