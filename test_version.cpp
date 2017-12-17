#include "ip_filter.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(split)
{
    auto result = otus::split("", '.');
    BOOST_CHECK_EQUAL(1, result.size());
    BOOST_CHECK(result[0].empty());

    result = otus::split("11", '.');
    BOOST_CHECK_EQUAL(1, result.size());
    BOOST_CHECK_EQUAL("11", result[0]);

    result = otus::split("..", '.');
    BOOST_CHECK_EQUAL(3, result.size());
    for (const auto& r : result) {
        BOOST_CHECK(r.empty());
    }
}

BOOST_AUTO_TEST_CASE(reverse)
{
    std::vector<std::vector<std::string>> pool {
        {"1", "2", "1", "1"},
        {"1", "10", "1", "1"},
        {"1", "2", "3", "1"},
        {"1", "1", "1", "1"}
    };

    std::string expected_reversed = "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.2.1.1\n"
                                    "1.1.1.1\n";

    otus::reverse(pool);
    std::stringstream buffer;
    otus::print(buffer, pool);
    BOOST_CHECK_EQUAL(expected_reversed, buffer.str());
}

BOOST_AUTO_TEST_CASE(print_reverse)
{
    std::vector<std::vector<std::string>> pool {
        {"1", "2", "1", "1"},
        {"1", "10", "1", "1"},
        {"1", "2", "3", "1"},
        {"1", "1", "1", "1"}
    };

    std::string expected_original = "1.2.1.1\n"
                                    "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.1.1.1\n";

    std::string expected_reversed = "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.2.1.1\n"
                                    "1.1.1.1\n";

    std::stringstream buffer;
    otus::print(buffer, pool);
    BOOST_CHECK_EQUAL(expected_original, buffer.str());

    buffer.str("");
    otus::print_reverse(buffer, pool);
    BOOST_CHECK_EQUAL(expected_reversed, buffer.str());
}

//BOOST_AUTO_TEST_CASE(sort)
//{
//    std::vector<std::vector<std::string>> pool {
//        {"1", "2", "1", "1"},
//        {"1", "10", "1", "1"},
//        {"1", "2", "3", "1"},
//        {"1", "1", "1", "1"}
//    };

//    std::string expected =
//        "1.1.1.1\n"
//        "1.2.1.1\n"
//        "1.2.3.1\n"
//        "1.10.1.1\n";

//    otus::sort(pool);

//    std::stringstream buffer;
//    otus::print(buffer, pool);
//    BOOST_CHECK_EQUAL(expected, buffer.str());

//    std::string reverse_expected =
//        "1.10.1.1\n"
//        "1.2.3.1\n"
//        "1.2.1.1\n"
//        "1.1.1.1\n";

//    BOOST_CHECK_EQUAL(4, pool.size());
//}

#if 0
struct Employee {
    Employee(int age, std::string name) : age(age), name(name) { }
    int age;
    std::string name;  // Does not participate in comparisons
};

std::vector<Employee> v = {
    Employee(108, "Zaphod"),
    Employee(32, "Arthur"),
    Employee(108, "Ford"),
};

bool operator<(const Employee &lhs, const Employee &rhs) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return lhs.age < rhs.age;
}

struct item_t
{
    std::string data;
};

using item_pool_t = std::vector<item_t>;
using pool_items_t = std::vector<item_pool_t>;

bool operator<(const item_t& lhs,
               const item_t& rhs)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    std::cout << "lhs = " << lhs.data << "\n";
    std::cout << "rhs = " << rhs.data << "\n";

    if (lhs.data.size() < rhs.data.size())
        return true;
    if (lhs.data.size() > rhs.data.size())
        return false;
    if (std::stoi(lhs.data) < std::stoi(rhs.data)) {
        return true;
    }
    return false;
}

bool operator<(const item_pool_t& lhs,
               const item_pool_t& rhs)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";

    if (lhs.size() < rhs.size())
        return true;
    if (lhs.size() > rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (std::stoi(lhs[i].data) < std::stoi(rhs[i].data)) {
            return true;
        }
    }
    return false;
}

bool operator<(const otus::entry_t& lhs,
               const otus::entry_t& rhs)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    std::cout << "lhs = ";
    otus::print_entry(std::cout, lhs);

    std::cout << "rhs = ";
    otus::print_entry(std::cout, rhs);

    if (lhs.size() < rhs.size())
        return true;
    if (lhs.size() > rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (std::stoi(lhs[i]) < std::stoi(rhs[i])) {
            return true;
        }
    }
    return false;
}

BOOST_AUTO_TEST_CASE(filter)
{
    otus::pool_t pool {
        {"1", "2", "1", "1"},
        {"1", "10", "1", "1"},
        {"1", "2", "3", "1"},
        {"1", "1", "1", "1"}
    };

    BOOST_CHECK_EQUAL(2, pool.size());

    std::stable_sort(v.begin(), v.end());
    std::stable_sort(pool.begin(), pool.end());

    for (const Employee &e : v) {
        std::cout << e.age << ", " << e.name << '\n';
    }

    item_pool_t p {
        {"10"}, {"2"}
    };
    std::stable_sort(p.begin(), p.end());

    pool_items_t pp {
        { {"10"}, {"2"} }
    };
    std::stable_sort(pp.begin(), pp.end());
}
#endif
