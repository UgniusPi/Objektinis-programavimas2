#include <vector>
#include <string>
#include <deque>
#include "strukturos.h"

using std::string;
using std::vector;
using std::deque;

void ivestEkr(deque<Studentas> &studentai, bool rndPaz, bool rndVard);
void ivestIsFailo(deque<Studentas> &studentai, string failoKelias, bool &klaida);
void isvestEkr(const deque<Studentas> &studentai, int pasirink);
void isvestIFaila(const deque<Studentas> &studentai, int pasirink, string failoPav = "isvestis.txt");
void skaicGal(deque<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
string rndVardas(int from, int to);
void klauskEigos(bool &testi, Nustatymai &nustatymai);
void rusiuok(deque<Studentas> &studentai, int rusBudas);
string klauskFailo(bool &klaida);
void skirstyk(deque<Studentas> &studentai, deque<Studentas> &vargsiukai);
string kurkFaila(int studSk, int pazSk);