#pragma once
/**
 * @file svge.h
 */

#include "document.h"
#include "storage.h"
#include "logger.h"

namespace svge {

/**
 * @brief Simple Vector Graphics Editor
 *
 * Contains a document and storage subsystem
 */
class Svge
{
    public:
        Svge() {}
        ~Svge() {}

        void create_document()
        {
            doc_ = std::make_unique<Document>();
        }

        void export_document(const std::string& filename)
        {
            if (doc_->modified()) {
                storage_.export_document(filename, doc_);
            }
        }

        void import_document(const std::string& filename)
        {
            doc_ = storage_.import_document(filename);
        }

        shape_id_t create_item(shape_type_t type)
        {
            return doc_->create_item(type);
        }

        void delete_item(shape_id_t id)
        {
            doc_->delete_item(id);
        }

        void request_document()
        {
            doc_->collect_items();
        }

    private:
        DocumentUPtr doc_;
        Storage storage_;
};

}
