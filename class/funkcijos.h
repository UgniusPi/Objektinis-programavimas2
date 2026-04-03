#include <vector>
#include <string>
#include "strukturos.h"

using std::string;
using std::vector;

void ivestEkr(vector<Studentas> &studentai, bool rndPaz, bool rndVard);
void ivestIsFailo(vector<Studentas> &studentai, string failoKelias, bool &klaida);
void isvestEkr(const vector<Studentas> &studentai, int pasirink);
void isvestIFaila(const vector<Studentas> &studentai, int pasirink, string failoPav = "isvestis.txt");
void skaicGal(vector<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
string rndVardas(int from, int to);
void klauskEigos(bool &testi, Nustatymai &nustatymai);
void rusiuok(vector<Studentas> &studentai, int rusBudas);
string klauskFailo(bool &klaida);
void skirstyk(vector<Studentas> &studentai, vector<Studentas> &vargsiukai);
string kurkFaila(int studSk, int pazSk);