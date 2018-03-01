#pragma once
/** @file vector.h
 *  @brief Vector
 */
#include "point.h"

namespace svge {

class Vector : public Shape
{
    public:
        using base = Shape;

        Vector() : base(shape_type_t::Vector) {}
        ~Vector() {}

        void setStart(const Point& p) { start_ = p; }
        const Point& start() const { return start_; }

        void setEnd(const Point& p) { end_ = p; }
        const Point& end() const { return end_; }

        std::ostream& write(std::ostream& out) const override
        {
            base::write(out);
            start_.write(out);
            end_.write(out);
            return out;
        }

        std::istream& read(std::istream& in) override
        {
            base::read(in);
            shape_type_t type;
            read_stream(in, type);
            start_.read(in);
            read_stream(in, type);
            end_.read(in);
            return in;
        }

        void get_info() const override
        {
            std::cout << "    Vector: id = " << id_
                      << " start(" << start_.x() << ", " << start_.y()
                      << "), end(" << end_.x() << ", " << end_.y() << ")\n";
        }

    private:
        Point start_;
        Point end_;
};

}
