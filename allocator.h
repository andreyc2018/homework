#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <typeinfo>
#include <cxxabi.h>

#define CAST(x)  static_cast<hw_allocator<T, N>>(x)

template<typename T>
void print_type(const char* msg, const T& v)
{
    int status;
    char* buffer = abi::__cxa_demangle(typeid(v).name(), nullptr, nullptr, &status);
    std::cout << msg << ": " << buffer << "\n";
    free(buffer);
}

namespace otus {

template <typename T, size_t N>
class hw_allocator
{
    public:
        using value_type = T;
        using pointer = T*;

        template<typename U>
        struct rebind
        { using other = hw_allocator<U, N>; };

        hw_allocator()
            : i_(0), max_elements_(N), head_(nullptr), copy_(false)
        {
            print_type("\ndefault ctor: T head = ", *head_);
            print_type("  default ctor: T this = ", *this);
        }

        hw_allocator(const hw_allocator<T, N>& other)
            : i_(other.i())
            , max_elements_(other.max_elements())
            , head_(other.head())
            , copy_(true)
        {
            print_type("\ncopy ctor: T head = ", *head_);
            print_type("  copy ctor: T other = ", other);
            print_type("  copy ctor: T this = ", *this);
        }

        template<typename U>
        hw_allocator(const hw_allocator<U, N>& other)
        {
            print_type("\ncopy ctor U: T head = ", *head_);
            print_type("  copy ctor U: U other = ", other);
            print_type("  copy ctor U: T this = ", *this);
        }

        ~hw_allocator()
        {
            print_type("\ndtor: T head = ", *head_);
            print_type("  dtor: T this = ", *this);
            if (!copy_)
                free(head_);
        }

        pointer allocate(std::size_t n)
        {
            if (head_ == nullptr) {
                head_ = static_cast<T*>(malloc(max_elements_ * sizeof (T)));
            }
            pointer ptr = &(head_[i_]);
            i_ += n;
            print_type("\nallocate: T ptr = ", *ptr);
            print_type("  allocate: T this = ", *this);
            return ptr;
        }

        void deallocate(pointer ptr, std::size_t)
        {
            print_type("\ndeallocate: T head = ", *head_);
            print_type("  deallocate: T ptr = ", *ptr);
            print_type("  deallocate: T this = ", *this);
        }

        template <typename U, typename... Args>
        void construct(U* ptr, Args&&... args)
        {
            print_type("\nconstruct: T head = ", *head_);
            print_type("  construct: U ptr = ", *ptr);
            print_type("  construct: T this = ", *this);
            ::new(static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
        }

        template <typename U>
        void destroy(U* ptr)
        {
            print_type("\ndestroy: T head = ", *head_);
            print_type("  destroy: U ptr = ", *ptr);
            print_type("  destroy: T this = ", *this);
            ptr->~U();
        }

        size_t i() const { return i_; }
        size_t max_elements() const { return max_elements_; }
        pointer head() const { return head_; }

    private:
        size_t i_;
        const size_t max_elements_;
        pointer head_;
        bool copy_;
};

}
