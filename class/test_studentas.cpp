#include <iostream>
#include <sstream>
#include "studentas.h"

using std::cout;
using std::endl;

#include <type_traits>

static_assert(std::is_abstract<Zmogus>::value, "Zmogus must be abstract (cannot instantiate).");

int main() {
    cout << "--- Default constructor ---" << endl;
    Studentas a;
    cout << "a: " << a << endl;

    cout << "--- Set fields ---" << endl;
    a.setVard("Jonas"); a.setPav("Jonaitis");
    a.addTarp(8); a.addTarp(9); a.setEgz(10);
    cout << "a after set: " << a << endl;

    cout << "--- Copy constructor ---" << endl;
    Studentas b(a);
    cout << "b: " << b << endl;

    cout << "--- Copy assignment ---" << endl;
    Studentas c;
    c = a;
    cout << "c: " << c << endl;

    cout << "--- Move constructor ---" << endl;
    Studentas d(std::move(a));
    cout << "d: " << d << endl;
    cout << "a after move: " << a << endl;

    cout << "--- Move assignment ---" << endl;
    Studentas e;
    e = std::move(b);
    cout << "e: " << e << endl;
    cout << "b after move assign: " << b << endl;

    cout << "--- istream operator>> test ---" << endl;
    std::istringstream iss("Petras Petraitis 6 7 8 9");
    Studentas f;
    iss >> f;
    cout << "f: " << f << endl;

    cout << "--- ostream operator<< test ---" << endl;
    std::ostringstream oss;
    oss << f;
    cout << "oss.str(): " << oss.str() << endl;

    return 0;
}