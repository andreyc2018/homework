#pragma once
/** @file svgecontroller.h
 *  @brief The editor main controller
 */

#include "svge.h"
#include "logger.h"
#include <vector>

namespace svge {

class SvgeController
{
    public:
        SvgeController(const LoggerPtr& logger) : logger_(logger), editor_(logger) {}
        ~SvgeController();

        void create_document()
        {
            editor_.create_document();
        }

        void export_document(const std::string& filename)
        {
            editor_.export_document(filename);
        }

        void import_document(const std::string& filename)
        {
            editor_.import_document(filename);
        }

        item_id_t create_item(item_type_t type)
        {
            return editor_.create_item(type);
        }

        void delete_item(item_id_t id)
        {
            editor_.delete_item(id);
        }

    private:
        LoggerPtr logger_;
        Svge editor_;
};

}
