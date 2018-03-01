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

        void export_document(const std::string& filename, const DocumentUPtr& doc)
        {
            std::ofstream file(filename, std::ios::binary);
            doc->write(file);
            file.close();
        }

        DocumentUPtr import_document(const std::string& filename)
        {
            auto doc = std::make_unique<Document>();
            std::ifstream file(filename, std::ios::binary);
            doc->read(file);
            file.close();
            return doc;
        }
};

}
