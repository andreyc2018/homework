#pragma once

#include <iostream>
#include <memory>

template <typename T>
struct logging_allocator
{
    using value_type = T;

    template<typename U>
    struct rebind
    { using other = logging_allocator<U>; };

    std::allocator<T> alloc;

    T* allocate(std::size_t n)
    {
        T* ptr = alloc.allocate(n);
        std::cerr << "allocate  : " << n << " " << ptr << "\n";
        return ptr;
    }

    void deallocate(T* ptr, std::size_t n)
    {
        std::cerr << "deallocate: " << n << " " << ptr << "\n";
        alloc.deallocate(ptr, n);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        std::cerr << "construct : " << ptr << " with " << sizeof...(args) << " args\n";
        alloc.construct(ptr, std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr)
    {
        std::cerr << "destroy   : " << ptr << "\n";
        alloc.destroy(ptr);
    }
};
