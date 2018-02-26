#pragma once

#include <set>
#include <map>
#include <array>
#include <stdexcept>
#include <iostream>

namespace matrix
{

/**
 * @brief array_to_tuple_helper
 * @param array
 * @returns std::tuple
 *
 * Helper to converts std::array to std::tuple using std::index_sequence
 */
template <typename A, std::size_t... Indices>
auto array_to_tuple_helper(A& array, std::index_sequence<Indices...>)
{
    return std::forward_as_tuple(array[Indices]...);
}

/**
 * @brief array_to_tuple
 * @param array
 * @returns std::tuple
 */
template <typename A>
auto array_to_tuple(A& array)
{
    return array_to_tuple_helper(array, std::make_index_sequence<array.size()>());
}

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
            coords_t coords { { static_cast<int>(args)... } };
            coordinates_.swap(coords);
        }

        Cell& operator=(value_t v) noexcept { set_value(v); return *this; }

        template<typename... Args,
                 typename std::enable_if_t<Dimension+1 == sizeof...(Args), int> = 0>
        operator std::tuple<Args...> () {
//            std::cout << __PRETTY_FUNCTION__ << "\n";
            auto coords = array_to_tuple(coordinates_);
            return std::tuple_cat(coords, std::tie(value_));
        }

        void set_value(value_t v) { value_ = v; }
        T get_value() const { return value_; }

        bool operator< (const Cell& other) const {
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
        using coords_t = std::array<int, Dimension>;
        using cell_t = Cell<value_t, Dimension>;
        using matrix_t = std::map<coords_t, cell_t>;
        class m_iterator
        {
            public:
                using map_it_t = typename matrix_t::iterator;
                using const_map_it_t = typename matrix_t::const_iterator;
                using iterator = m_iterator;
                using reference = cell_t&;

                m_iterator(const_map_it_t& it) : it_(it) {}

                reference operator*()
                {
                    return it_->second;
                }

                //! pre-increment
                iterator& operator++()
                {
                    it_++; return *this;
                }

                iterator& operator--()
                {
                    it_--; return *this;
                }

                //! post-increment
                iterator operator++(int)
                {
                    m_iterator tmp(it_);
                    ++it_;
                    return tmp;
                }

                iterator operator--(int)
                {
                    m_iterator tmp(it_);
                    --it_;
                    return tmp;
                }

                bool operator==(const iterator& b) const
                {
                    return it_->first == b.it_->first;
                }

                bool operator!=(const iterator& b) const
                {
                    return !(*this == b);
                }

                void set_it(const_map_it_t& it)
                {
                    it_ = it;
                }

            private:
                map_it_t& it_;
        };

        using iterator = m_iterator;
        using const_iterator = const iterator;

        Matrix() {}
        ~Matrix() {}

        size_t size() const {
            return matrix_.size();
        }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), value_t>
        get(Args&&... args)
        {
//            std::cout << __PRETTY_FUNCTION__ << "\n";
            coords_t coords = { { static_cast<int>(args)... } };
            auto it = matrix_.find(coords);
            if (it == matrix_.end()) {
                return Default;
            }
            return it->second.get_value();
        }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), void>
        set(value_t value, Args&&... args)
        {
//            std::cout << __PRETTY_FUNCTION__ << "\n";
            coords_t coords = { { static_cast<int>(args)... } };
            auto it = matrix_.find(coords);
            if (it != matrix_.end()) {
                if (value == Default) {
                    matrix_.erase(it);
                }
                else {
                    it->second.set_value(value);
                }
                return;
            }
            if (value == Default) {
                return;
            }
            cell_t c(std::forward<Args>(args)...);
            c.set_value(value);
            matrix_.insert(std::make_pair(coords, c));
        }

        iterator begin() noexcept {
            iterator it(matrix_.begin());
            return it;
        }

        const_iterator end() noexcept {
            const_iterator it(matrix_.end());
            return it;
        }

    private:
        matrix_t matrix_;
};

}
