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

const char* shape_type_string(shape_type_t type)
{
    if (type == shape_type_t::Point) {
        return "point";
    }
    else if (type == shape_type_t::Vector) {
        return "vector";
    }
    return "unknown";
}

//std::istream& operator>> (std::istream& in, shape_type_t& val)
//{
//    uint8_t t;
//    uint8_t min = static_cast<uint8_t>(shape_type_t::Point);
//    uint8_t max = static_cast<uint8_t>(shape_type_t::Unknown);
//    in >> t;
//    if (t >= min && t < max) {
//        val = static_cast<shape_type_t>(t);
//    }
//    return in;
//}

std::ostream& operator<< (std::ostream& out, shape_type_t val)
{
    out << static_cast<uint8_t>(val);
    return out;
}

template<typename T>
std::istream& read_stream(std::istream& in, T& data, const char* type)
{
    gLogger->debug("reading {} {} bytes", type, sizeof (T));
    in.read(reinterpret_cast<char*>(&data), sizeof (T));
    return in;
}

template<typename T>
std::ostream& write_stream(std::ostream& out, const T& data, const char* type)
{
    gLogger->debug("writing {} {} bytes", type, sizeof (T));
    out.write(reinterpret_cast<const char*>(&data), sizeof (T));
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
        Shape() : type_(shape_type_t::Unknown), id_(0) {}
        explicit Shape(shape_type_t type) : type_(type), id_(0) {}
        virtual ~Shape() {}

        shape_id_t id() const { return id_; }
        void setId(shape_id_t id) { id_ = id; }

        shape_type_t type() const { return type_; }
        void setType(shape_type_t type) { type_ = type; }

        virtual std::ostream& write(std::ostream& out) const = 0;
        virtual std::istream& read(std::istream& in) = 0;

        virtual void get_info() const = 0;

    protected:
        shape_type_t type_;
        shape_id_t id_;
};

std::ostream& Shape::write(std::ostream& out) const
{
    write_stream(out, type_, "type");
    write_stream(out, id_, "id");
    return out;
}

std::istream& Shape::read(std::istream& in)
{
    read_stream(in, id_, "id");
    return in;
}

}
