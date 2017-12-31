#pragma once

#include "log_tools.h"
#include <memory>

template <typename T>
struct logging_allocator
{
    using value_type = T;

    template<typename U>
    struct rebind
    { using other = logging_allocator<U>; };

    std::allocator<T> alloc;

    logging_allocator()
    {
        T* head_;
        print_type("\ndefault ctor: T head = ", *head_);
        print_type("  default ctor: T this = ", *this);
    }

    ~logging_allocator()
    {
        T* head_;
        print_type("\ndtor: T head = ", *head_);
        print_type("  dtor: T this = ", *this);
    }

    T* allocate(std::size_t n)
    {
        T* ptr = alloc.allocate(n);
        print_type("\nallocate: T ptr = ", *ptr);
        print_type("  allocate: T this = ", *this);
        return ptr;
    }

    void deallocate(T* ptr, std::size_t n)
    {
        print_type("\ndeallocate: T ptr = ", *ptr);
        print_type("  deallocate: T this = ", *this);
        alloc.deallocate(ptr, n);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        T* head_;
        print_type("\nconstruct: T head = ", *head_);
        print_type("  construct: U ptr = ", *ptr);
        print_type("  construct: T this = ", *this);
        alloc.construct(ptr, std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr)
    {
        T* head_;
        print_type("\ndestroy: T head = ", *head_);
        print_type("  destroy: U ptr = ", *ptr);
        print_type("  destroy: T this = ", *this);
        alloc.destroy(ptr);
    }
};
