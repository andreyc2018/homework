#include <map>
#include <iostream>

#define TRACE()  std::cout << __PRETTY_FUNCTION__ << "\n"

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

// 1-dimensional matrix
template<typename T, size_t D>
class Matrix
{
    public:
        using coords_t = std::array<int, D>;
        using value_t = typename std::conditional<D == 1, T, Matrix<T, D-1>>;

        using map_t = std::map<coords_t, value_t>;
        using map_it_t = typename map_t::iterator;

        map_t m_;

        class m_iterator
        {
            public:
                m_iterator(map_it_t it) : it_(it) {}

                value_t operator*()
                {
                    return it_->second;
                }

                //! pre-increment
                m_iterator& operator++()
                {
                    it_++; return *this;
                }

                bool operator==(const m_iterator& b) const
                {
                    return it_->first == b.it_->first;
                }

                bool operator!=(const m_iterator& b) const
                {
                    return !(*this == b);
                }

                map_it_t it_;
        };

        using iterator = m_iterator;

        value_t& operator[](int i) {
            coords_t c { {i} };
            return m_[c];
        }

        iterator begin() noexcept {
            iterator it(m_.begin());
            return it;
        }

        iterator end() noexcept {
            iterator it(m_.end());
            return it;
        }
};

int main(int, char**)
{
    using matrix_t = Matrix<int, 1>;
    matrix_t m;
    for (int i = 0; i < 3; ++i)
    {
        m[i] = i*2;
    }

//    for (auto it = m.begin(); it != m.end(); ++it)
//    {
//        std::cout << it->first << " = " << it->second << "\n";
//    }

    for (int i = 0; i < 3; ++i)
    {
        std::cout << m[i] << "\n";
    }

    for (auto c : m)
    {
        std::cout << c << "\n";
    }

    return 0;
}
