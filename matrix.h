#pragma once

#include <set>
#include <map>
#include <array>
#include <stdexcept>
#include <iostream>

#define TRACE()  std::cout << __PRETTY_FUNCTION__ << "\n"

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

template<typename T, int Dimension, T Default>
class Matrix
{
    public:
        using matrix_t = Matrix<T, Dimension, Default>;
        /**
         * @brief The Cell class
         *
         * Represents a cell in a matrix of dimension Dimension
         * Keeps it's own coordinates and a value
         */
        class Cell
        {
            public:
                using value_t = T;
                using coords_t = std::array<int, Dimension>;

                Cell() = default;

                template<typename... Args,
                         typename std::enable_if_t<Dimension == sizeof...(Args), int> = 0>
                Cell(matrix_t* m, Args&&... args) : matrix_(m), value_()
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

                Cell& operator=(T v) { TRACE();
                                       for (auto x : coordinates_) {
                                           std::cout << x << " ";
                                       }
                                       std::cout << "\n";
                                       value_ = v; return *this; }
                operator T() const { TRACE(); return value_; }

                template<typename... Args,
                         typename std::enable_if_t<Dimension+1 == sizeof...(Args), int> = 0>
                operator std::tuple<Args...> () {
                    auto coords = array_to_tuple(coordinates_);
                    return std::tuple_cat(coords, std::tie(value_));
                }

                void set_value(value_t v) { value_ = v; }
                T& get_value() { return value_; }

                bool operator< (const Cell& other) const {
                    return coordinates_ < other.coordinates_;
                }

            private:
                matrix_t* matrix_;
                coords_t coordinates_;
                value_t value_;
        };

    public:
        using value_t = T;
        using coords_t = std::array<int, Dimension>;
        using cell_t = Cell;
        using map_t = std::map<coords_t, cell_t>;
        class iterator
        {
            public:
                using map_it_t = typename map_t::iterator;
                using reference = cell_t&;

                iterator(map_it_t& it) : it_(it) {}

                reference operator*() { return it_->second; }

                //! pre-
                iterator& operator++() { it_++; return *this; }
                iterator& operator--() { it_--; return *this; }

                //! post-
                iterator operator++(int) { iterator tmp(it_); ++it_; return tmp; }
                iterator operator--(int) { iterator tmp(it_); --it_; return tmp; }

                //! equality
                bool operator==(const iterator& b) const { return it_->first == b.it_->first; }
                bool operator!=(const iterator& b) const { return !(*this == b); }

            private:
                map_it_t& it_;
        };

        using const_iterator = const iterator;

        Matrix() {}
        ~Matrix() {}

        size_t size() const { return matrix_.size(); }
        T default_value() const { return Default; }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), cell_t&>
        get(Args&&... args)
        {
            coords_t coords = { { static_cast<int>(args)... } };
            auto it = matrix_.find(coords);
            if (it == matrix_.end()) {
                cell_t c(*this, std::forward<Args>(args)...);
                matrix_.insert(std::make_pair(coords, c));
                return matrix_[coords];
            }
            return it->second;
        }

        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), void>
        set(value_t value, Args&&... args)
        {
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
            cell_t c(*this, std::forward<Args>(args)...);
            c.set_value(value);
            matrix_.insert(std::make_pair(coords, c));
        }

        iterator begin() noexcept { iterator it(matrix_.begin()); return it; }
        iterator end() noexcept { iterator it(matrix_.end()); return it; }

    private:
        map_t matrix_;
};
