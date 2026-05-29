/**
 * @file studentas.h (my_vector kopija)
 */

#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include "Vector.h"
#include "zmogus.h"

using std::string;
using mystl::Vector;
using std::istream;
using std::ostream;

class Studentas : public Zmogus {
private:
    Vector<int> tarp_;
    int egz_;
    double gal_;
public:
    Studentas() : Zmogus(), tarp_(), egz_(0), gal_(0) { }
    Studentas(istream& is);
    Studentas(const Studentas &other);
    Studentas(Studentas &&other) noexcept;
    Studentas &operator=(const Studentas &other);
    Studentas &operator=(Studentas &&other) noexcept;
    ~Studentas();

    inline const Vector<int>& getTarp() const { return tarp_; }
    inline int getEgz() const { return egz_; }
    inline double getGal() const { return gal_; }

    inline void setTarp(const Vector<int> &t) { tarp_ = t; }
    inline void addTarp(int t) { tarp_.push_back(t); }
    inline void clearTarp() { tarp_.clear(); }
    inline void setEgz(int e) { egz_ = e; }
    inline void setGal(double g) { gal_ = g; }

    istream& readStudent(istream&);
    double galBalas(int pasirink);
    friend istream& operator>>(istream& is, Studentas& s);
    friend ostream& operator<<(ostream& os, const Studentas& s);
};

bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalGal(const Studentas&, const Studentas&);

void printStudentTiming();

#endif
