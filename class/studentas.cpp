#include "studentas.h"
#include <sstream>
#include <algorithm>
#include <iostream>


Studentas::Studentas(std::istream& is) {
    readStudent(is);
}

Studentas::Studentas(const Studentas &other)
    : vard_(other.vard_), pav_(other.pav_), tarp_(other.tarp_), egz_(other.egz_), gal_(other.gal_) {
    // std::cerr << "[Studentas] copy ctor: " << vard_ << " " << pav_ << "\n";
}

Studentas::Studentas(Studentas &&other) noexcept
    : vard_(std::move(other.vard_)), pav_(std::move(other.pav_)), tarp_(std::move(other.tarp_)), egz_(other.egz_), gal_(other.gal_) {
    other.egz_ = 0; other.gal_ = 0;
    // std::cerr << "[Studentas] move ctor\n";
}

Studentas &Studentas::operator=(const Studentas &other) {
    if (this == &other) return *this;
    vard_ = other.vard_;
    pav_ = other.pav_;
    tarp_ = other.tarp_;
    egz_ = other.egz_;
    gal_ = other.gal_;
    // std::cerr << "[Studentas] copy assign: " << vard_ << " " << pav_ << "\n";
    return *this;
}

Studentas &Studentas::operator=(Studentas &&other) noexcept {
    if (this == &other) return *this;
    vard_ = std::move(other.vard_);
    pav_ = std::move(other.pav_);
    tarp_ = std::move(other.tarp_);
    egz_ = other.egz_;
    gal_ = other.gal_;
    other.egz_ = 0; other.gal_ = 0;
    // std::cerr << "[Studentas] move assign\n";
    return *this;
}

Studentas::~Studentas() {
}

std::istream& Studentas::readStudent(std::istream& is) {
    if (!(is >> vard_)) return is;
    if (!(is >> pav_)) return is;

    std::vector<int> paz;
    int val;
    while (is >> val) {
        paz.push_back(val);
    }

    if (!paz.empty()) {
        egz_ = paz.back();
        paz.pop_back();
        tarp_ = paz;
    } else {
        egz_ = 0;
        tarp_.clear();
    }

    return is;
}

double Studentas::galBalas(int pasirink) {
    if (pasirink == 1) {
        if (tarp_.empty()) return (double)egz_ * 0.6;
        double suma = 0;
        for (int p : tarp_) suma += p;
        double vid = suma / (double)tarp_.size();
        return vid * 0.4 + (double)egz_ * 0.6;
    }

    if (tarp_.empty()) return (double)egz_ * 0.6;
    auto tmp = tarp_;
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    double med = 0;
    if (n % 2 == 1) med = tmp[n/2];
    else med = ((double)tmp[n/2] + tmp[n/2 - 1]) / 2.0;
    return med * 0.4 + (double)egz_ * 0.6;
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.readStudent(is);
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << s.vard_ << " " << s.pav_;
    for (const auto &p : s.tarp_) os << " " << p;
    os << " " << s.egz_;
    os << " " << s.gal_;
    return os;
}

bool compare(const Studentas &a, const Studentas &b) {
    return a.getVard() < b.getVard();
}

bool comparePagalPavarde(const Studentas &a, const Studentas &b) {
    return a.getPav() < b.getPav();
}

bool comparePagalGal(const Studentas &a, const Studentas &b) {
    return a.getGal() > b.getGal();
}