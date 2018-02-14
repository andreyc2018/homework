#pragma once

#include "logger.h"
#include <map>
#include <iostream>

namespace svge {

using shape_id_t = size_t;

/**
 * @brief The shape_type_t enum
 * Graphics Shape Type
 */
enum class shape_type_t : uint8_t
{
    Point = 1, Vector, Unknown
};

std::istream& operator>> (std::istream& in, shape_type_t& val)
{
    uint8_t t;
    uint8_t min = static_cast<uint8_t>(shape_type_t::Point);
    uint8_t max = static_cast<uint8_t>(shape_type_t::Unknown);
    in >> t;
    if (t >= min && t < max) {
        val = static_cast<shape_type_t>(t);
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, shape_type_t val)
{
    out << static_cast<uint8_t>(val);
    return out;
}

class Shape;

using ShapeUPtr = std::unique_ptr<Shape>;
using shape_container_t = std::map<shape_id_t, ShapeUPtr>;

/**
 * @brief The Shape class
 *
 * Base class for all shapes
 */
class Shape
{
    public:
        Shape() : type_(shape_type_t::Unknown), id_(0)
        {
            TRACE();
        }
        explicit Shape(shape_type_t type) : type_(type), id_(0)
        {
            TRACE();
        }
        virtual ~Shape()
        {
            TRACE();
        }

        shape_id_t id() const { return id_; }
        void setId(shape_id_t id) { id_ = id; }

        shape_type_t type() const { return type_; }
        void setType(shape_type_t type) { type_ = type; }

        virtual std::ostream& write(std::ostream& out) = 0;
        virtual std::istream& read(std::istream& in) = 0;

    protected:
        shape_type_t type_;
        shape_id_t id_;
};

std::ostream& Shape::write(std::ostream& out)
{
    TRACE();
    out << type_ << id_;
    return out;
}

std::istream& Shape::read(std::istream& in)
{
    TRACE();
    in >> id_;
    return in;
}

}
