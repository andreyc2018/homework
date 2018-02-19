#pragma once

#include <set>
#include <array>
#include <stdexcept>
#include <iostream>

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
                 typename std::enable_if_t<Dimension == sizeof...(Args), int> = 0>
        Cell(Args&&... args) : value_()
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
class Data
{
    public:
        using value_t = T;
        using data_t = Data<T, Dimension-1, Default>;

        Data() {}
        ~Data() {}

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
        std::set<data_t> data_;
};

template<typename T, int Dimension, T Default>
class Matrix
{
    public:
        using value_t = T;
        using data_t = Data<T, Dimension-1, Default>;

        Matrix() {}
        ~Matrix() {}

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), value_t>&
        operator[](Args&&... args)
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
//            return mVector[idx];
        }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), const value_t>&
        operator[](Args&&... args) const
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
//            return mVector[idx];
        }

    private:
        std::set<data_t> matrix_;
};

}
