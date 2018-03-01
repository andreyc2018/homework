#pragma once

#include "point.h"
#include "vector.h"

namespace svge {

class ShapeFactory
{
    public:
        static ShapeUPtr create(shape_type_t type)
        {
            ShapeUPtr item;
            switch(type) {
                case shape_type_t::Point:
                    item = std::make_unique<Point>();
                    break;
                case shape_type_t::Vector:
                    item = std::make_unique<Vector>();
                    break;
                default:
                    break;
            }
            return item;
        }
};

}
