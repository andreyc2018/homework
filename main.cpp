/**
 * @file main.cpp
 *  @brief All GUI handlers are here.
 *
 *  GUI events.
 */
#include "svge.h"

#include <iostream>
#include <string>

using svge::Svge;
using svge::shape_id_t;
using svge::shape_type_t;
using svge::shape_type_string;

/**
 * @brief The GuiApp class
 *
 * The main GUI class that receives comands from user interface.
 */
class GuiApp
{
    public:
        GuiApp() {}
        ~GuiApp() {}

        /**
         * @brief on_new_document
         *
         * New document requested
         */
        void on_new_document()
        {
            std::cout << ":: Creating new document\n";
            controller_.create_document();
            update_view();
        }

        void on_export_document(const std::string& filename)
        {
            std::cout << ":: Exporting document to a file " << filename << "\n";
            controller_.export_document(filename);
        }

        void on_import_document(const std::string& filename)
        {
            std::cout << ":: Importing document from a file " << filename << "\n";
            controller_.import_document(filename);
            update_view();
        }

        shape_id_t on_create_item(shape_type_t type)
        {
            std::cout << ":: Adding " << shape_type_string(type) << "\n";
            shape_id_t id = controller_.create_item(type);
            std::cout << ":: Added " << shape_type_string(type) << " id = " << id << "\n";
            update_view();
            return id;
        }

        void on_delete_item(shape_id_t id)
        {
            std::cout << ":: Deleting shape id = " << id << "\n";
            controller_.delete_item(id);
            update_view();
        }

        /**
         * @brief on_update_view
         *
         * Requests document info from a controller to update view.
         * Requested info is printed to stdout
         */
        void on_update_view()
        {
            controller_.request_document();
        }

    private:
        Svge controller_;

        /**
         * @brief update_view
         *
         * Notifies GUI that document was changed
         * The GUI will will send an update view request to all
         * components.
         */
        void update_view()
        {
            /* GUI sends an update request */
            on_update_view();
        }
};

int main(int, char const**)
{
    try {
        GuiApp app;
        app.on_new_document();
        app.on_create_item(shape_type_t::Point);
        app.on_create_item(shape_type_t::Vector);
        app.on_create_item(shape_type_t::Point);
        app.on_export_document("hello.svg");
        app.on_import_document("hello.svg");
        app.on_delete_item(2);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
