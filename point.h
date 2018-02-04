#pragma once
/** @file point.h
 *  @brief Point
 */
#include "item.h"

namespace svge {

class Point : public SimpleItem
{
    public:
        Point(item_id_t id, ssize_t x, ssize_t y)
            : SimpleItem(id), x_(x), y_(y) {}

        ssize_t x() const { return x_; }
        void setX(const ssize_t& x) { x_ = x; }

        ssize_t y() const { return y_; }
        void setY(const ssize_t& y) { y_ = y; }

    protected:
        ssize_t x_;
        ssize_t y_;

};

}
