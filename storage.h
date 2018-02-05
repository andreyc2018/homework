#pragma once

#include "document.h"
#include "logger.h"
#include <fstream>

namespace svge {

class Storage
{
    public:
        Storage() {}
        ~Storage() {}

        DocumentUPtr import_document(const std::string& filename)
        {
            TRACE();
            auto doc = std::make_unique<Document>();
//            gLogger->info("Import document from file {}", filename);
//            std::ifstream file(filename, std::ios::binary);
//            doc->read(file);
            return doc;
        }

        void export_document(const std::string& filename, const DocumentUPtr& doc)
        {
            TRACE();
            std::ofstream file(filename, std::ios::binary);
//            doc->write(file);
        }
};

}
