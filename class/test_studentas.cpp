#include <iostream>
#include <sstream>
#include "studentas.h"

using std::cout;
using std::endl;

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
}