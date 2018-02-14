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
using svge::shape_id_t;
using svge::shape_type_t;

LoggerPtr gLogger = spdlog::stdout_logger_mt("console", true);

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

        void on_export_document(const std::string& filename)
        {
            controller_.export_document(filename);
            gLogger->info("exported document to a file {}", filename);
        }

        void on_import_document(const std::string& filename)
        {
            controller_.import_document(filename);
            gLogger->info("imported document from a file {}", filename);
        }

        shape_id_t on_create_item(shape_type_t type)
        {
            shape_id_t id = controller_.create_item(type);
            gLogger->info("Added item id = {}", id);
            return id;
        }

//        void on_delete_item(gp_id_t id)
//        {
//            controller_.delete_item(id);
//        }

    private:
        Svge controller_;
};

int main(int argc, char const**)
{
    try {
        if (argc > 1)
            gLogger->set_level(spdlog::level::trace);
        GuiApp app;
        app.on_new_document();
        app.on_create_item(shape_type_t::Point);
        app.on_create_item(shape_type_t::Vector);
        app.on_export_document("hello.svg");
        app.on_import_document("hello.svg");
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
