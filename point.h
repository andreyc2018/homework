#pragma once
/** @file point.h
 *  @brief Point
 */
#include "item.h"

namespace svge {

class Point : public SimpleItem
{
    public:
        Point(item_id_t id)
            : SimpleItem(id, item_type_t::Point), x_(0), y_(0) {}

        Point(item_id_t id, ssize_t x, ssize_t y)
            : SimpleItem(id, item_type_t::Point), x_(x), y_(y) {}

        ssize_t x() const { return x_; }
        void setX(const ssize_t& x) { x_ = x; }

        ssize_t y() const { return y_; }
        void setY(const ssize_t& y) { y_ = y; }

        std::ostream& write(std::ostream& out) override
        {
            out << x_ << y_;
            return out;
        }

        std::istream& read(std::istream& in) override
        {
        }

    protected:
        ssize_t x_;
        ssize_t y_;
};

}
