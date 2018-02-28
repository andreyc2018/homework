#include <map>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#define TRACE()  std::cout << __PRETTY_FUNCTION__ << "\n"

template<typename T>
std::ostream& print_type(std::ostream& out, const T)
{
    int status;
    char *realname = nullptr;
    realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
    if (realname) {
        out << typeid(T).name() << " : " << realname;
        free(realname);
    }
    else {
        out << "demangle error: " << status;
    }
    return out;
}

template<typename T>
class V
{
    public:
        using v_t = T;
        v_t v_;

        // Conversions from T and to T:
        explicit V(const T& x) : v_(x) {}

        template <typename U>
        V(const V<U>& x) : v_(x.v_) {}

        explicit operator T() const { return v_; }

        // Semiregular:
        V(const V& x) : v_(x.v_) {}
        V() : v_() {}
        ~V() {}
        V& operator=(const V& x) {
            if (this != &x) {
                v_ = x.v_;
            }
            return *this;
        }

        V& operator=(const T& x) {
            if (&(this->v_) != &x) {
                v_ = x;
            }
            return *this;
        }

        // Regular
        friend
        bool operator==(const V& x, const V& y) {
            return x.v_ == y.v_;
        }
        friend
        bool operator!=(const V& x, const V& y) {
            return !(x == y);
        }

        // TotallyOrdered
        friend
        bool operator<(const V& x, const V& y) {
            return x.v_ < y.v_;
        }
        friend
        bool operator>(const V& x, const V& y) {
            return y < x;
        }
        friend
        bool operator<=(const V& x, const V& y) {
            return !(y < x);
        }
        friend
        bool operator>=(const V& x, const V& y) {
            return !(x < y);
        }

        std::enable_if<
        v_t& operator[](int i) {
            return v_[i];
        }
};

template<typename T, size_t D, T Z>
class Matrix
{
    public:
        using coords_t = int;
        using value_t = V<typename std::conditional<D == 1, T, Matrix<T, D-1, Z>>::type>;

        using map_t = std::map<coords_t, value_t>;
        using map_it_t = typename map_t::iterator;

        map_t m_;

        class m_iterator
        {
            public:
                m_iterator(map_it_t it) : it_(it) {}

                value_t operator*() { return it_->second; }

                //! pre-increment
                m_iterator& operator++() { it_++; return *this; }

                bool operator==(const m_iterator& b) const { return it_->first == b.it_->first; }
                bool operator!=(const m_iterator& b) const { return !(*this == b); }

                map_it_t it_;
        };

        using iterator = m_iterator;

        size_t size() const { return m_.size(); }

        value_t& operator[](int i) {
            coords_t c { i };
            return m_[c];
        }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const V<T>& obj)
{
    os << obj.v_;
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, V<T>& obj)
{
    T t;
    is >> t;
    obj = t;
    return is;
}

int main(int, char**)
{
    using matrix_t = Matrix<int, 2, 0>;
    matrix_t m;

    std::cout << "type m = ";
    print_type(std::cout, m) << "\n";
    std::cout << "size = " << m.size() << "\n";

    std::cout << "type m[0] = ";
    print_type(std::cout, m[0]) << "\n";
    std::cout << "size = " << m.size() << "\n";

    std::cout << "type m[0][0] = ";
    print_type(std::cout, m[0][0]) << "\n";
    std::cout << "size = " << m.size() << "\n";

    return 0;
}
