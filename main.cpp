/**
 * @file main.cpp
 *  @brief All GUI handlers are here.
 *
 *  GUI events.
 */
#include "svgecontroller.h"
#include "logger.h"

#include <iostream>
#include <string>

using svge::SvgeController;
using svge::item_id_t;
using svge::item_type_t;

class GuiApp
{
    public:
        GuiApp(const LoggerPtr& logger) : logger_(logger), controller_(logger) {}
        ~GuiApp() {}

        void on_new_document()
        {
            controller_.create_document();
        }

        void on_export_document(const std::string& filename)
        {
            controller_.export_document(filename);
        }

        void on_import_document(const std::string& filename)
        {
            controller_.import_document(filename);
        }

        void on_create_item(item_type_t type)
        {
            item_id_t id = controller_.create_item(type);
            logger_->info("Added item id = {}", id);
        }

        void on_delete_item(item_id_t id)
        {
            controller_.delete_item(id);
        }

    private:
        LoggerPtr logger_;
        SvgeController controller_;
};

int main(int, char const**)
{
    try {
        auto console = spdlog::stdout_logger_mt("console");
        GuiApp app(console);
        app.on_new_document();

    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
