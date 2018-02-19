#include "matrix.h"
#include <map>
#define BOOST_TEST_MODULE Matrix
#include <boost/test/unit_test.hpp>
#include <iostream>

using matrix::Cell;
using matrix::Matrix;

BOOST_AUTO_TEST_CASE(init)
{
    Cell<int> c1(1, 1);
    c1.set_value(10);

    Cell<int> c2(1, 1);
    c2.set_value(10);

// error: no matching function for call to ‘matrix::Cell<int, 3>::set(int, int, int)’
//    constexpr int Dimension = 3;
//    Cell<int, 3> c3;
//    int value = 11;
//    int x = 1, y = 1, z = 0;
//    c3.set(value, x, y); Number of coordinates is less than a dimension

    BOOST_CHECK(!(c1 < c2));

    Cell<int> c4(0, 0);
    c4.set_value(12);
    BOOST_CHECK(c4 < c1);
}

BOOST_AUTO_TEST_CASE(add_to_set)
{
    constexpr int Dimension = 2;
    using cell_t = Cell<int, Dimension>;
    std::set<cell_t> matrix;

    cell_t c1;
    c1.set_coordinates(1, 1);
    c1.set_value(10);

    cell_t c2(1, 1);
    c2.set_value(11);

    auto rc = matrix.insert(c1);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(1, matrix.size());
    BOOST_CHECK_EQUAL(c1.get_value(), rc.first->get_value());

    rc = matrix.insert(c2);
    BOOST_CHECK(!rc.second);
    BOOST_CHECK_EQUAL(1, matrix.size());
    BOOST_CHECK_EQUAL(c1.get_value(), rc.first->get_value());

    cell_t c3(1, 1);
    BOOST_CHECK_EQUAL(0, c3.get_value());
    auto it = matrix.find(c3);
    BOOST_CHECK_EQUAL(c1.get_value(), it->get_value());
}

BOOST_AUTO_TEST_CASE(assignment)
{
    constexpr int Dimension = 2;
    using cell_t = Cell<int, Dimension>;

    std::set<cell_t> matrix;

    cell_t c4(1, 2);
    auto it = matrix.find(c4);
    BOOST_CHECK(it == matrix.end());

    c4.set_value(12);
    auto rc = matrix.insert(c4);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(c4.get_value(), rc.first->get_value());

    it = matrix.find(c4);
    BOOST_CHECK(it != matrix.end());
    BOOST_CHECK_EQUAL(c4.get_value(), it->get_value());

    cell_t c5(3, 3);
    c5 = 12;
    rc = matrix.insert(c5);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(c5.get_value(), rc.first->get_value());

    it = matrix.find(c5);
    BOOST_CHECK(it != matrix.end());
    BOOST_CHECK_EQUAL(c5.get_value(), it->get_value());
}

template<typename T>
class Data
{
    public:
        using value_t = T;
        value_t v_;

        // Conversions from T and to T:
        explicit Data(const T& x) : v_(x) {
            std::cout << __PRETTY_FUNCTION__ << "\n";
        }
        explicit operator T() const {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            return v_;
        }
        template <typename U>
        Data(const Data<U>& x) : v_(x.v_) {
            std::cout << __PRETTY_FUNCTION__ << "\n";
        }

        // Semiregular:
        Data(const Data& x) : v_(x.v_) { // could be implicitly declared
            std::cout << __PRETTY_FUNCTION__ << "\n";
        }
        Data() : v_() { // could be implicitly declared sometimes
            std::cout << __PRETTY_FUNCTION__ << "\n";
        }
        ~Data() { // could be implicitly declared
            std::cout << __PRETTY_FUNCTION__ << "\n";
        }
        Data& operator=(const Data& x) { // could be implicitly declared
            if (this != &x) {
                std::cout << __PRETTY_FUNCTION__ << "\n";
                v_ = x.v_;
            }
            return *this;
        }

        Data& operator=(const T& x) {
            if (&(this->v_) != &x) {
                std::cout << __PRETTY_FUNCTION__ << "\n";
                v_ = x;
            }
            return *this;
        }

        // Regular
        friend
        bool operator==(const Data& x, const Data& y) {
            return x.v_ == y.v_;
        }
        friend
        bool operator!=(const Data& x, const Data& y) {
            return !(x == y);
        }

        // TotallyOrdered
        friend
        bool operator<(const Data& x, const Data& y) {
            return x.v_ < y.v_;
        }
        friend
        bool operator>(const Data& x, const Data& y) {
            return y < x;
        }
        friend
        bool operator<=(const Data& x, const Data& y) {
            return !(y < x);
        }
        friend
        bool operator>=(const Data& x, const Data& y) {
            return !(x < y);
        }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Data<T>& obj)
{
    os << obj.v_;
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Data<T>& obj)
{
    T t;
    is >> t;
    obj = t;
    return is;
}

template<typename T, T Default>
class M
{
    public:
        using value_t = Data<T>;
        using index_t = size_t;

        M() {}
        ~M() {}

        value_t& operator[](index_t idx)
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            auto it = matrix_.find(idx);
            if (it != matrix_.end()) {
                std::cout << it->first << ":" << it->second << "\n";
            }
            else {
                std::cout << "not found " << idx << "\n";
            }
//            if (idx >= matrix_.size()) {
//                matrix_.reserve(matrix_.size() + idx);
//                for (size_t i = 0; i <= idx; ++i) {
//                    matrix_.push_back(Default);
//                }
//            }
            return matrix_[idx];
        }

        const value_t& operator[](index_t idx) const
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            auto it = matrix_.find(idx);
            if (idx >= matrix_.size()) {
                std::string what = "Index ";
                what.append(std::to_string(idx)).
                        append(" is out of range ").
                        append(std::to_string(matrix_.size()));
                throw std::out_of_range(what);
            }
            return matrix_[idx];
        }

    private:
        std::map<index_t, value_t> matrix_;
};

BOOST_AUTO_TEST_CASE(matrix_init)
{
    using matrix_t = M<int, -1>;

    matrix_t m;
    m[0] = 99;
    std::cout << m[0] << "\n";
    std::cout << m[1] << "\n";
}
