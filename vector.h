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

        Vector() : base(shape_type_t::Vector)
        {
            TRACE();
        }

        ~Vector()
        {
            TRACE();
        }

        void setStart(ShapeUPtr& p) { start_ = std::move(p); }
        const ShapeUPtr& start() const { return start_; }

        void setEnd(ShapeUPtr& p) { end_ = std::move(p); }
        const ShapeUPtr& end() const { return end_; }

        std::ostream& write(std::ostream& out) override
        {
            TRACE();
            base::write(out);
            if (start_)
                start_->write(out);
            if (end_)
                end_->write(out);
            return out;
        }

        std::istream& read(std::istream& in) override
        {
            TRACE();
            base::read(in);

//            start_->read(in);
//            end_->read(in);
            return in;
        }

    private:
        ShapeUPtr start_;
        ShapeUPtr end_;
};

}
