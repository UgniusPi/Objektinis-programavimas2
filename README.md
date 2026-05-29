Sukurta kodo dokumentacija, kuri randasi aplanke "docs".

Ji buvo sugeneruota naudojant Doxygen, prieš tai kode pridėjus aprašus apie esamas klases, funkcijas, kintamuosius ir pan.

PDF dokumentacija buvo sukurta naudojant TinyTex kompiliatorių.

Unit testai

Projekte pridėti GoogleTest C++ unit testai. Testai yra faile `class/test_studentas_gtest.cpp` ir skirti patikrinti `Studentas` klasės elgesį (galutinio balo skaičiavimą, vidurkio/medianos atvejus ir kopijavimo/move semantikos - rule of five).

Testų rezultatai (lokaliai): 4 testai — visi praėjo (4/4).

Kaip paleisti testus (Windows PowerShell, iš repozitorijos šaknies):

1) (jei neturite) klonuokite ir bootstrap'inkite `vcpkg`:

```powershell
git clone https://github.com/microsoft/vcpkg.git vcpkg
.\vcpkg\bootstrap-vcpkg.bat
```

2) Įdiekite GoogleTest per `vcpkg` (rekomenduojamas statinis MinGW tripletas):

```powershell
.\vcpkg\vcpkg.exe install gtest:x64-mingw-static
```

3) Konfigūruokite ir surinkite projektą su `vcpkg` toolchain (Ninja):

```powershell
cmake -S class -B class/build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_BUILD_TYPE=Debug
cmake --build class/build --parallel
```

4) Paleiskite visus testus:

```powershell
ctest --test-dir class/build --output-on-failure
```

5) Arba paleiskite vykdomąjį tiesiai (filtravimas pagal testų vardą):

```powershell
.\class\build\studentas_gtest.exe --gtest_filter=StudentasTest.CopyAndMoveSemantics_RuleOfFive
```

Pastabos:
- Jei naudojate kitą kompiliatorių/toolchain (pvz. MSVC), pakeiskite `-DVCPKG_TARGET_TRIPLET` į atitinkamą tripletą (pvz. `x64-windows`).
- Jei pasirenkate dinaminį tripletą (pvz. `x64-mingw-dynamic`), užtikrinkite, kad reikalingi GoogleTest DLL būtų prieinami `PATH` arba nukopijuoti į vykdomąjį katalogą; kitaip testų vykdymas gali žlugti dėl trūkstamų DLL.
