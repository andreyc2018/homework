#pragma once
/** @file point.h
 *  @brief Point
 */
#include "shape.h"

namespace svge {

class Point : public Shape
{
    public:
        using base = Shape;

        Point() : base(shape_type_t::Point), x_(0), y_(0) {}

        ~Point() {}

        ssize_t x() const { return x_; }
        void setX(const ssize_t& x) { x_ = x; }

        ssize_t y() const { return y_; }
        void setY(const ssize_t& y) { y_ = y; }

        std::ostream& write(std::ostream& out) const override
        {
            base::write(out);            
            write_stream(out, x_);
            write_stream(out, y_);
            return out;
        }

        std::istream& read(std::istream& in) override
        {
            base::read(in);
            read_stream(in, x_);
            read_stream(in, y_);
            return in;
        }

        void get_info() const override
        {
            std::cout << "    Point: id = " << id_
                      << " x = " << x_ << ", y =" << y_ << "\n";
        }

    protected:
        ssize_t x_;
        ssize_t y_;
};

using PointUPtr = std::unique_ptr<Point>;

}
