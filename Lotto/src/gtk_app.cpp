#include "gtk_app.hpp"
#include "files/lotto_glade.hpp"

gtk_app::gtk_app()
{
    try
    {
        builder = Gtk::Builder::create_from_string(std::string(lotto_glade, lotto_glade_len));
        get_components();
        connect_signals();
    }
    catch(const Glib::Exception & e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}

gtk_app::~gtk_app()
{
    delete main_window;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window);
}

void gtk_app::connect_signals()
{
}
