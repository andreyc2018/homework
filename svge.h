#pragma once

#include "document.h"
#include <vector>
#include <memory>
#include <fstream>

namespace svge {

class Svge
{
    public:
        Svge() {}
        ~Svge() {}

        item_id_t create_new_document();

        void export_document(item_id_t id, const std::string& filename)
        {

        }

    private:
        std::vector<Document> docs_;
};

using SvgeUPtr = std::unique_ptr<Svge>;

}
