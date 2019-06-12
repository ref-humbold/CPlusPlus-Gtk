#include "gtk_app.hpp"

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
