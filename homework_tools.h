#pragma once

#include <iostream>
#include <vector>

namespace otus {

using byte = unsigned char;

/*! \brief Convert value to a vector of bytes
 */
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

/*! \brief Print original address presented a number
 */
template<typename T>
std::ostream& print_original(std::ostream& out, const T& ip)
{
    out << std::hex << ip;
    return out;
}

/*! \brief Print original address presented a number: specialization for <I>char</I>
 */
template<>
std::ostream& print_original<char>(std::ostream& out, const char& ip)
{
    return print_original(out, uint(ip));
}

/*! \brief Print original address presented a number: specialization for <I>unsigned char</I>
 */
template<>
std::ostream& print_original<unsigned char>(std::ostream& out, const unsigned char& ip)
{
    return print_original(out, uint(ip));
}

/*! \brief Print address presented a number
 */
template<typename T>
int print_ip(std::ostream& out, const T& ip)
{
    print_original(out, ip) << " --> ";
    std::vector<byte> bytes = to_bytes(ip);
    for (size_t i = 0; i < bytes.size(); ++i) {
        if (i != 0) {
            out << ".";
        }
        out << uint(bytes[i]);
    }
    out << std::dec << " --> ";
    for (size_t i = 0; i < bytes.size(); ++i) {
        if (i != 0) {
            out << ".";
        }
        out << uint(bytes[i]);
    }
    out << "\n";
    return 0;
}

}
