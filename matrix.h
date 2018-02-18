#pragma once

#include <set>
#include <array>
#include <iostream>

namespace details
{
template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;
}

template<bool B, class T = void>
using enable_if_t = details::enable_if_t<B, T>;

namespace matrix
{

template<typename T>
class CellData
{
    public:
        using value_t = T;
        using data_t = CellData<T>;

        void set_value(T&& v) { std::move(value_, v); }
        T value() const { return value_; }

        data_t& operator=(value_t v) noexcept { set_value(v); return *this; }

    private:
        T value_;
};
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
                 typename ::enable_if_t<Dimension == sizeof...(Args), int> = 0>
        Cell(Args&&... args) : value_()
        {
            set_coordinates(std::forward<Args>(args)...);
        }

        template<typename... Args>
        typename ::enable_if_t<Dimension == sizeof...(Args), void>
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

template<typename T>
class DataPlane
{
    public:
        DataPlane() {}
        ~DataPlane() {}

        T& operator[](size_t idx)
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            return data_.find(idx);
        }

        const T& operator[](size_t idx) const
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            return data_.find(idx);
        }

    private:
        std::set<T> data_;
};

template<typename T, int Dimension, T Default>
class Matrix
{
    public:
        using value_t = T;
        using cell_t = Cell<T, Dimension>;

        Matrix() {}
        ~Matrix() {}

        template<typename... Args>
        typename ::enable_if_t<Dimension == sizeof...(Args), value_t>&
        operator[](Args&&... args)
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
//            return mVector[idx];
        }

        template<typename... Args>
        typename ::enable_if_t<Dimension == sizeof...(Args), const value_t>&
        operator[](Args&&... args) const
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
//            return mVector[idx];
        }

    private:
        std::set<cell_t> matrix_;
};

}
