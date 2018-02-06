#pragma once
/** @file line.h
 *  @brief Line
 */
#include "point.h"
#include "logger.h"

namespace svge {

class Vector : public GraphicsShape
{
    public:
        Vector()
        {
            TRACE();
        }

        ~Vector()
        {
            TRACE();
        }

        void set_start(Point* p) { add_item(p); }
        void set_end(Point* p) { add_item(p); }

        std::istream& read(std::istream& in) override
        {
            return in;
        }
};

}
