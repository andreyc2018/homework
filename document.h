#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "graphicsprimitive.h"
#include "point.h"
#include "vector.h"
#include "logger.h"
#include <vector>
#include <iostream>

namespace svge {

class Document
{
    public:

        Document() : next_id_(1)
        {
            TRACE();
        }

        ~Document()
        {
            TRACE();
        }

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
                gs_type_t type;
                in >> type;
                GPUPtr item = make_item(type);
                item->read(in);
                shapes_[item->id()] = std::move(item);
            }
            return in;
        }

        gp_id_t create_item(gs_type_t type)
        {
            GPUPtr item = make_item(type);
            gp_id_t id = item->id();
            shapes_[id] = std::move(item);
            return id;
        }

        GPUPtr make_item(gs_type_t type)
        {
            GPUPtr item = nullptr;
            switch(type) {
                case gs_type_t::Point:
                    item.reset(new Point);
                    break;
                case gs_type_t::Vector:
                    item.reset(new Vector);
                    break;
                default:
                    break;
            }
            item->setId(next_id());
            return item;
        }
    private:
        gp_id_t next_id_;
        gp_container_t shapes_;

        gp_id_t next_id() { return next_id_++; }
        void reset_id() { next_id_ = 1; }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
