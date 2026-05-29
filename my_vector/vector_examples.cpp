#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "Vector.h"

using std::cout;
using std::endl;
using mystl::Item;

template<typename StdVec, typename MyVec>
bool equal_contents(const StdVec &s, const MyVec &m) {
    if (s.size() != m.size()) return false;
    auto it1 = s.begin();
    auto it2 = m.begin();
    for (; it1 != s.end(); ++it1, ++it2) {
        if (!(*it1 == *it2)) return false;
    }
    return true;
}

void print_test_result(const char *name, bool ok) {
    cout << name << ": " << (ok ? "OK" : "FAIL") << endl;
}



int main() {
    using mystl::Vector;
    bool all_ok = true;

    // 1) push_back, size, iteration
    std::vector<int> sv1;
    Vector<int> mv1;
    sv1.push_back(1); sv1.push_back(2); sv1.push_back(3);
    mv1.push_back(1); mv1.push_back(2); mv1.push_back(3);
    bool t1 = equal_contents(sv1, mv1) && sv1.size() == mv1.size();
    print_test_result("push_back / iteration / size", t1);
    all_ok &= t1;

    // 2) initializer_list, operator[] and at()
    std::vector<std::string> sv2 = {"a","b","c"};
    Vector<std::string> mv2 = {"a","b","c"};
    bool t2 = (sv2[1] == mv2[1]) && (sv2.at(2) == mv2.at(2)) && equal_contents(sv2, mv2);
    print_test_result("initializer_list / operator[] / at", t2);
    all_ok &= t2;

    // 3) insert and erase
    std::vector<int> sv3 = {1,3,4};
    Vector<int> mv3 = {1,3,4};
    sv3.insert(sv3.begin() + 1, 2);
    mv3.insert(mv3.begin() + 1, 2);
    bool t3a = equal_contents(sv3, mv3);
    sv3.erase(sv3.begin() + 2);
    mv3.erase(mv3.begin() + 2);
    bool t3b = equal_contents(sv3, mv3);
    print_test_result("insert", t3a);
    print_test_result("erase", t3b);
    all_ok &= (t3a && t3b);

    // 4) reserve, capacity
    std::vector<int> sv4; Vector<int> mv4;
    sv4.reserve(16); mv4.reserve(16);
    bool t4 = (sv4.capacity() == mv4.capacity());
    print_test_result("reserve / capacity", t4);
    all_ok &= t4;
}
