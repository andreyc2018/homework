#pragma once

#include "document.h"
#include <tuple>
#include <vector>
#include <memory>
#include <fstream>

namespace svge {

class Svge
{
    public:
        Svge() {}
        ~Svge() {}

        item_id_t create_document()
        {
            if (docs_) {}
        }

        void export_document(item_id_t id, const std::string& filename)
        {

        }

    private:
        DocumentUPtr docs_;
};

using SvgeUPtr = std::unique_ptr<Svge>;

}
