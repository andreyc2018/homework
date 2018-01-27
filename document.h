#pragma once
/** @file document.h
    @brief The document representation.

    Details.
*/

#include "item.h"
#include <vector>

namespace svge {

class Document
{
    public:
        Document() {}
        ~Document() {}

    private:
        std::vector<Item> items_;
};

using DocumentUPtr = std::unique_ptr<Document>;

}
