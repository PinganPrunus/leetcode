/**
 * @file dynamic_array.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-03-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_ALGORITHMS_DYNAMIC_H_
#define LEETCODE_ALGORITHMS_DYNAMIC_H_

#include <cstddef>
#include <cstring>
#include <sstream>
#include <string>

namespace datastructures {
template <typename T>
class DynamicArray final {
 public:
  DynamicArray(std::size_t capacity = 2)
      : capacity_(capacity), size_(0), objects_(new T[capacity]){};

  ~DynamicArray() { delete[] objects_; }

  std::size_t GetSize() const { return size_; }

  bool IsEmpty() { return size_ == 0; }

  void Append(T const& value) {
    if (IsFull()) {
      Expand();
    }
    objects_[size_++] = value;
  }

  void Remove() {
    --size_;
    if (IsSparse()) {
      Shrink();
    }
  }

  T Head() const { return operator[](0); };

  T Tail() const { return operator[](size_ - 1); };

  std::string ToString() const {
    std::stringstream sstream;
    sstream << "[";
    for (std::size_t idx = 0; idx < size_; ++idx) {
      sstream << objects_[idx];
      if (idx + 1 < size_) {
        sstream << ", ";
      }
    }
    sstream << "]";
    return sstream.str();
  };

  T const& operator[](std::size_t index) const {
    if (index >= size_) {
      std::abort();
    }
    return objects_[index];
  };

  T& operator[](std::size_t index) {
    if (index >= size_) {
      std::abort();
    }
    return objects_[index];
  };

 private:
  bool IsFull() const { return size_ == capacity_; }

  void Expand() {
    T* old = objects_;
    std::size_t old_capacity = capacity_;
    capacity_ <<= 1;
    objects_ = new T[capacity_];
    std::memcpy(objects_, old, old_capacity * sizeof(T));
    delete[] old;
  }

  bool IsSparse() { return size_ < capacity_ >> 1; }

  void Shrink() {
    T* old = objects_;
    capacity_ >>= 1;
    objects_ = new T[capacity_];
    std::memcpy(objects_, old, capacity_ * sizeof(T));
    delete[] old;
  }

  std::size_t capacity_;
  std::size_t size_;
  T* objects_;
};
}  // namespace datastructures

#endif