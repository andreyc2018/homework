#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "item.h"
#include "point.h"
#include "line.h"
#include "logger.h"
#include <vector>

namespace svge {

class Document : public ComplexItem
{
    public:
        using base = ComplexItem;

        Document(const LoggerPtr& logger)
            : ComplexItem(0, item_type_t::Document)
            , logger_(logger), next_id_(1) {}
        ~Document() {}

        void reset()
        {
            clear();
            reset_id();
        }

        void delete_item(item_id_t id)
        {
        }

        std::ostream& write(std::ostream& out) override
        {
            out << items_.size();
            return base::write(out);
        }

        std::istream& read(std::istream& in) override
        {
            return in;
        }

    private:
        LoggerPtr logger_;
        item_id_t next_id_;

        item_id_t next_id() { return next_id_++; }
        void reset_id() { next_id_ = 1; }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
