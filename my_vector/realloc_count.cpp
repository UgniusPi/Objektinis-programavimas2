#include <iostream>
#include <vector>
#include <cstdint>
#include "Vector.h"
#include <chrono>

int main() {
    using namespace std::chrono;
    const std::uint64_t N = 100000000ULL; // 100 million

    std::cout << "Counting reallocations for N=" << N << "\n";

    // std::vector
    {
        std::vector<int> v;
        std::uint64_t reallocs = 0;
        auto t0 = steady_clock::now();
        for (std::uint64_t i = 0; i < N; ++i) {
            if (v.capacity() == v.size()) ++reallocs;
            v.push_back(static_cast<int>(i));
        }
        auto t1 = steady_clock::now();
        double ms = duration<double, std::milli>(t1 - t0).count();
        std::cout << "std::vector: reallocations=" << reallocs << ", time_ms=" << ms << "\n";
    }

    // mystl::Vector
    {
        mystl::Vector<int> v;
        std::uint64_t reallocs = 0;
        auto t0 = steady_clock::now();
        for (std::uint64_t i = 0; i < N; ++i) {
            if (v.capacity() == v.size()) ++reallocs;
            v.push_back(static_cast<int>(i));
        }
        auto t1 = steady_clock::now();
        double ms = duration<double, std::milli>(t1 - t0).count();
        std::cout << "mystl::Vector: reallocations=" << reallocs << ", time_ms=" << ms << "\n";
    }

    return 0;
}
