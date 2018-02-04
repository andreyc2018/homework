/** @file main.cpp
 *  @brief All GUI handlers are here.
 *
 *  GUI events.
 */
#include "svgecontroller.h"
#include <iostream>
#include <string>

using svge::SvgeController;
using svge::item_id_t;

class GuiApp
{
    public:
        GuiApp() {}
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

        void on_create_item()
        {
            controller_.create_item();
        }

        void on_delete_item(item_id_t id)
        {
            controller_.delete_item(id);
        }

    private:
        SvgeController controller_;
};

int main(int, char const**)
{
    try {
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
