#pragma once

#include "document.h"
#include "logger.h"

namespace svge {

class Storage
{
    public:
        Storage(const LoggerPtr& logger) : logger_(logger) {}
        ~Storage() {}

        DocumentUPtr import_document(const std::string& filename)
        {
            auto doc = std::make_unique<Document>(logger_);
            logger_->info("Import document from file {}", filename);
            return doc;
        }

        void export_document(const std::string& filename, const DocumentUPtr& doc)
        {
            logger_->info("Export document {} to file {}", doc, filename);
        }

    private:
        LoggerPtr logger_;
};

}
