#pragma once

#include "document.h"
#include "logger.h"
#include <fstream>

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
            std::ifstream file(filename, std::ios::binary);
            doc->read(file);
            return doc;
        }

        void export_document(const std::string& filename, const DocumentUPtr& doc)
        {
            std::ofstream file(filename, std::ios::binary);
            doc->write(file);
        }

    private:
        LoggerPtr logger_;
};

}
