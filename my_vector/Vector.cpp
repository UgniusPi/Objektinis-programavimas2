#include "Vector.h"
#include <new>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <filesystem>
#include "studentas.h"

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

// Iterators
template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept { return data_; }

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept { return data_ + size_; }

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept { return data_; }

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept { return data_ + size_; }

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept { return data_; }

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept { return data_ + size_; }

// Capacity
template<typename T>
bool Vector<T>::empty() const noexcept { return size_ == 0; }

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept { return size_; }

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept { return cap_; }

template<typename T>
void Vector<T>::reserve(size_type newCap) {
    if (newCap <= cap_) return;
    reallocate(newCap);
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (cap_ > size_) {
        if (size_ == 0) {
            ::operator delete(data_);
            data_ = nullptr;
            cap_ = 0;
        } else {
            reallocate(size_);
        }
    }
}

// Element access
template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type idx) { return data_[idx]; }

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type idx) const { return data_[idx]; }

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_type idx) {
    if (idx >= size_) throw std::out_of_range("Vector::at");
    return data_[idx];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type idx) const {
    if (idx >= size_) throw std::out_of_range("Vector::at");
    return data_[idx];
}

template<typename T>
typename Vector<T>::reference Vector<T>::front() { return data_[0]; }

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const { return data_[0]; }

template<typename T>
typename Vector<T>::reference Vector<T>::back() { return data_[size_ - 1]; }

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const { return data_[size_ - 1]; }

template<typename T>
typename Vector<T>::pointer Vector<T>::data() noexcept { return data_; }

template<typename T>
typename Vector<T>::const_pointer Vector<T>::data() const noexcept { return data_; }

// Modifiers
template<typename T>
void Vector<T>::clear() noexcept {
    destroy_range(data_, data_ + size_);
    size_ = 0;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == cap_) reserve(cap_ ? cap_ * 2 : 1);
    new (data_ + size_) T(value);
    ++size_;
}

template<typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == cap_) reserve(cap_ ? cap_ * 2 : 1);
    new (data_ + size_) T(std::move(value));
    ++size_;
}

template<typename T>
template<class... Args>
void Vector<T>::emplace_back(Args&&... args) {
    if (size_ == cap_) reserve(cap_ ? cap_ * 2 : 1);
    new (data_ + size_) T(std::forward<Args>(args)...);
    ++size_;
}

template<typename T>
void Vector<T>::pop_back() {
    if (size_ == 0) return;
    --size_;
    data_[size_].~T();
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T& value) {
    size_type idx = pos - data_;
    if (idx > size_) idx = size_;
    if (size_ == cap_) reserve(cap_ ? cap_ * 2 : 1);
    for (size_type i = size_; i > idx; --i) {
        new (data_ + i) T(std::move(data_[i - 1]));
        data_[i - 1].~T();
    }
    new (data_ + idx) T(value);
    ++size_;
    return data_ + idx;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
    size_type idx = pos - data_;
    if (idx >= size_) return end();
    data_[idx].~T();
    for (size_type i = idx; i < size_ - 1; ++i) {
        new (data_ + i) T(std::move(data_[i + 1]));
        data_[i + 1].~T();
    }
    --size_;
    return data_ + idx;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last) {
    size_type idx1 = first - data_;
    size_type idx2 = last - data_;
    if (idx1 >= size_ || idx1 >= idx2) return data_ + idx1;
    size_type count = idx2 - idx1;
    for (size_type i = 0; i < count; ++i)
        data_[idx1 + i].~T();
    for (size_type i = idx1; i + count < size_; ++i) {
        new (data_ + i) T(std::move(data_[i + count]));
        data_[i + count].~T();
    }
    size_ -= count;
    return data_ + idx1;
}

template<typename T>
void Vector<T>::resize(size_type count) {
    if (count < size_) {
        for (size_type i = count; i < size_; ++i)
            data_[i].~T();
        size_ = count;
    } else if (count > size_) {
        reserve(count);
        for (size_type i = size_; i < count; ++i)
            new (data_ + i) T();
        size_ = count;
    }
}

template<typename T>
void Vector<T>::resize(size_type count, const T& value) {
    if (count < size_) {
        for (size_type i = count; i < size_; ++i)
            data_[i].~T();
        size_ = count;
    } else if (count > size_) {
        reserve(count);
        for (size_type i = size_; i < count; ++i)
            new (data_ + i) T(value);
        size_ = count;
    }
}

template<typename T>
void Vector<T>::assign(size_type count, const T& value) {
    clear();
    reserve(count);
    for (size_type i = 0; i < count; ++i)
        new (data_ + i) T(value);
    size_ = count;
}

template<typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
}

// Non-member comparisons
template<typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (typename Vector<T>::size_type i = 0; i < a.size(); ++i)
        if (!(a.data()[i] == b.data()[i])) return false;
    return true;
}

template<typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b) {
    return !(operator==(a, b));
}

// Explicit instantiations for types used in examples/tests
template class Vector<int>;
template bool operator==<int>(const Vector<int>&, const Vector<int>&);
template bool operator!=<int>(const Vector<int>&, const Vector<int>&);

template class Vector<std::string>;
template bool operator==<std::string>(const Vector<std::string>&, const Vector<std::string>&);
template bool operator!=<std::string>(const Vector<std::string>&, const Vector<std::string>&);

template class Vector<Item>;
template bool operator==<Item>(const Vector<Item>&, const Vector<Item>&);
template bool operator!=<Item>(const Vector<Item>&, const Vector<Item>&);

// Explicit instantiations for project-specific types used in my_vector
template class Vector<std::filesystem::path>;
template bool operator==<std::filesystem::path>(const Vector<std::filesystem::path>&, const Vector<std::filesystem::path>&);
template bool operator!=<std::filesystem::path>(const Vector<std::filesystem::path>&, const Vector<std::filesystem::path>&);

template class Vector<Studentas>;

// Explicitly instantiate member-template emplace_back for the usage in examples
template void Vector<Item>::emplace_back<std::string,int>(std::string&&, int&&);

} // namespace mystl
