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
    Point, Vector
};

class GraphicsPrimitive;

using gp_container_t = std::map<gp_id_t, GraphicsPrimitive*>;

class GraphicsPrimitive
{
    public:
        GraphicsPrimitive() : id_(0)
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
        gp_id_t id_;
        gs_type_t type_;
};

class GraphicsShape : public GraphicsPrimitive
{
    public:
        GraphicsShape()
        {
            SPDLOG_TRACE(gLogger);
        }

        ~GraphicsShape()
        {
            SPDLOG_TRACE(gLogger);
            for (const auto& item : items_) {
                delete item.second;
            }
        }

        std::ostream& write(std::ostream& out) override
        {
            SPDLOG_TRACE(gLogger);
            out << items_.size();
            for (const auto& item : items_) {
                item.second->write(out);
            }
            return out;
        }

    protected:
        gp_container_t items_;
};

}
