#pragma once

#include "log_tools.h"

template<class T>
struct minimal_allocator
{
    using value_type = T;
    minimal_allocator()
    {
        print_type("default ctor: T this = ", *this);
    }

    template<class U> minimal_allocator(minimal_allocator<U> const& other) noexcept
    {
        print_type("copy ctor: U other = ", other);
        print_type("  default ctor: T this = ", *this);
    }

    T* allocate(size_t n)
    {
        T* ptr = static_cast<T*>(operator new(n * sizeof (T)));
        print_type("\nallocate: T ptr = ", *ptr);
        print_type("  allocate: T this = ", *this);
        return ptr;
    }

    void deallocate(T* ptr, size_t n)
    {
        print_type("\ndeallocate: T ptr = ", *ptr);
        print_type("  deallocate: T this = ", *this);
        operator delete(ptr, n);
    }
};

template<class T> bool
operator ==(minimal_allocator<T> const&, minimal_allocator<T> const&)
{
    return true;
}

template<class T> bool
operator !=(minimal_allocator<T> const& l, minimal_allocator<T> const& r)
{
    return !(l == r);
}
