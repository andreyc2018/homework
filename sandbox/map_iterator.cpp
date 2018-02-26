#include <map>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#define TRACE()  std::cout << __PRETTY_FUNCTION__ << "\n"

template<typename T>
std::ostream& print_type(std::ostream& out, T& t)
{
    int     status;
    char   *realname;
    realname = abi::__cxa_demangle(typeid(t).name(), 0, 0, &status);
    out << "\"" << realname << "\"";
    return out;
}

template<typename T, typename... Args>
std::ostream& print_type(std::ostream& out, T& t, Args... args)
{
    print_type(out, t);
    out << ", ";
    print_type(out, args...);
    out << "\n";
    return out;
}

template<typename T>
class Cell
{
    public:
        using value_t = T;
        value_t v_;

        // Conversions from T and to T:
        explicit Cell(const T& x) : v_(x) {
            TRACE();
        }
        explicit operator T() const {
            TRACE();
            return v_;
        }
        template <typename U>
        Cell(const Cell<U>& x) : v_(x.v_) {
            TRACE();
        }

        // Semiregular:
        Cell(const Cell& x) : v_(x.v_) { // could be implicitly declared
            TRACE();
        }
        Cell() : v_() { // could be implicitly declared sometimes
            TRACE();
        }
        ~Cell() { // could be implicitly declared
            TRACE();
        }
        Cell& operator=(const Cell& x) { // could be implicitly declared
            if (this != &x) {
                TRACE();
                v_ = x.v_;
            }
            return *this;
        }

        Cell& operator=(const T& x) {
            if (&(this->v_) != &x) {
                TRACE();
                v_ = x;
            }
            return *this;
        }

        // Regular
        friend
        bool operator==(const Cell& x, const Cell& y) {
            return x.v_ == y.v_;
        }
        friend
        bool operator!=(const Cell& x, const Cell& y) {
            return !(x == y);
        }

        // TotallyOrdered
        friend
        bool operator<(const Cell& x, const Cell& y) {
            return x.v_ < y.v_;
        }
        friend
        bool operator>(const Cell& x, const Cell& y) {
            return y < x;
        }
        friend
        bool operator<=(const Cell& x, const Cell& y) {
            return !(y < x);
        }
        friend
        bool operator>=(const Cell& x, const Cell& y) {
            return !(x < y);
        }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Cell<T>& obj)
{
    os << obj.v_;
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Cell<T>& obj)
{
    T t;
    is >> t;
    obj = t;
    return is;
}

// D-dimensional matrix
template<typename T, size_t D>
class Matrix
{
    public:
        using coords_t = std::array<int, D>;
        using value_t = typename std::conditional<D == 1, T, Matrix<T, D-1>>::type;

        using map_t = std::map<coords_t, value_t>;
        using map_it_t = typename map_t::iterator;

        map_t m_;

        operator std::tuple<int, int, int> () const {
            TRACE();
            return std::make_tuple(1, 2, 3);
        }

        operator int () const {
            TRACE();
            return 3;
        }


        class m_iterator
        {
            public:
                m_iterator(map_it_t it) : it_(it) {}

                value_t operator*()
                {
                    TRACE();
                    return it_->second;
                }

                //! pre-increment
                m_iterator& operator++()
                {
                    TRACE();
                    it_++; return *this;
                }

                bool operator==(const m_iterator& b) const
                {
                    TRACE();
                    return it_->first == b.it_->first;
                }

                bool operator!=(const m_iterator& b) const
                {
                    TRACE();
                    return !(*this == b);
                }

                map_it_t it_;
        };

        using iterator = m_iterator;

        value_t& operator[](int i) {
            TRACE();
            coords_t c { {i} };
            return m_[c];
        }

        iterator begin() noexcept {
            TRACE();
            iterator it(m_.begin());
            return it;
        }

        iterator end() noexcept {
            TRACE();
            iterator it(m_.end());
            return it;
        }
};

void single_dimension()
{
    TRACE();
    using matrix_t = Matrix<int, 1>;
    matrix_t m;

    std::cout << "Assign\n";
    for (int i = 0; i < 3; ++i) {
        print_type(std::cout, m[i]);
        m[i] = i*2;
    }

    std::cout << "\nRead using iterator\n";
    for (auto it = m.begin(); it != m.end(); ++it) {
        print_type(std::cout, it);
        std::cout << *it << " = " << *it << "\n";
    }

    std::cout << "\nRead using index\n";
    for (int i = 0; i < 3; ++i) {
        print_type(std::cout, m[i]);
        std::cout << " " << m[i] << "\n";
    }

    std::cout << "\nRead using range for\n";
    for (auto c : m) {
        print_type(std::cout, c);
        std::cout << " " << c << "\n";
    }
    std::cout << "\n";
}

void two_dimension()
{
    TRACE();
    using matrix_t = Matrix<int, 2>;
    matrix_t m;

    std::cout << "Assign\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            print_type(std::cout, m[i], m[i][j]);
            m[i][j] = i+j;
        }
    }

    std::cout << "\nRead using iterator\n";
    for (auto it = m.begin(); it != m.end(); ++it) {
        print_type(std::cout, it);
        for (auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
            auto n = *jt;
            print_type(std::cout, jt, n);
            std::cout << n << ", ";
        }
        std::cout << "\n";
    }

    std::cout << "\nRead using index\n";
    for (int i = 0; i < 3; ++i) {
        print_type(std::cout, m[i]) << "\n";
//        std::cout << m[i] << "\n";
    }

    std::cout << "\nRead using range for\n";
    for (auto c : m) {
        print_type(std::cout, c) << "\n";
//        std::cout << c << "\n";
        int x = -1;
        int y = -1;
        int v = -1;
//        std::tie(x, y, v) = c;
        v = c;
        std::cout << x << " : " << y << " : " << v << "\n";
    }
    std::cout << "\n";
}

int main(int, char**)
{
//    single_dimension();
    two_dimension();

    return 0;
}
