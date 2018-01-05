#pragma once
#include <iostream>

struct xray
{
    xray() : name("xray") { std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; }
    xray(const char* n) : name(n) { std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; }
    xray(const xray& other) : name(other.name) { std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; }
    xray(xray&& other) : name(other.name) { std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; }
    ~xray() { std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; }
    
    xray& operator=(const xray& other) { name = other.name; std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; return *this; }
    xray& operator=(xray&& other) { name = other.name; std::cout << __PRETTY_FUNCTION__ << " " << name << "\n"; return *this; }
    const char* name;
};
