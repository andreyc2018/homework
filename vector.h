#pragma once
/** @file vector.h
 *  @brief Vector
 */
#include "point.h"
#include "logger.h"

namespace svge {

class Vector : public GraphicsShape
{
    public:
        using base = GraphicsShape;

        Vector() : base(gs_type_t::Vector)
        {
            TRACE();
        }

        ~Vector()
        {
            TRACE();
        }

        void setStart(GPUPtr& p) { start_ = std::move(p); }
        const GPUPtr& start() const { return start_; }

        void setEnd(GPUPtr& p) { end_ = std::move(p); }
        const GPUPtr& end() const { return end_; }

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
        GPUPtr start_;
        GPUPtr end_;
};

}
