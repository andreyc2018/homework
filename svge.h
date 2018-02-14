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
            TRACE();
            // There is no checking if the document contains any modifications.
            // std::make_unique() is not available on Travis
            doc_.reset(new Document);
        }

        void export_document(const std::string& filename)
        {
            storage_.export_document(filename, doc_);
        }

        void import_document(const std::string& filename)
        {
            doc_ = storage_.import_document(filename);
        }

        shape_id_t create_item(shape_type_t type)
        {
            return doc_->create_item(type);
        }

//        void delete_item(item_id_t id)
//        {
//            doc_->delete_item(id);
//        }

    private:
        DocumentUPtr doc_;
        Storage storage_;
};

}
