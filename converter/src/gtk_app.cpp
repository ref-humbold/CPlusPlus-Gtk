#include "gtk_app.hpp"

using namespace std::string_literals;

gtk_app::gtk_app(std::string path)
{
    try
    {
        this->builder = Gtk::Builder::create_from_file(path.append("/../converter.glade"));
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
    delete this->main_window;
    delete this->exit_button;
    delete this->convert_button;
    delete this->result_label;
    delete this->entry_B1;
    delete this->spinbutton_B2;
    delete this->spinbutton_B3;
}

void gtk_app::get_components()
{
    this->builder->get_widget("main_window", this->main_window);
    this->builder->get_widget("exit_button", this->exit_button);
    this->builder->get_widget("convert_button", this->convert_button);
    this->builder->get_widget("result_label", this->result_label);
    this->builder->get_widget("entry_B1", this->entry_B1);
    this->builder->get_widget("spinbutton_B2", this->spinbutton_B2);
    this->builder->get_widget("spinbutton_B3", this->spinbutton_B3);
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
    std::string result;

    try
    {
        converter conv(entry_B1->get_text(), spinbutton_B2->get_value_as_int(),
                       spinbutton_B3->get_value_as_int());

        result = conv.convert();
    }
    catch(const converter_exception & e)
    {
        result = "ERROR: "s + e.what();
    }

    entry_B1->set_text("");
    result_label->set_text(result);
}
