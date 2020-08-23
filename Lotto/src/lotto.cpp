#include <cstdlib>
#include <string>
#include "gtk_app.hpp"

int main(int argc, char * argv[])
{
    Glib::RefPtr<Gtk::Application> application = Gtk::Application::create(argc, argv, "Lotto");
    gtk_app app_window;

    application->run(app_window.main_window());

    return 0;
}
