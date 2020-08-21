#include "gtk_app.hpp"
#include "files/converter_glade.hpp"

using namespace std::string_literals;

gtk_app::gtk_app()
try
{
    builder = Gtk::Builder::create_from_string(converter_glade);
    get_components();
    connect_signals();
}
catch(const Glib::Exception & e)
{
    std::cerr << e.what() << '\n';
    throw;
}

gtk_app::~gtk_app()
{
    delete main_window_;
    delete exit_button;
    delete convert_button;
    delete result_label;
    delete value_entry;
    delete base_value_spinbutton;
    delete base_result_spinbutton;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window_);
    builder->get_widget("exit_button", exit_button);
    builder->get_widget("convert_button", convert_button);
    builder->get_widget("result_label", result_label);
    builder->get_widget("value_entry", value_entry);
    builder->get_widget("base_value_spinbutton", base_value_spinbutton);
    builder->get_widget("base_result_spinbutton", base_result_spinbutton);
}

void gtk_app::connect_signals()
{
    exit_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::exit_button_clicked_cb));
    convert_button->signal_clicked().connect(
            sigc::mem_fun(*this, &gtk_app::convert_button_clicked_cb));
}

void gtk_app::exit_button_clicked_cb()
{
    main_window_->hide();
}

void gtk_app::convert_button_clicked_cb()
{
    std::string input = value_entry->get_text();
    std::string result;

    try
    {
        std::string value = converter(base_value_spinbutton->get_value_as_int(),
                                      base_result_spinbutton->get_value_as_int())
                                    .convert(input);

        result = input + "\n|||\n"s + value;
    }
    catch(const converter_exception & e)
    {
        result = "ERROR: "s + e.what();
    }

    value_entry->set_text("");
    result_label->set_text(result);
}
