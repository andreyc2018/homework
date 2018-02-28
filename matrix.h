#pragma once

#include <map>
#include <array>

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
 *
 * Converts std::array to std::tuple
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

                Cell() : matrix_(nullptr), value_(Default) {}

                template<typename... Args,
                         typename std::enable_if_t<Dimension == sizeof...(Args), int> = 0>
                Cell(matrix_t* m, Args&&... args) : matrix_(m), value_(Default)
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

                /**
                 * @brief operator =()
                 * @param v
                 * @return return a reference to itself
                 *
                 * Inserts itself into matrix if not in the matrix and
                 * v is not Default
                 * Removes itself from the matrix if v is Default
                 */
                Cell& operator=(T v) {
                    value_ = v;
                    if (matrix_) {
                        if (matrix_->find(coordinates_)) {
                            matrix_->erase_if(coordinates_, v == Default);
                        }
                        else {
                            matrix_->insert_if(*this, v != Default);
                        }
                    }
                    return *this;
                }

                /**
                 * @brief operator T()
                 *
                 * Type conversion to T
                 */
                operator T() const { return value_; }

                /**
                 * @brief operator std::tuple<Args>()
                 *
                 * Type conversion to tuple
                 * Makes possible to read coordinates and value into a tuple
                 */
                template<typename... Args,
                         typename std::enable_if_t<Dimension+1 == sizeof...(Args), int> = 0>
                operator std::tuple<Args...> () {
                    auto coords = array_to_tuple(coordinates_);
                    return std::tuple_cat(coords, std::tie(value_));
                }

                bool operator< (const Cell& other) const {
                    return coordinates_ < other.coordinates_;
                }

                coords_t coordinates() const {
                    return coordinates_;
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
        using map_it_t = typename map_t::iterator;
        class iterator
        {
            public:
                using reference = cell_t&;

                iterator(map_it_t&& it) : it_(it) {}

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
                map_it_t it_;
        };

        Matrix() {}
        ~Matrix() {}

        size_t size() const { return matrix_.size(); }
        T default_value() const { return Default; }

        /**
         * @brief operator ()
         * @param coordinates
         * @return either new Cell or Cell from a matrix
         *
         * Multidimensional subscripting
         */
        template<typename... Args>
        typename std::enable_if_t<Dimension == sizeof...(Args), cell_t>
        operator() (Args&&... args)
        {
            coords_t coords = { { static_cast<int>(args)... } };
            auto it = matrix_.find(coords);
            if (it == matrix_.end()) {
                cell_t c(this, std::forward<Args>(args)...);
                return c;
            }
            return it->second;
        }

        iterator begin() { iterator it(matrix_.begin()); return it; }
        iterator end() { iterator it(matrix_.end()); return it; }

    private:
        map_t matrix_;

        void insert_if(cell_t& cell, bool condition) {
            if (condition)
                matrix_.insert(std::make_pair(cell.coordinates(), cell));
        }

        bool find(const coords_t& c) {
            auto it = matrix_.find(c);
            return it != matrix_.end();
        }

        void erase_if(const coords_t& c, bool condition) {
            if (condition)
                matrix_.erase(c);
        }
};
