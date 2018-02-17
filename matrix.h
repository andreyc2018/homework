#pragma once

#include <set>
#include <array>
#include <cstdint>

namespace matrix
{

/**
 */
template<typename T, int Dimension>
class Cell
{
    public:
        /// variadic set allows to set
        template<typename... Args>
        void set(T v, Args&&... args)
        {
            std::array<int, Dimension> coords = { { args... } };
            coordinates_.swap(coords);
            value_ = v;
        }

        T get() const { return value_; }

        bool operator< (const Cell& other) const
        {
            return coordinates_ == other.coordinates_ && value_ < other.value_;
        }
    private:
        std::array<uint8_t, Dimension> coordinates_;
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
