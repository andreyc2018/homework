#pragma once

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

template<typename T>
void print_type(const char* msg, const T& v)
{
    int status;
    char* buffer = abi::__cxa_demangle(typeid(v).name(), nullptr, nullptr, &status);
    std::cout << msg << ": " << buffer << "\n";
    free(buffer);
}
