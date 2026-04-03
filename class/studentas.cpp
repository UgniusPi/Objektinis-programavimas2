#include "studentas.h"
#include <sstream>
#include <algorithm>

Studentas::Studentas(std::istream& is) {
    readStudent(is);
}

std::istream& Studentas::readStudent(std::istream& is) {
    if (!(is >> vard_)) return is;
    if (!(is >> pav_)) return is;

    std::string rest;
    std::getline(is, rest); 
    std::stringstream ss(rest);
    std::vector<int> paz;
    int val;
    while (ss >> val) {
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

bool compare(const Studentas &a, const Studentas &b) {
    return a.getVard() < b.getVard();
}

bool comparePagalPavarde(const Studentas &a, const Studentas &b) {
    return a.getPav() < b.getPav();
}

bool comparePagalEgza(const Studentas &a, const Studentas &b) {
    return a.getGal() > b.getGal();
}