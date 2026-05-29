#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vard_;
    std::string pav_;
public:
    Zmogus() : vard_("Nenurodyta"), pav_("Nenurodyta") {}
    Zmogus(const std::string &vard, const std::string &pav) : vard_(vard), pav_(pav) {}
    virtual ~Zmogus() = 0;

    inline std::string getVard() const { return vard_; }
    inline std::string getPav() const { return pav_; }
    inline void setVard(const std::string &v) { vard_ = v; }
    inline void setPav(const std::string &p) { pav_ = p; }
};

inline Zmogus::~Zmogus() {}

#endif
