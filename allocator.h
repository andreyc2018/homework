#pragma once

#include <iostream>
#include <memory>

template <typename T, int N>
struct hw_allocator
{
    using value_type = T;

    template<typename U>
    struct rebind
    { using other = hw_allocator<U, N>; };

    size_t i;
    const size_t max_elements;

    T* head_;

    hw_allocator() : i(0), max_elements(N), head_(nullptr)
    {
        std::cerr << "ctor: hw_allocator() i = " << i
                  << " max = " << max_elements << "\n";
    }

    ~hw_allocator()
    {
        std::cerr << "dtor: ~hw_allocator() i = " << i
                  << " max = " << max_elements
                  << " head = " << head_ << "\n";
        free(head_);
    }

    T* allocate(std::size_t n)
    {
        if (head_ == nullptr) {
            head_ = static_cast<T*>(malloc(max_elements * sizeof (T)));
        }
        std::cerr << "i = " << i << " max = " << max_elements
                  << " head = " << head_ << "\n";
        T* ptr = &(head_[i++]);
        std::cerr << "allocate  : " << n << " " << ptr
                  << " ptr - head = " << ptr - head_ << "\n";
        return ptr;
    }

    void deallocate(T* ptr, std::size_t n)
    {
        std::cerr << "deallocate: " << n << " " << ptr << "\n";
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        std::cerr << "construct : " << ptr << " with " << sizeof...(args) << " args\n";
        ::new(static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr)
    {
        std::cerr << "destroy   : " << ptr << "\n";
        ptr->~U();
    }
};
