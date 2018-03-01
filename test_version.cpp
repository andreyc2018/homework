/** @file test_version.cpp
    @brief The unit tests
*/
#include "point.h"
#define BOOST_TEST_MODULE Test_SVGE
#include <boost/test/unit_test.hpp>
#include <sstream>

using svge::shape_type_t;
using svge::Point;

LoggerPtr gLogger = spdlog::stdout_logger_mt("console", true);

BOOST_AUTO_TEST_CASE(gs_type)
{
    gLogger->set_level(spdlog::level::trace);
    TRACE();
    gLogger->info("Set type to Point and write to stringstream");

    shape_type_t t = shape_type_t::Point;
    gLogger->info("sizeof(t) = {}, sizeof(gs_type_t) = {}",
                  sizeof (t), sizeof (shape_type_t));

    std::stringstream ss;
    ss.write(reinterpret_cast<const char*>(&t), sizeof (t));
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }

    gLogger->info("Read type as uint8_t and compare with 1");
    ss.seekg(0);
    uint8_t ut;
    ss.read(reinterpret_cast<char*>(&ut), sizeof (ut));
    BOOST_CHECK_EQUAL(1, ut);

    gLogger->info("Read type as gs_type_t and compare with Point");
    ss.seekg(0);
    shape_type_t t2;
    ss.read(reinterpret_cast<char*>(&t2), sizeof (t2));
    BOOST_CHECK_EQUAL(shape_type_t::Point, t2);

    gLogger->info("Write uninitialized gs_type_t to stringstream");
    gLogger->info("The value of uninitialzied enum is not defined");
    shape_type_t t3;
    gLogger->info("sizeof(t3) = {}, sizeof(gs_type_t) = {}",
                  sizeof (t3), sizeof (shape_type_t));
    ss.str(std::string());
    ss.write(reinterpret_cast<const char*>(&t3), sizeof (t3));
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }

    gLogger->info("Set uint8_t to value more than gs_type_t and write to stringstream");
    uint8_t ut1 = 99;
    ss.str(std::string());
    ss.write(reinterpret_cast<const char*>(&ut1), sizeof (ut1));
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }
    gLogger->info("Read out of range value into gs_type_t");
    ss.seekg(0);
    ss.read(reinterpret_cast<char*>(&t3), sizeof (t3));
    ss.str(std::string());
    ss.write(reinterpret_cast<const char*>(&t3), sizeof (t3));
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }
}

BOOST_AUTO_TEST_CASE(point_init)
{
    auto p = std::make_unique<Point>();
    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(0, p->id());
    BOOST_CHECK_EQUAL(0, p->x());
}
