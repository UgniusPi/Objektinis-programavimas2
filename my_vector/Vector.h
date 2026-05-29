#pragma once
#include <cstddef>
#include <initializer_list>
#include <string>

namespace mystl {

template<typename T>
class Vector {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
};
} // namespace mystl
