**Vector Konteineris (mystl::Vector) — ataskaita**

Pridėta paprasta `mystl::Vector` šabloninė klasė, skirta imituoti `std::vector` pagrindinį API. Kataloge `my_vector` yra:
- `Vector.h` — implementacija.
- `vector_examples.cpp` — palyginamieji pavyzdžiai, kurie atlieka tas pačias operacijas su `std::vector` ir `mystl::Vector` ir palygina rezultatus.

Toliau pateikiami bent 5 funkcijų pavyzdžiai (kodas yra `my_vector/vector_examples.cpp`):

- **`push_back`**: įdeda elementą į vektoriaus galą.
	- Pavyzdys: su `std::vector<int>` ir `mystl::Vector<int>` įdedami skaičiai 1,2,3; patikrinama `size()` ir turinys.

- **`emplace_back`**: konstruktoriaus argumentai perduodami tiesiai naujam elementui sukurti (in-place).
	- Pavyzdys: su struktūra `Person` sukuriami du objektai `("Alice",30)` ir `("Bob",25)` be papildomų kopijų.

- **`insert` / `erase`**: įterpimas viduryje ir elemento pašalinimas.
	- Pavyzdys: pradinis masyvas `{1,3,4}` → `insert(begin()+1,2)` → `{1,2,3,4}`, tada `erase(begin()+2)` → `{1,2,4}`; rezultatai sutampa abiem konteineriams.

- **`reserve` / `capacity`**: išankstinis vietos rezervavimas ir talpos tikrinimas.
	- Pavyzdys: `reserve(16)` tiek `std::vector`, tiek `mystl::Vector` atnaujina `capacity()` į 16.

- **`resize`**: keičiama vektoriaus dydis mažinant arba didinant (su užpildymo reikšme).
	- Pavyzdys: `{1,2,3,4,5}` → `resize(3)` → `{1,2,3}`; vėliau `resize(6,9)` → `{1,2,3,9,9,9}`. Abiejų konteinerių elgesys sutampa.

Taip pat pademonstruoti ir patikrinti: kopijavimo / perkelimo konstruktoriai, `assign`, `swap`, `operator[]` ir `at()`.

Kaip paleisti palyginimus (Windows PowerShell, repozitorijos šakninis katalogas):

```powershell
g++ -std=c++17 -O2 my_vector/vector_examples.cpp -o my_vector/vector_examples.exe
.\my_vector\vector_examples.exe
```

Programos išvestis praneš apie kiekvieną patikrą (`OK` / `FAIL`) ir baigiamąją eilutę `ALL TESTS PASSED` arba `SOME TESTS FAILED`.

**Veikimo spartos palyginimas (benchmark)**

- **Metodika:** Programos sukurtos ir vykdytos su kompiliatoriaus išvestimi: `g++.exe (MinGW-W64) 15.2.0`. Kompiliavimo vėliavėlės: `-std=c++17 -O2`. Laiko matavimams naudotas `std::chrono::steady_clock`. Kiekvienam dydžiui atlikti po 3 bandymus, imtas vidurkis. Prieš `push_back()` nebuvo kviečiamas `reserve()` (t. y. realokacijos vyko natūraliai).
- **Kodas:** [my_vector/bench_vector.cpp](my_vector/bench_vector.cpp)
- **Kompiliavimas ir paleidimas:**

```powershell
g++ -std=c++17 -O2 my_vector/Vector.cpp my_vector/bench_vector.cpp -o my_vector/bench_vector.exe
.\my_vector\bench_vector.exe
```

Vidutiniai `push_back` laikai (milisekundėmis) — tuščių vektorių užpildymas N `int` elementų naudojant `push_back()` (3 bandymų vidurkis):

| Elementų skaičius | std::vector (ms) | mystl::Vector (ms) | Santykis (mystl / std) |
|---:|---:|---:|---:|
| 10 000 | 0.087 | 0.106 | 1.22x |
| 100 000 | 0.466 | 0.689 | 1.48x |
| 1 000 000 | 3.276 | 6.331 | 1.93x |
| 10 000 000 | 41.473 | 73.755 | 1.78x |
| 100 000 000 | 289.821 | 595.483 | 2.05x |

