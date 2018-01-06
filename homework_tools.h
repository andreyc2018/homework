#pragma once

#include <iostream>
#include <vector>

namespace otus {

using byte = unsigned char;

template <typename T>
std::vector<byte> to_bytes(const T& value)
{
    std::vector<byte> bytes;
    bytes.reserve(sizeof (value));
    const byte* begin = reinterpret_cast<const byte*>(std::addressof(value));
    const byte* end = begin + sizeof(T);
    std::copy(begin, end, std::back_inserter(bytes));
    return bytes;
}

template<typename T>
void print_ip(std::ostream& out, const T& ip)
{
    std::vector<byte> bytes = to_bytes(ip);
    for (size_t i = 0; i < bytes.size(); ++i) {
        if (i != 0) {
            out << ".";
        }
        out << uint(bytes[i]);
    }
}

}
