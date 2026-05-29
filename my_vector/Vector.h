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

private:
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type cap_ = 0;

    // Destroy elements in range [first, last)
    void destroy_range(pointer first, pointer last) noexcept;

    // Allocate new storage and move elements
    void reallocate(size_type newCap);

public:
    // Constructors / destructor / assignment
    Vector() noexcept;
    explicit Vector(size_type count, const T& value = T());
    Vector(std::initializer_list<T> il);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();
};
};
} // namespace mystl
