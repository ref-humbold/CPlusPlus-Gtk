#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <gtkmm.h>

#pragma region gtk_app

class gtk_app
{
private:
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window;

public:
    explicit gtk_app(std::string path);
    ~gtk_app();
    gtk_app(const gtk_app &) = delete;
    gtk_app(gtk_app &&) = delete;
    gtk_app & operator=(const gtk_app &) = delete;
    gtk_app & operator=(gtk_app &&) = delete;

private:
    void get_components();
    void connect_signals();
    void togglebutton_clicked_cb();
};

gtk_app::gtk_app(std::string path)
{
    try
    {
        this->builder = Gtk::Builder::create_from_file(path.append("/../lotto.glade"));
        this->get_components();
        this->connect_signals();
    }
    catch(const Glib::Exception & e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}

gtk_app::~gtk_app()
{
}

void gtk_app::get_components()
{
    this->builder->get_widget("main_window", this->main_window);
}

void gtk_app::connect_signals()
{
}

#pragma endregion

std::string extract_directory(const char * full_path)
{
    std::string exec_path = std::string(full_path);
    size_t dirpos = exec_path.find_last_of("/\\");

    return exec_path.substr(0, dirpos);
}

int main(int argc, char * argv[])
{
    Glib::RefPtr<Gtk::Application> application =
        Gtk::Application::create(argc, argv, "generator.liczby.pi");
    gtk_app app_window(extract_directory(argv[0]));

    application->run(app_window.get_main_window());

    return 0;
}
