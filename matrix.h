#pragma once

#include <set>
#include <array>

namespace matrix
{

template<typename T, uint Dimension>
class Cell
{
    public:
        Cell();
        ~Cell();

        /// variadic set allows to set
        template<typename... Args>
        void set(T value, Args... dimensions)
        {

        }

    private:
        std::array<uint, Dimension> coordinates_;
        T value_;
};

template<typename T, int Dimension, int Default>
class Matrix
{
    public:
        Matrix();
        ~Matrix();

    private:
};

}
