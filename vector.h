#pragma once
/** @file vector.h
 *  @brief Vector
 */
#include "point.h"
#include "logger.h"

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
            read_stream(in, type, "type");
            start_.read(in);
            read_stream(in, type, "type");
            end_.read(in);
            return in;
        }

        void get_info() const override
        {
            gLogger->info("Vector: id = {}, start({}, {}), end({}, {})",
                          id_, start_.x(), start_.y(), end_.x(), end_.y());
        }

    private:
        Point start_;
        Point end_;
};

}
