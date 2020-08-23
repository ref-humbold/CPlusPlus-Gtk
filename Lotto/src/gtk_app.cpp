#include "gtk_app.hpp"
#include <iostream>
#include <string>
#include "files/lotto_glade.hpp"

using namespace std::string_literals;

gtk_app::gtk_app()
{
    try
    {
        builder = Gtk::Builder::create_from_string(lotto_glade);
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
    for(size_t i = 0; i < NUMBERS; ++i)
        delete number_buttons[i];

    delete run_button;
    delete next_button;
    delete close_button;
    delete draw_value_label;
    delete jackpot_value_label;
    delete results_label;
    delete main_window_;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window_);
    builder->get_widget("run_button", run_button);
    builder->get_widget("next_button", next_button);
    builder->get_widget("close_button", close_button);
    builder->get_widget("draw_value_label", draw_value_label);
    builder->get_widget("jackpot_value_label", jackpot_value_label);
    builder->get_widget("results_label", results_label);

    for(size_t i = 0; i < lotto_game::NUMBERS; ++i)
    {
        builder->get_widget("togglebutton_"s + std::to_string(i + 1), number_buttons[i]);
    }
}

void gtk_app::connect_signals()
{
    close_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::close_button_clicked));
    run_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::run_button_clicked));
    next_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::next_button_clicked));

    for(size_t i = 0; i < NUMBERS; ++i)
        number_buttons[i]->signal_toggled().connect(
                sigc::bind<size_t>(sigc::mem_fun(*this, &gtk_app::number_toggled), i + 1));
}

void gtk_app::run_button_clicked()
{
}

void gtk_app::next_button_clicked()
{
}

void gtk_app::close_button_clicked()
{
    main_window_->hide();
}

void gtk_app::number_toggled(size_t number)
{
    std::cout << "TOGGLED " << number << "\n";
}
