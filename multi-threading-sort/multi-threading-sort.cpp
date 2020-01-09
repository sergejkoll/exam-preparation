// Copyright 2020 AndreevSemen semen.andreev00@mail.ru (librarians-squad)

#include <iostream>

#include <vector>
#include <thread>
#include <algorithm>

template<class IT1, size_t MinFragmentSize=4>
void MultiThreadingSort(IT1 first, IT1 last) {
    size_t distance = std::distance(first, last);
    IT1 half = first + distance/2;

    if (distance/2 < MinFragmentSize) {
        std::sort(first, half);
        std::sort(half, last);
    } else {
        std::thread firstThread(MultiThreadingSort<IT1, MinFragmentSize>, first, half);
        std::thread secondThread(MultiThreadingSort<IT1, MinFragmentSize>, half, last);

        firstThread.join();
        secondThread.join();
    }

    std::vector<typename IT1::value_type> merged(distance);
    std::merge(first, half, half, last, merged.begin());

    for (const auto& item : merged) {
        if (first == last) break;

        *first = item;
        ++first;
    }
}

int main() {
    std::vector<int> vec;
    for (size_t i = 10000; i != 0; --i) {
        vec.push_back(i);
    }

    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    auto sorted = vec;
    MultiThreadingSort(vec.begin(), vec.end());

    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::reverse(sorted.begin(), sorted.end());
    std::cout << (sorted == vec) << std::endl;

    return 0;
}
