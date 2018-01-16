#pragma once
#include <iostream>

template <typename T>
struct xray
{
    xray() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    xray(const T& v) : value(v) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    xray(const xray&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    xray(xray&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~xray() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    
    xray& operator=(const xray&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
    xray& operator=(xray&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }

    T value;
};
