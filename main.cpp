/**
 * @file main.cpp
 *  @brief All GUI handlers are here.
 *
 *  GUI events.
 */
#include "svge.h"
#include "logger.h"

#include <iostream>
#include <string>

using svge::Svge;
using svge::gp_id_t;
using svge::gs_type_t;

LoggerPtr gLogger = spdlog::stdout_logger_mt("console");

class GuiApp
{
    public:
        GuiApp() {}
        ~GuiApp() {}

        void on_new_document()
        {
            TRACE();
            controller_.create_document();
            gLogger->info("created new document");
        }

//        void on_export_document(const std::string& filename)
//        {
//            controller_.export_document(filename);
//            gLogger->info("exported document to a file {}", filename);
//        }

//        void on_import_document(const std::string& filename)
//        {
//            controller_.import_document(filename);
//        }

//        void on_create_item(item_type_t type)
//        {
//            item_id_t id = controller_.create_item(type);
//            gLogger->info("Added item id = {}", id);
//        }

//        void on_delete_item(item_id_t id)
//        {
//            controller_.delete_item(id);
//        }

    private:
        Svge controller_;
};

int main(int, char const**)
{
    try {
        GuiApp app;
        app.on_new_document();

    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
