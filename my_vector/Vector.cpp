#include "Vector.h"
#include <new>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

namespace mystl {

template<typename T>
void Vector<T>::destroy_range(pointer first, pointer last) noexcept {
    while (first != last) {
        (--last)->~T();
    }
}

template<typename T>
void Vector<T>::reallocate(size_type newCap) {
    pointer newData = static_cast<pointer>(::operator new(sizeof(T) * newCap));
    for (size_type i = 0; i < size_; ++i) {
        new (newData + i) T(std::move_if_noexcept(data_[i]));
        data_[i].~T();
    }
    ::operator delete(data_);
    data_ = newData;
    cap_ = newCap;
}

// Constructors / destructor / assignment
template<typename T>
Vector<T>::Vector() noexcept = default;

template<typename T>
Vector<T>::Vector(size_type count, const T& value) {
    reserve(count);
    for (size_type i = 0; i < count; ++i)
        new (data_ + i) T(value);
    size_ = count;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> il) {
    reserve(il.size());
    for (const T &v : il)
        new (data_ + size_++) T(v);
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
    reserve(other.size_);
    for (size_type i = 0; i < other.size_; ++i)
        new (data_ + i) T(other.data_[i]);
    size_ = other.size_;
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), cap_(other.cap_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
}

template<typename T>
Vector<T>::~Vector() {
    clear();
    ::operator delete(data_);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) return *this;
    clear();
    reserve(other.size_);
    for (size_type i = 0; i < other.size_; ++i)
        new (data_ + i) T(other.data_[i]);
    size_ = other.size_;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) return *this;
    clear();
    ::operator delete(data_);
    data_ = other.data_;
    size_ = other.size_;
    cap_ = other.cap_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
    return *this;
}
} // namespace mystl
