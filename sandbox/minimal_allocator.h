#pragma once

#include <iostream>

template<class T>
struct minimal_allocator
{
    using value_type = T;
    minimal_allocator()
    {
    }

    template<class U> minimal_allocator(minimal_allocator<U> const&) noexcept
    {
    }

    T* allocate(size_t n);
    void deallocate(T* p, size_t);
};

template<class T> bool
operator ==(minimal_allocator<T> const&, minimal_allocator<T> const&);

template<class T> bool
operator !=(minimal_allocator<T> const&, minimal_allocator<T> const&);
