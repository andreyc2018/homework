#pragma once
/** @file point.h
 *  @brief Point
 */
#include "shape.h"
#include "logger.h"

namespace svge {

class Point : public Shape
{
    public:
        using base = Shape;

        Point() : base(shape_type_t::Point), x_(0), y_(0)
        {
            TRACE();
        }

        ~Point()
        {
            TRACE();
        }

        ssize_t x() const { return x_; }
        void setX(const ssize_t& x) { x_ = x; }

        ssize_t y() const { return y_; }
        void setY(const ssize_t& y) { y_ = y; }

        std::ostream& write(std::ostream& out) override
        {
            TRACE();
            base::write(out);
            out << x_ << y_;
            return out;
        }

        std::istream& read(std::istream& in) override
        {
            TRACE();
            base::read(in);
            in >> x_ >> y_;
            return in;
        }

    protected:
        ssize_t x_;
        ssize_t y_;
};

}
