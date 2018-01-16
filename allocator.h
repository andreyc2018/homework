#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <typeinfo>
#include <cxxabi.h>

namespace otus {

template <typename T, size_t N>
class hw_allocator
{
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        template<typename U>
        struct rebind
        { using other = hw_allocator<U, N>; };

        hw_allocator() : i_(0), max_elements_(N), head_(nullptr) { }

        template<typename U>
        hw_allocator(const hw_allocator<U, N>&) : hw_allocator() { }

        ~hw_allocator()
        {
            ::operator delete(head_);
        }

        T* allocate(std::size_t n)
        {
            if (head_ == nullptr) {
                head_ = static_cast<T*>(::operator new(max_elements_ * sizeof (T)));
            }
            T* ptr = &(head_[i_]);
            i_ += n;
            return ptr;
        }

        void deallocate(T*, std::size_t)
        {
        }

        template <typename U, typename... Args>
        void construct(U* ptr, Args&&... args)
        {
            ::new(static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
        }

        template <typename U>
        void destroy(U* ptr)
        {
            ptr->~U();
        }

        size_t i() const { return i_; }
        size_t max_elements() const { return max_elements_; }
        T* head() const { return head_; }

    private:
        size_t i_;
        const size_t max_elements_;
        T* head_;
};

}
