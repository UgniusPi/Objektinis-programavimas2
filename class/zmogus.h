#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

/**
 * @file zmogus.h
 * @brief Bazinė abstrakti klasė `Zmogus`, sauganti asmens vardą ir pavardę.
 */

/**
 * @brief Abstrakti bazinė klasė, kurioje saugomi asmens duomenys.
 */
class Zmogus {
protected:
    std::string vard_;
    std::string pav_;
public:
    /** @brief Numatytoji konstruktoriaus reikšmė (nenustatyta). */
    Zmogus() : vard_("Nenurodyta"), pav_("Nenurodyta") {}
    /** @brief Konstruktorius su vardu ir pavarde. */
    Zmogus(const std::string &vard, const std::string &pav) : vard_(vard), pav_(pav) {}
    /** @brief Abstraktus destruktorius (padaro klasę abstrakčia). */
    virtual ~Zmogus() = 0;

    /** @brief Grąžina vardą. */
    inline std::string getVard() const { return vard_; }
    /** @brief Grąžina pavardę. */
    inline std::string getPav() const { return pav_; }
    /** @brief Nustato vardą. */
    inline void setVard(const std::string &v) { vard_ = v; }
    /** @brief Nustato pavardę. */
    inline void setPav(const std::string &p) { pav_ = p; }
};

inline Zmogus::~Zmogus() {}

#endif
