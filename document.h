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

        Document() : next_id_(1), modified_(false) {}
        ~Document() {}

        std::ostream& write(std::ostream& out)
        {
            shape_container_t::size_type size = shapes_.size();
            write_stream(out, size, "size");
            for (const auto& shape : shapes_) {
                shape.second->write(out);
            }
            return out;
        }

        std::istream& read(std::istream& in)
        {
            shape_container_t::size_type size = 0;
            read_stream(in, size, "size");
            for (size_t i = 0; i < size; ++i) {
                shape_type_t type;
                read_stream(in, type, "type");
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
            modified_ = true;
            return id;
        }

        ShapeUPtr make_item(shape_type_t type)
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
            if (item)
                item->setId(next_id());
            return item;
        }

        void delete_item(shape_id_t id)
        {
            modified_ = shapes_.erase(id) > 0;
        }

        void collect_items()
        {
            gLogger->info("Document contains {} shapes", shapes_.size());
            for (const auto& shape : shapes_) {
                shape.second->get_info();
            }
        }

        bool modified() const { return modified_; }

    private:
        shape_id_t next_id_;
        shape_container_t shapes_;
        bool modified_;

        shape_id_t next_id() { return next_id_++; }
        void reset_id() { next_id_ = 1; }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
