#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "shapefactory.h"
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
            write_stream(out, size);
            for (const auto& shape : shapes_) {
                shape.second->write(out);
            }
            return out;
        }

        std::istream& read(std::istream& in)
        {
            shape_container_t::size_type size = 0;
            read_stream(in, size);
            for (size_t i = 0; i < size; ++i) {
                shape_type_t type;
                read_stream(in, type);
                ShapeUPtr item = ShapeFactory::create(type);
                item->read(in);
                shapes_[item->id()] = std::move(item);
            }
            return in;
        }

        shape_id_t create_shape(shape_type_t type)
        {
            ShapeUPtr item = ShapeFactory::create(type);
            shape_id_t id = 0;
            if (item) {
                item->setId(next_id());
                id = item->id();
                shapes_[id] = std::move(item);
                modified_ = true;
            }
            return id;
        }

        void delete_item(shape_id_t id)
        {
            modified_ = shapes_.erase(id) > 0;
        }

        void collect_items()
        {
            std::cout << "  Document contains " << shapes_.size() << " shapes\n";
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
};

using DocumentUPtr = std::unique_ptr<Document>;

}
