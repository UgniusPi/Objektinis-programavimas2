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

    // 5) resize
    std::vector<int> sv5 = {1,2,3,4,5}; Vector<int> mv5 = {1,2,3,4,5};
    sv5.resize(3); mv5.resize(3);
    bool t5a = equal_contents(sv5, mv5) && sv5.size() == mv5.size();
    sv5.resize(6, 9); mv5.resize(6, 9);
    bool t5b = equal_contents(sv5, mv5) && sv5.size() == mv5.size();
    print_test_result("resize (smaller)", t5a);
    print_test_result("resize (larger with value)", t5b);
    all_ok &= (t5a && t5b);

    // 6) emplace_back with struct
    std::vector<Item> sv6; Vector<Item> mv6;
    sv6.emplace_back(std::string("Alice"), 30); sv6.emplace_back(std::string("Bob"), 25);
    mv6.emplace_back(std::string("Alice"), 30); mv6.emplace_back(std::string("Bob"), 25);
    bool t6 = equal_contents(sv6, mv6);
    print_test_result("emplace_back (construct in place)", t6);
    all_ok &= t6;

    // 7) copy and move
    std::vector<int> sv7 = {1,2,3}; Vector<int> mv7 = {1,2,3};
    std::vector<int> sv7_copy = sv7; Vector<int> mv7_copy = mv7; // copy ctor
    bool t7a = equal_contents(sv7_copy, mv7_copy);
    std::vector<int> sv7_move = std::move(sv7); Vector<int> mv7_move = std::move(mv7);
    bool t7b = equal_contents(sv7_move, mv7_move);
    print_test_result("copy constructor", t7a);
    print_test_result("move constructor", t7b);
    all_ok &= (t7a && t7b);

    // 8) assign and swap
    std::vector<int> sv8; Vector<int> mv8;
    sv8.assign(4, 7); mv8.assign(4, 7);
    bool t8a = equal_contents(sv8, mv8);
    sv8.swap(sv7_copy); mv8.swap(mv7_copy);
    bool t8b = equal_contents(sv8, mv8);
    print_test_result("assign", t8a);
    print_test_result("swap", t8b);
    all_ok &= (t8a && t8b);

    cout << (all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << endl;
    return all_ok ? 0 : 1;
}
