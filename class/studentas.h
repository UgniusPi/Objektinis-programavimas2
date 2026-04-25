#include <string>
#include <vector>

using std::string;
using std::vector;
using std::istream;
using std::ostream;

class Studentas {
private:
    string vard_;
    string pav_;
    vector<int> tarp_;
    int egz_;
    double gal_;
public:
    Studentas() : vard_("Nenurodyta"), pav_("Nenurodyta"), egz_(0), gal_(0) { }
    Studentas(istream& is);

    Studentas(const Studentas &other);
    Studentas(Studentas &&other) noexcept;
    Studentas &operator=(const Studentas &other);
    Studentas &operator=(Studentas &&other) noexcept;
    ~Studentas();

    inline string getVard() const { return vard_; }
    inline string getPav() const { return pav_; }
    inline const vector<int>& getTarp() const { return tarp_; }
    inline int getEgz() const { return egz_; }
    inline double getGal() const { return gal_; }

    inline void setVard(const string &v) { vard_ = v; }
    inline void setPav(const string &p) { pav_ = p; }
    inline void setTarp(const vector<int> &t) { tarp_ = t; }
    inline void addTarp(int t) { tarp_.push_back(t); }
    inline void clearTarp() { tarp_.clear(); }
    inline void setEgz(int e) { egz_ = e; }
    inline void setGal(double g) { gal_ = g; }
    istream& readStudent(istream&);

    double galBalas(int pasirink);
    friend ostream& operator<<(std::ostream& os, const Studentas& s);
};

bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalGal(const Studentas&, const Studentas&);