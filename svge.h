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
        Svge(const LoggerPtr& logger)
            : logger_(logger)
            , doc_(std::make_unique<Document>(logger))
            , storage_(logger) {}
        ~Svge() {}

        void create_document()
        {
            // There is no checking if the document contains some modifications.
            // Just clean it up and move forward.
            doc_->reset();
        }

        void export_document(const std::string& filename)
        {
            storage_.export_document(filename, doc_);
        }

        void import_document(const std::string& filename)
        {
            doc_ = storage_.import_document(filename);
        }

        item_id_t create_item(item_type_t type)
        {
            doc_->create_item(type);
        }

        void delete_item(item_id_t id)
        {
            doc_->delete_item(id);
        }

    private:
        LoggerPtr logger_;
        DocumentUPtr doc_;
        Storage storage_;

};

}
