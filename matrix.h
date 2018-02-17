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
template<typename T, size_t Dimension = 2>
class Cell
{
    public:
        using value_t = T;
        using cell_t = Cell<T, Dimension>;

        Cell() = default;

        template<typename... Args,
                 typename std::enable_if_t<Dimension == sizeof...(Args), size_t> = 0>
        Cell(Args&&... args) : Cell(T(), std::forward<Args>(args)...) {}

        template<typename... Args,
                 typename std::enable_if_t<Dimension == sizeof...(Args), size_t> = 0>
        Cell(value_t v, Args&&... args)
        {
            set_value(v);
            set_coordinates(std::forward<Args>(args)...);
        }

        template<typename... Args,
                 typename std::enable_if_t<Dimension == sizeof...(Args), size_t> = 0>
        void set_coordinates(Args&&... args)
        {
            std::array<size_t, Dimension> coords = { { args... } };
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
        std::array<size_t, Dimension> coordinates_;
        value_t value_;
};

template<typename T, size_t Dimension, T Default>
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
