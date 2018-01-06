#pragma once
#include <iostream>

struct xray
{
    xray() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    xray(const xray&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    xray(xray&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~xray() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    
    xray& operator=(const xray&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
    xray& operator=(xray&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
};
