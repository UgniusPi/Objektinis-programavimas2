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
} // namespace mystl
