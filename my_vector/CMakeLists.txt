cmake_minimum_required(VERSION 3.14)
project(my_vector_app LANGUAGES CXX) # Pakeičiau pavadinimą į app

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Sukuriam pačią programą (pridėk savo main.cpp, jei tokį turi!)
add_executable(mano_vektorius
    Vector.cpp
    input.cpp
    output.cpp
    studentas.cpp
    main.cpp  # <-- Čia turėtų būti tavo pagrindinis programos failas
)

target_include_directories(mano_vektorius PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ==========================================
# CPACK KONFIGŪRACIJA (INSTALLERIS)
# ==========================================

# 2. Nurodome MSI formatą
set(CPACK_GENERATOR "WIX")

# 3. Svarbu: Pakeičiau į "mano_vektorius", kad sutaptų su add_executable!
install(TARGETS mano_vektorius DESTINATION bin)

# 4. Paleidžiame CPack
include(CPack)