/**
 * @file funkcijos.h (my_vector kopija)
 * @brief Pagalbinės funkcijos (naudoja mystl::Vector)
 */

#include "Vector.h"
#include <string>
#include "strukturos.h"
#include "studentas.h"

using std::string;
using mystl::Vector;

void ivestEkr(Vector<Studentas> &studentai, bool rndPaz, bool rndVard);
void ivestIsFailo(Vector<Studentas> &studentai, string failoKelias, bool &klaida);
void isvestEkr(const Vector<Studentas> &studentai, int pasirink);
void isvestIFaila(const Vector<Studentas> &studentai, int pasirink, string failoPav = "isvestis.txt");
void skaicGal(Vector<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
string rndVardas(int from, int to);
void klauskEigos(bool &testi, Nustatymai &nustatymai);
void rusiuok(Vector<Studentas> &studentai, int rusBudas);
string klauskFailo(bool &klaida);
void skirstyk(Vector<Studentas> &studentai, Vector<Studentas> &vargsiukai);
string kurkFaila(int studSk, int pazSk);
