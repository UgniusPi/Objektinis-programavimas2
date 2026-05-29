/**
 * @file studentas.cpp
 * @brief Studento klasės funkcijų įgyvendinimai.
 */

#include "studentas.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>

using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;


Studentas::Studentas(std::istream& is) {
    readStudent(is);
}

Studentas::Studentas(const Studentas &other)
    : Zmogus(other), tarp_(other.tarp_), egz_(other.egz_), gal_(other.gal_) {
    // std::cerr << "[Studentas] copy ctor: " << vard_ << " " << pav_ << "\n";
}

Studentas::Studentas(Studentas &&other) noexcept
    : Zmogus(std::move(other)), tarp_(std::move(other.tarp_)), egz_(other.egz_), gal_(other.gal_) {
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
    std::string line;
    if (!std::getline(is, line)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (line.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::istringstream iss(line);
    std::string vard, pav;
    if (!(iss >> vard >> pav)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::vector<int> paz;
    int val;
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    int pushCount = 0;
    while (iss >> val) {
        if (val < 0 || val > 10) {
            is.setstate(std::ios::failbit);
            return is;
        }
        paz.push_back(val);
        ++pushCount;
    }
    auto t1 = steady_clock::now();
    duration<double> pushElapsed = t1 - t0;
    static double total_paz_push_time = 0.0;
    static size_t total_paz_push_count = 0;
    total_paz_push_time += pushElapsed.count();
    total_paz_push_count += pushCount;

    if (paz.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    vard_ = vard;
    pav_ = pav;
    egz_ = paz.back();
    paz.pop_back();
    tarp_ = paz;

    return is;
}

double Studentas::galBalas(int pasirink) {
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    double result = 0.0;
    if (pasirink == 1) {
        if (tarp_.empty()) result = (double)egz_ * 0.6;
        else {
            double suma = 0;
            for (int p : tarp_) suma += p;
            double vid = suma / (double)tarp_.size();
            result = vid * 0.4 + (double)egz_ * 0.6;
        }
    } else {
        if (tarp_.empty()) result = (double)egz_ * 0.6;
        else {
            auto tmp = tarp_;
            std::sort(tmp.begin(), tmp.end());
            size_t n = tmp.size();
            double med = 0;
            if (n % 2 == 1) med = tmp[n/2];
            else med = ((double)tmp[n/2] + tmp[n/2 - 1]) / 2.0;
            result = med * 0.4 + (double)egz_ * 0.6;
        }
    }
    auto t1 = steady_clock::now();
    duration<double> elapsed = t1 - t0;
    static double total_galbal_time = 0.0;
    static size_t total_galbal_calls = 0;
    total_galbal_time += elapsed.count();
    ++total_galbal_calls;
    return result;
}

void printStudentTiming() {
    std::cout << "Studentas: laiko matavimai sukaupti (detalesni duomenys spausdinami vietose):" << std::endl;
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.readStudent(is);
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << left << setw(21) << s.getPav() << left << setw(16) << s.getVard() << left << setw(20) << fixed << setprecision(2) << s.gal_;
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