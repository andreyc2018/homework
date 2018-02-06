/** @file test_version.cpp
    @brief The unit tests
*/
#include "point.h"
//#include "line.h"
#define BOOST_TEST_MODULE Test_SVGE
//#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/unit_test.hpp>
#include <sstream>

using svge::gs_type_t;
//using svge::create_item;
using svge::Point;
//using svge::ComplexItem;

LoggerPtr gLogger = spdlog::stdout_logger_mt("console", true);

BOOST_AUTO_TEST_CASE(gs_type)
{
    gLogger->set_level(spdlog::level::trace);
    TRACE();
    gLogger->info("Set type to Point and write to stringstream");

    gs_type_t t = gs_type_t::Point;
    gLogger->info("sizeof(t) = {}, sizeof(gs_type_t) = {}",
                  sizeof (t), sizeof (gs_type_t));

    std::stringstream ss;
    ss << t;
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }

    gLogger->info("Read type as uint8_t and compare with 1");
    ss.seekg(0);
    uint8_t ut;
    ss >> ut;
    BOOST_CHECK_EQUAL(1, ut);

    gLogger->info("Read type as gs_type_t and compare with Point");
    ss.seekg(0);
    gs_type_t t2;
    ss >> t2;
    BOOST_CHECK_EQUAL(gs_type_t::Point, t2);

    gLogger->info("Write uninitialized gs_type_t to stringstream");
    gLogger->info("The value of uninitialzied enum is not defined");
    gs_type_t t3;
    gLogger->info("sizeof(t3) = {}, sizeof(gs_type_t) = {}",
                  sizeof (t3), sizeof (gs_type_t));
    ss.str(std::string());
    ss << t3;
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }

    gLogger->info("Set uint8_t to value more than gs_type_t and write to stringstream");
    uint8_t ut1 = 99;
    ss.str(std::string());
    ss << ut1;
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }
    gLogger->info("Read out of range value into gs_type_t");
    ss.seekg(0);
    ss >> t3;
    ss.str(std::string());
    ss << t3;
    for (const auto& c : ss.str()) {
        gLogger->info("Type {:#x}", c);
    }
}

BOOST_AUTO_TEST_CASE(point_init)
{
    auto p = new Point();
    BOOST_CHECK_EQUAL(0, p->id());
    BOOST_CHECK_EQUAL(0, p->x());
//    BOOST_CHECK(true);
    delete p;
}

BOOST_AUTO_TEST_CASE(line_init)
{
//    auto l = create_item<Line>();
//    BOOST_CHECK_EQUAL(3, l->id());
    BOOST_CHECK(true);
}
