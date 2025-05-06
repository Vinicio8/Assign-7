#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace cs106l {

template <typename T> 
class unique_ptr {
private:
  T* ptr_;

public:
  explicit unique_ptr(T* ptr) : ptr_(ptr) {}
  unique_ptr(std::nullptr_t) : ptr_(nullptr) {}

  unique_ptr() : unique_ptr(nullptr) {}

  ~unique_ptr() {
    delete ptr_;
  }

  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;
  
  unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  // Asignación por movimiento
  unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a reference to the object.
   * @return A reference to the object.
   */
  T& operator*() {
    if (!ptr_) throw std::runtime_error("Dereferencing nullptr");
    return *ptr_;
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a const reference to the object.
   * @return A const reference to the object.
   */
  const T& operator*() const {
    if (!ptr_) throw std::runtime_error("Dereferencing nullptr");
    return *ptr_;
  }

  /**
   * @brief Returns a pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A pointer to the object.
   */
  T* operator->() {
    if (!ptr_) throw std::runtime_error("Accessing member of nullptr");
    return ptr_;
  }

  /**
   * @brief Returns a const pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A const pointer to the object.
   */
  const T* operator->() const {
    if (!ptr_) throw std::runtime_error("Accessing member of nullptr");
    return ptr_;
  }

  /**
   * @brief Returns whether or not the `unique_ptr` is non-null.
   * @note This allows us to use a `unique_ptr` inside an if-statement.
   * @return `true` if the `unique_ptr` is non-null, `false` otherwise.
   */
  operator bool() const {
    return ptr_ != nullptr;
  }

  T* release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  void reset(T* new_ptr = nullptr) {
    delete ptr_;
    ptr_ = new_ptr;
  }

  T* get() const {
    return ptr_;
  }
};

/**
 * @brief Creates a new unique_ptr for a type with the given arguments.
 * @example auto ptr = make_unique<int>(5);
 * @tparam T The type to create a unique_ptr for.
 * @tparam Args The types of the arguments to pass to the constructor of T.
 * @param args The arguments to pass to the constructor of T.
 */
template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}  
