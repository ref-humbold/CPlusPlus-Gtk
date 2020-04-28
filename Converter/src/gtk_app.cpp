#include "gtk_app.hpp"
#include "files/converter_glade.hpp"

using namespace std::string_literals;

gtk_app::gtk_app()
{
    try
    {
        builder =
                Gtk::Builder::create_from_string(std::string(converter_glade, converter_glade_len));
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
    delete exit_button;
    delete convert_button;
    delete result_label;
    delete entry_B1;
    delete spinbutton_B2;
    delete spinbutton_B3;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window);
    builder->get_widget("exit_button", exit_button);
    builder->get_widget("convert_button", convert_button);
    builder->get_widget("result_label", result_label);
    builder->get_widget("entry_B1", entry_B1);
    builder->get_widget("spinbutton_B2", spinbutton_B2);
    builder->get_widget("spinbutton_B3", spinbutton_B3);
}

void gtk_app::connect_signals()
{
    exit_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::exit_button_clicked_cb));
    convert_button->signal_clicked().connect(
            sigc::mem_fun(*this, &gtk_app::convert_button_clicked_cb));
}

void gtk_app::exit_button_clicked_cb()
{
    main_window->hide();
}

void gtk_app::convert_button_clicked_cb()
{
    std::string input = entry_B1->get_text();
    std::string result = input + "\n=>\n"s;

    try
    {
        result += converter(spinbutton_B2->get_value_as_int(), spinbutton_B3->get_value_as_int())
                          .convert(input);
    }
    catch(const converter_exception & e)
    {
        result += "ERROR: "s + e.what();
    }

    entry_B1->set_text("");
    result_label->set_text(result);
}
