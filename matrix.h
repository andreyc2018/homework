#pragma once

#include <set>
#include <array>

namespace matrix
{

/**
 * @brief The Cell class
 *
 * Represents a cell in a matrix of dimension Dimension
 * Keeps it's own coordinates and a value
 */
template<typename T, int Dimension = 2>
class Cell
{
    public:
        using value_t = T;
        using cell_t = Cell<T, Dimension>;
        using coords_t = std::array<int, Dimension>;

        Cell() = default;

        template<typename... Args,
                 typename std::enable_if_t<Dimension == sizeof...(Args), int> = 0>
        Cell(Args&&... args)
        {
            set_coordinates(std::forward<Args>(args)...);
        }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), void>
        set_coordinates(Args&&... args)
        {
            coords_t coords = { { args... } };
            coordinates_.swap(coords);
        }

        cell_t& operator=(value_t v) noexcept { set_value(v); return *this; }

        void set_value(value_t v) { value_ = v; }
        T get_value() const { return value_; }

        bool operator< (const Cell& other) const
        {
            return coordinates_ < other.coordinates_;
        }

    private:
        coords_t coordinates_;
        value_t value_;
};

template<typename T, int Dimension, T Default>
class Matrix
{
    public:
        using value_t = T;
        using cell_t = Cell<T, Dimension>;

        Matrix();
        ~Matrix();

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), value_t>&
        operator[](Args&&... args)
        {
//            return mVector[idx];
        }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), const value_t>&
        operator[](Args&&... args) const
        {
//            return mVector[idx];
        }

    private:
        std::set<cell_t> matrix_;
};

}
