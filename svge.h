#pragma once
/**
 * @file svge.h
 *
 * Controller
 */

#include "document.h"
#include "storage.h"

namespace svge {

/**
 * @brief Simple Vector Graphics Editor
 *
 * Main controller.
 * Contains a document and storage subsystem
 */
class Svge
{
    public:
        Svge() : storage_(std::make_unique<Storage>()) {}
        ~Svge() {}

        void create_document()
        {
            doc_ = std::make_unique<Document>();
        }

        void export_document(const std::string& filename)
        {
            if (doc_->modified()) {
                storage_->export_document(filename, doc_);
            }
        }

        void import_document(const std::string& filename)
        {
            doc_ = storage_->import_document(filename);
        }

        shape_id_t create_item(shape_type_t type)
        {
            return doc_->create_shape(type);
        }

        void delete_item(shape_id_t id)
        {
            doc_->delete_item(id);
        }

        void request_document()
        {
            doc_->collect_items();
        }

        void set_storage(StorageUPtr& storage)
        {
            storage_.swap(storage);
        }

    private:
        DocumentUPtr doc_;
        StorageUPtr storage_;
};



}
