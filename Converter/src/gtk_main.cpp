#include <cstdlib>
#include <string>
#include "gtk_app.hpp"

std::string extract_directory(const char * full_path)
{
    std::string exec_path = std::string(full_path);
    size_t dirpos = exec_path.find_last_of("/\\");

    return exec_path.substr(0, dirpos);
}

int main(int argc, char * argv[])
{
    Glib::RefPtr<Gtk::Application> application = Gtk::Application::create(argc, argv, "converter");
    gtk_app app_window(extract_directory(argv[0]));

    application->run(app_window.get_main_window());

    return 0;
}
