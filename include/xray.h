#pragma once
#include <iostream>

#define xtrace()  std::cout << __PRETTY_FUNCTION__ << "\n"
struct xray
{
    xray() { xtrace(); }
    xray(const xray&) { xtrace(); }
    xray(xray&&) { xtrace(); }
    ~xray() { xtrace(); }
    
    xray& operator=(const xray&) { xtrace(); return *this; }
    xray& operator=(xray&&) { xtrace(); return *this; }

    bool operator==(const xray&) const { xtrace(); return true; }
};
