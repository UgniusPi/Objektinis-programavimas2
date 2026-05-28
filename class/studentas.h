/**
 * @file studentas.h
 * @brief Studento klasė ir susiję metodai.
 */

#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include "zmogus.h"

using std::string;
using std::vector;
using std::istream;
using std::ostream;

/**
 * @brief Klasė reprezentuojanti studentą, paveldimą iš `Zmogus`.
 *
 * Laikomi tarpiniai pažymiai (`tarp_`), egzamino rezultatas (`egz_`) ir
 * galutinis balas (`gal_`).
 */
class Studentas : public Zmogus {
private:
    vector<int> tarp_;
    int egz_;
    double gal_;
public:
    /** @brief Numatytoji konstruktorius. */
    Studentas() : Zmogus(), tarp_(), egz_(0), gal_(0) { }

    /**
     * @brief Konstruktorius skaitantis studentą iš srauto.
     * @param is Įvesties srautas (vienos eilutės formato: vardas pavardė nd1 nd2 ... egz)
     */
    Studentas(istream& is);

    /** @brief Kopijavimo konstruktorius. */
    Studentas(const Studentas &other);
    /** @brief Move konstruktorius. */
    Studentas(Studentas &&other) noexcept;
    /** @brief Kopijavimo priskyrimo operatorius. */
    Studentas &operator=(const Studentas &other);
    /** @brief Move priskyrimo operatorius. */
    Studentas &operator=(Studentas &&other) noexcept;
    /** @brief Destruktorius. */
    ~Studentas();

    /** @brief Grąžina tarpinį pažymių vektorių. */
    inline const vector<int>& getTarp() const { return tarp_; }
    /** @brief Grąžina egzamino rezultatą. */
    inline int getEgz() const { return egz_; }
    /** @brief Grąžina galutinį balą. */
    inline double getGal() const { return gal_; }

    /** @brief Nustato tarpinį pažymių vektorių. */
    inline void setTarp(const vector<int> &t) { tarp_ = t; }
    /** @brief Prideda vieną tarpinį pažymį. */
    inline void addTarp(int t) { tarp_.push_back(t); }
    /** @brief Išvalo tarpinį pažymių sąrašą. */
    inline void clearTarp() { tarp_.clear(); }
    /** @brief Nustato egzamino rezultatą. */
    inline void setEgz(int e) { egz_ = e; }
    /** @brief Nustato galutinį balą. */
    inline void setGal(double g) { gal_ = g; }

    /**
     * @brief Skaito studentą iš srauto.
     * @param is Įvesties srautas.
     * @return Įvesties srautas.
     */
    istream& readStudent(istream&);

    /**
     * @brief Apskaičiuoja galutinį balą pagal pasirinktą metodą.
     * @param pasirink 1 - vidurkis, 2 - mediana.
     * @return Galutinis balas.
     */
    double galBalas(int pasirink);

    /** @brief Skaitymo operatorius. */
    friend istream& operator>>(istream& is, Studentas& s);
    /** @brief Rašymo operatorius. */
    friend ostream& operator<<(ostream& os, const Studentas& s);
};

/** @brief Lygina studentus pagal vardą (ascending). */
bool compare(const Studentas&, const Studentas&);
/** @brief Lygina studentus pagal pavardę (ascending). */
bool comparePagalPavarde(const Studentas&, const Studentas&);
/** @brief Lygina studentus pagal galutinį balą (descending). */
bool comparePagalGal(const Studentas&, const Studentas&);

#endif