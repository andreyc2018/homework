#pragma once

#include <map>

namespace svge {

/**
 * @brief The item_type_t enum
 *
 * There are two primitives Point and Vector.
 * All other shapes are a combination of these two.
 */
enum class item_type_t : uint8_t
{
    Point, Vector
};

using item_id_t = size_t;

class GraphicsPrimitive
{
    public:
        virtual ~GraphicsPrimitive() {}
};

class GraphicsShape : public GraphicsPrimitive
{
    public:
        virtual ~GraphicsShape() {}
};

}
