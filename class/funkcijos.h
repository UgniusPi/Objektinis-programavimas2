/**
 * @file funkcijos.h
 * @brief Programos pagalbinės funkcijos: įvestis/išvestis, validacija, ir kt.
 */

#include <vector>
#include <string>
#include "strukturos.h"
#include "studentas.h"

using std::string;
using std::vector;

/**
 * @brief Įveda studentus iš ekrano arba juos sugeneruoja.
 * @param studentai Rezultatinis studentų vektorius (pridedami elementai).
 * @param rndPaz Ar generuoti tarpinius pažymius atsitiktinai.
 * @param rndVard Ar generuoti vardus/pavardes atsitiktinai.
 */
void ivestEkr(vector<Studentas> &studentai, bool rndPaz, bool rndVard);

/**
 * @brief Nuskaito studentų duomenis iš failo.
 * @param studentai Rezultatinis studentų vektorius.
 * @param failoKelias Įvesties failo kelias.
 * @param klaida Išeities parametras: true jei įvyko klaida.
 */
void ivestIsFailo(vector<Studentas> &studentai, string failoKelias, bool &klaida);

/** @brief Išveda studentus į ekraną. */
void isvestEkr(const vector<Studentas> &studentai, int pasirink);

/**
 * @brief Išsaugo studentų sąrašą į failą.
 * @param failoPav Pasirinktinai - išeities failo pavadinimas.
 */
void isvestIFaila(const vector<Studentas> &studentai, int pasirink, string failoPav = "isvestis.txt");

/** @brief Apskaičiuoja visų studentų galutinius balus. */
void skaicGal(vector<Studentas> &studentai, int pasirink);

/** @brief Tikrina ar eilutė yra sveikasis skaičius. */
bool isInt(string inp);

/** @brief Perskaito ir validuoja sveiką įvestį iš vartotojo. */
int validInput(string prompt);

/** @brief Validuoja įvestą skaičių intervale [from, to]. */
int validRange(int from, int to, string prompt);

/** @brief Tikrina tekstinio lauko ilgį ir grąžina galutinį tekstą. */
string validLength(int maxLength, string prompt);

/** @brief Sugeneruoja atsitiktinį vardą/pavardę nurodytu ilgio intervale. */
string rndVardas(int from, int to);

/**
 * @brief Užduoda vartotojui programos eigą ir užpildo `Nustatymai`.
 * @param testi Išeities parametras: ar tęsti programą.
 * @param nustatymai Išvedami pasirinkimai.
 */
void klauskEigos(bool &testi, Nustatymai &nustatymai);

/** @brief Rūšiuoja studentus pagal pasirinktą kriterijų. */
void rusiuok(vector<Studentas> &studentai, int rusBudas);

/**
 * @brief Leidžia vartotojui pasirinkti įvesties failą arba sugeneruoti naują.
 * @param klaida Išeities parametras: true jei įvyko klaida.
 * @return Grąžina pasirinkto failo kelią arba sugeneruoto failo kelią.
 */
string klauskFailo(bool &klaida);

/** @brief Atskiria į dvi grupes: silpnesnius ir stipresnius studentus. */
void skirstyk(vector<Studentas> &studentai, vector<Studentas> &vargsiukai);

/** @brief Sukuria atsitiktinį įvesties failą su nurodytu studentų ir pažymių skaičiumi. */
string kurkFaila(int studSk, int pazSk);