**Komentarai / analizė:**
- `mystl::Vector` šiuose testuose sistemingai veikia lėčiau nei `std::vector`; lėtinimo faktorius svyruoja maždaug nuo 1.2x iki 2.1x priklausomai nuo dydžio.

**Pagrindinės priežastys:**
- Trivialiems tipams (pvz., `int`) standartinės bibliotekos implementacijos dažnai naudoja žemo lygio optimizacijas atminties perkėlimui (pvz., `memcpy`/`memmove` arba specifiškus allocatoriaus sprendimus) realokuodamos buferį; mūsų `Vector` perkėlė elementus po vieną (placement-new + destruktorius), kas yra lėčiau.
- Skirtingos talpos didinimo ir allocatoriaus strategijos: `std::vector` diegimai gali turėti papildomų optimizacijų ir geriau pritaikytų strategijų, tuo tarpu paprasta dvigubinimo politika ir vienetinis perkėlimas mūsų implementacijoje prideda overhead'o.

**Praktinės pasekmės:**
- Jei dirbate su trivialesniais tipais ir jums svarbi maksimalus greitis, rekomenduojama naudoti `std::vector` arba pridėti optimizacijas į `mystl::Vector`.
- Paprasta optimizacija: aptikti `std::is_trivially_move_constructible<T>::value` arba `std::is_trivially_copyable` ir trivialesems tipams naudoti `std::memmove`/`std::memcpy` arba `std::uninitialized_copy_n` vietoje elementų perkėlimo vienas po kito.

Jei norite, galiu:
- Įdiegti optimizuotą kelią `my_vector/Vector.cpp` triviales tipams (naudojant `memmove`) ir vėl paleisti benchmark'ą.
- Pridėti benchmark kaip `CMake` tikslą, kad būtų lengva paleisti ir kituose aplinkose.

**Perskirstymų skaičiaus palyginimas (100 000 000 elementų)**

- **Užduotis:** Palyginti, kiek kartų vyksta atminties perskirstymai (`realloc` įvykiai) `užpildant konteinerį 100 000 000 `int` elementų, kai perskirstymas skaičiuojamas kaip įvykis, kai prieš `push_back()` tenkinama sąlyga `capacity() == size()`.
- **Kodas:** [my_vector/realloc_count.cpp](my_vector/realloc_count.cpp) — prieš kiekvieną `push_back()` tikrinamas `capacity() == size()` ir jei sąlyga tenkinama, skaičiuojamas perskirstymas.
- **Kompiliavimas ir paleidimas:**

```powershell
g++ -std=c++17 -O2 my_vector/Vector.cpp my_vector/realloc_count.cpp -o my_vector/realloc_count.exe
.\my_vector\realloc_count.exe
```

**Rezultatai (vienkartinis paleidimas, N = 100000000):**

```
Counting reallocations for N=100000000
std::vector: reallocations=28, time_ms=409.863
mystl::Vector: reallocations=28, time_ms=970.929
```

**Paaiškinimas ir išvados:**
- Abi implementacijos užfiksavo vienodą perskirstymų skaičių — **28**. Tai reiškia, kad talpos didinimo strategija (čia — dvigubinimas: `cap = cap ? cap*2 : 1`) lemia perskirstymų dažnį, nepriklausomai nuo to, kaip elementai yra perkelti į naują buferį.
- Laiko skirtumas (mystl::Vector žymiai lėtesnis) kyla dėl el. perkėlimo būdo: `std::vector` diegimas gali naudoti optimizuotus žemo lygio operacijų (pvz., `memcpy`/`memmove` trivialiems tipams arba kitus optimizavimo priemonių), tuo tarpu mūsų `mystl::Vector` realokacijos metu perkelia elementus po vieną per placement-new ir iškviečia destruktorius, kas yra lėčiau.
- Išvados:
	- Jei jus domina tik perskirstymų skaičius, abu konteineriai elgiasi vienodai (tame pačiame augimo modelyje).
	- Jei jus domina ir veikimo trukmė, `std::vector` vis dar pranašesnis dėl papildomų optimizacijų.




