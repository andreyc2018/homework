#pragma once
/** @file svgecontroller.h
 *  @brief The editor main controller
 */

#include "svge.h"
#include <vector>

namespace svge {

class SvgeController
{
    public:
        SvgeController() : editor_(std::make_unique<Svge>()) {}
        ~SvgeController();

        item_id_t create_document() { return editor_->create_document(); }
        void export_document(const std::string& filename) {}
        void import_document(const std::string& filename) {}
        item_id_t create_item() {}
        void delete_item(item_id_t id) {}

    private:
        SvgeUPtr editor_;
};

}
