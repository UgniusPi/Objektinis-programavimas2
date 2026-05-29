#include <chrono>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Vector.h"

int main() {
    using namespace std::chrono;
    using mystl::Vector;

    std::vector<size_t> sizes = {10000u, 100000u, 1000000u, 10000000u, 100000000u};
    const int runs = 3;

    std::cout << "Benchmark: push_back (average of " << runs << " runs)\n";
    std::cout << "Size,std_vector_ms,mystl_vector_ms\n";

    for (size_t sz : sizes) {
        double sum_std = 0.0;
        double sum_my = 0.0;

        for (int r = 0; r < runs; ++r) {
            // std::vector
            {
                auto t0 = steady_clock::now();
                std::vector<int> v;
                for (size_t i = 0; i < sz; ++i) v.push_back(static_cast<int>(i));
                auto t1 = steady_clock::now();
                sum_std += duration<double, std::milli>(t1 - t0).count();
            }

            // mystl::Vector
            {
                auto t0 = steady_clock::now();
                Vector<int> v;
                for (size_t i = 0; i < sz; ++i) v.push_back(static_cast<int>(i));
                auto t1 = steady_clock::now();
                sum_my += duration<double, std::milli>(t1 - t0).count();
            }
        }

        double avg_std = sum_std / runs;
        double avg_my = sum_my / runs;
        std::cout << sz << ',' << std::fixed << std::setprecision(3) << avg_std << ',' << avg_my << '\n';
    }

    return 0;
}
