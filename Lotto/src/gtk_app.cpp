#include "gtk_app.hpp"
#include <iostream>
#include <set>
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
        next_button_clicked();
    }
    catch(const Glib::Exception & e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}

gtk_app::~gtk_app()
{
    for(auto && btn : number_buttons)
        delete btn;

    delete run_button;
    delete next_button;
    delete close_button;
    delete draw_value_label;
    delete jackpot_value_label;
    delete result_value_label;
    delete matched_value_label;
    delete next_jackpot_value_label;
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
    builder->get_widget("result_value_label", result_value_label);
    builder->get_widget("matched_value_label", matched_value_label);
    builder->get_widget("next_jackpot_value_label", next_jackpot_value_label);

    for(size_t i = 0; i < lotto_game::TOTAL_NUMBERS; ++i)
    {
        Gtk::ToggleButton * btn;

        builder->get_widget("togglebutton_"s + std::to_string(i + 1), btn);
        number_buttons.push_back(btn);
    }
}

void gtk_app::connect_signals()
{
    close_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::close_button_clicked));
    run_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::run_button_clicked));
    next_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::next_button_clicked));

    for(size_t i = 0; i < number_buttons.size(); ++i)
        number_buttons[i]->signal_toggled().connect(
                sigc::bind<size_t>(sigc::mem_fun(*this, &gtk_app::number_toggled), i));
}

void gtk_app::run_button_clicked()
{
    std::set<size_t> result = game.run();
    size_t matched = game.check(result);
    size_t next_jackpot = game.count_jackpot(matched);

    result_value_label->set_text("");
    matched_value_label->set_text(std::to_string(matched));
    next_jackpot_value_label->set_text(std::to_string(next_jackpot));
    next_button->set_sensitive(true);
    run_button->set_sensitive(false);

    for(auto && btn : number_buttons)
        btn->set_sensitive(false);
}

void gtk_app::next_button_clicked()
{
    for(auto && btn : number_buttons)
        btn->set_active(false);

    game.start();

    draw_value_label->set_text(std::to_string(game.run_number()));
    jackpot_value_label->set_text(std::to_string(game.jackpot()));
    result_value_label->set_text("");
    matched_value_label->set_text("");
    next_jackpot_value_label->set_text("");
    next_button->set_sensitive(false);
    run_button->set_sensitive(false);

    for(auto && btn : number_buttons)
        btn->set_sensitive(true);
}

void gtk_app::close_button_clicked()
{
    main_window_->hide();
}

void gtk_app::number_toggled(size_t number)
{
    game.toggle(number);

    if(game.count_chosen() >= lotto_game::DRAW_NUMBERS)
    {
        unsigned long long int chosen = game.mask();

        run_button->set_sensitive(true);

        for(size_t i = 0; i < number_buttons.size(); ++i)
            number_buttons[i]->set_sensitive((chosen & (1ULL << i)) == (1ULL << i));
    }
    else if(game.count_chosen() == lotto_game::DRAW_NUMBERS - 1 && !game.is_chosen(number))
    {
        run_button->set_sensitive(false);

        for(auto && btn : number_buttons)
            btn->set_sensitive(true);
    }
}
