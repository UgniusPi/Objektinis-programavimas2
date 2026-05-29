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
    
}
