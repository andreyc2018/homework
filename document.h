#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "graphicsprimitive.h"
//#include "point.h"
//#include "line.h"
#include "logger.h"
#include <vector>

namespace svge {

class Document
{
    public:

        Document() : next_id_(1), modified_(false)
        {
            TRACE();
        }

        ~Document()
        {
            TRACE();
            for (const auto& shape : shapes_) {
                delete shape.second;
            }
        }

//        std::ostream& write(std::ostream& out)
//        {
//            if (!modified_) {
//                out << shapes_.size();
//                for (const auto& shape : shapes_) {
//                    shape.second->write(out);
//                }
//            }
//            return out;
//        }

//        std::istream& read(std::istream& in)
//        {
//            return in;
//        }

    private:
        gp_id_t next_id_;
        bool modified_;
        gp_container_t shapes_;

        gp_id_t next_id() { return next_id_++; }
        void reset_id() { next_id_ = 1; }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
