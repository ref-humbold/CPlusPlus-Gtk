#include <cstdlib>
#include <string>
#include "gtk_app.hpp"

int main(int argc, char * argv[])
{
    Glib::RefPtr<Gtk::Application> application =
            Gtk::Application::create(argc, argv, "pi.generator");
    gtk_app app_window;

    application->run(app_window.get_main_window());

    return 0;
}
