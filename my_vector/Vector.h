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

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // Iterators
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type newCap);
    void shrink_to_fit();

    // Element access
    reference operator[](size_type idx);
    const_reference operator[](size_type idx) const;
    reference at(size_type idx);
    const_reference at(size_type idx) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    pointer data() noexcept;
    const_pointer data() const noexcept;
};
} // namespace mystl
