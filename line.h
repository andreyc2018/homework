#pragma once
/** @file line.h
 *  @brief Line
 */
#include "point.h"

namespace svge {

class Line : public ComplexItem
{
    public:
        Line(item_id_t id) : ComplexItem(id, item_type_t::Line) {}

        void set_start(Point* p) { add_item(p); }
        void set_end(Point* p) { add_item(p); }
};

}
