#include "homework_tools.h"
#include <iostream>

template <int N>
struct Factorial { enum { value = N * Factorial<N - 1>::value }; };

template <>
struct Factorial<0> { enum { value = 1 }; };

int otus::factorial(int n)
{
    static int data[otus::MaxElements] = {
            Factorial<0>::value,
            Factorial<1>::value,
            Factorial<2>::value,
            Factorial<3>::value,
            Factorial<4>::value,
            Factorial<5>::value,
            Factorial<6>::value,
            Factorial<7>::value,
            Factorial<8>::value,
            Factorial<9>::value
    };
    return data[n];
}
