#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "shape.h"
#include "point.h"
#include "vector.h"
#include "logger.h"
#include <vector>
#include <iostream>

namespace svge {

/**
 * @brief The Document class
 *
 * Contains the shapes.
 */
class Document
{
    public:

        Document() : next_id_(1) { TRACE(); }
        ~Document() { TRACE(); }

        std::ostream& write(std::ostream& out)
        {
            TRACE();
            out << shapes_.size();
            for (const auto& shape : shapes_) {
                shape.second->write(out);
            }
            return out;
        }

        std::istream& read(std::istream& in)
        {
            TRACE();
            size_t shapes_size = 0;
            in >> shapes_size;
            for (size_t i = 0; i < shapes_size; ++i) {
                shape_type_t type;
                in >> type;
                ShapeUPtr item = make_item(type);
                item->read(in);
                shapes_[item->id()] = std::move(item);
            }
            return in;
        }

        shape_id_t create_item(shape_type_t type)
        {
            ShapeUPtr item = make_item(type);
            shape_id_t id = item->id();
            shapes_[id] = std::move(item);
            return id;
        }

        ShapeUPtr make_item(shape_type_t type)
        {
            ShapeUPtr item;
            switch(type) {
                case shape_type_t::Point:
                    item.reset(new Point);
                    break;
                case shape_type_t::Vector:
                    item.reset(new Vector);
                    break;
                default:
                    break;
            }
            if (item)
                item->setId(next_id());
            return item;
        }

    private:
        shape_id_t next_id_;
        shape_container_t shapes_;

        shape_id_t next_id() { return next_id_++; }
        void reset_id() { next_id_ = 1; }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
