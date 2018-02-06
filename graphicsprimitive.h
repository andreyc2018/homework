#pragma once

#include "logger.h"
#include <map>
#include <iostream>

namespace svge {

using gp_id_t = size_t;

/**
 * @brief The gs_type_t enum
 * Graphics Shape Type
 */
enum class gs_type_t : uint8_t
{
    Point = 1, Vector, Unknown
};

std::istream& operator>> (std::istream& in, gs_type_t& val)
{
    uint8_t t;
    uint8_t min = static_cast<uint8_t>(gs_type_t::Point);
    uint8_t max = static_cast<uint8_t>(gs_type_t::Unknown);
    in >> t;
    if (t >= min && t < max) {
        val = static_cast<gs_type_t>(t);
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, gs_type_t val)
{
    out << static_cast<uint8_t>(val);
    return out;
}

class GraphicsPrimitive;

using GPUPtr = std::unique_ptr<GraphicsPrimitive>;
using gp_container_t = std::map<gp_id_t, GPUPtr>;

class GraphicsPrimitive
{
    public:
        GraphicsPrimitive() : type_(gs_type_t::Unknown), id_(0)
        {
            TRACE();
        }
        explicit GraphicsPrimitive(gs_type_t type) : type_(type), id_(0)
        {
            TRACE();
        }
        virtual ~GraphicsPrimitive()
        {
            TRACE();
        }

        gp_id_t id() const { return id_; }
        void setId(gp_id_t id) { id_ = id; }

        gs_type_t type() const { return type_; }
        void setType(gs_type_t type) { type_ = type; }

        virtual std::ostream& write(std::ostream& out) = 0;
        virtual std::istream& read(std::istream& in) = 0;

    protected:
        gs_type_t type_;
        gp_id_t id_;
};

class GraphicsShape : public GraphicsPrimitive
{
    public:
        GraphicsShape() { TRACE(); }
        explicit GraphicsShape(gs_type_t type) : GraphicsPrimitive(type) {}
        ~GraphicsShape() { TRACE(); }
};

std::ostream& GraphicsPrimitive::write(std::ostream& out)
{
    TRACE();
    out << type_ << id_;
    return out;
}

std::istream& GraphicsPrimitive::read(std::istream& in)
{
    TRACE();
    in >> id_;
    return in;
}

}
