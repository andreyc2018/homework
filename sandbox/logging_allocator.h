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
        T* t_ptr;
        print_type("\ndefault ctor: T t_ptr = ", *t_ptr);
        print_type("  default ctor: T this = ", *this);
    }

    logging_allocator(const logging_allocator<T>&)
    {
        T* t_ptr;
        print_type("\ncopy ctor: T t_ptr = ", *t_ptr);
        print_type("  copy ctor: T this = ", *this);
    }

    template<typename U>
    logging_allocator(const logging_allocator<U>&)
    {
        T* t_ptr;
        T* u_ptr;
        print_type("\ncopy ctor: U t_ptr = ", *t_ptr);
        print_type("  copy ctor: U u_ptr = ", *u_ptr);
        print_type("  copy ctor: U this = ", *this);
    }

    ~logging_allocator()
    {
        T* t_ptr;
        print_type("\ndtor: T t_ptr = ", *t_ptr);
        print_type("  dtor: T this = ", *this);
    }

    T* allocate(std::size_t n)
    {
        T* ptr = static_cast<T*>(::operator new(n * sizeof (T)));
        print_type("\nallocate: T ptr = ", *ptr);
        print_type("  allocate: T this = ", *this);
        return ptr;
    }

    void deallocate(T* ptr, std::size_t)
    {
        print_type("\ndeallocate: T ptr = ", *ptr);
        print_type("  deallocate: T this = ", *this);
        ::operator delete(ptr);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        T* t_ptr;
        print_type("\nconstruct: T t_ptr = ", *t_ptr);
        print_type("  construct: U ptr = ", *ptr);
        print_type("  construct: T this = ", *this);
        ::new(static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr)
    {
        T* t_ptr;
        print_type("\ndestroy: T t_ptr = ", *t_ptr);
        print_type("  destroy: U ptr = ", *ptr);
        print_type("  destroy: T this = ", *this);
        ptr->~U();
    }
};
