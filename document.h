#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "item.h"
#include <vector>

namespace svge {

class Document : public ComplexItem
{
    public:
        using base = ComplexItem;

        Document(item_id_t id) : ComplexItem(id) {}
        ~Document() {}

        std::ostream& write(std::ostream& out) override
        {
            out << id_;
            return base::write(out);
        }

        std::istream& read(std::istream& in) override
        {
            in >> id_;
            return base::read(in);
        }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
