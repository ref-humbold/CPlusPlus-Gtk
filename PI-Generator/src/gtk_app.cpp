#include "gtk_app.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include "files/generator_glade.hpp"

gtk_app::gtk_app() : distribution{0.0, 1.0}
{
    try
    {
        builder = Gtk::Builder::create_from_string(generator_glade);
        get_components();
        connect_signals();
    }
    catch(const Glib::Exception & e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }

    srand(time(nullptr));
}

gtk_app::~gtk_app()
{
    delete close_button;
    delete generate_button;
    delete progress_bar;
    delete pi_value_label;
    delete error_value_label;
    delete main_window_;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window_);
    builder->get_widget("close_button", close_button);
    builder->get_widget("generate_button", generate_button);
    builder->get_widget("progress_bar", progress_bar);
    builder->get_widget("pi_value_label", pi_value_label);
    builder->get_widget("error_value_label", error_value_label);
}

void gtk_app::connect_signals()
{
    close_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::close_button_clicked));
    generate_button->signal_clicked().connect(
            sigc::mem_fun(*this, &gtk_app::generate_button_clicked));
}

void gtk_app::close_button_clicked()
{
    main_window_->hide();
}

void gtk_app::generate_button_clicked()
{
    set_progress_bar(0.0);
    pi_value = count_pi();
    pi_value_label->set_text(std::to_string(pi_value));
    error_value_label->set_text(std::to_string(pi_value - M_PI));
}

double gtk_app::count_pi()
{
    long long int shots = 0LL;
    constexpr long long int total_number = 1LL << 24;
    constexpr long long int step = total_number >> 5;

    for(double j = 1.0; j <= total_number / step; ++j)
    {
        shots += shoot_points(step);
        set_progress_bar(j * step / total_number);
    }

    return (4.0 * shots) / total_number;
}

long long int gtk_app::shoot_points(long long int throws)
{
    long long int shots = 0LL;

    for(long long int i = 0LL; i < throws; ++i)
    {
        double pos_x = distribution(rand_eng);
        double pos_y = distribution(rand_eng);

        if(sqrt(pos_x * pos_x + pos_y * pos_y) <= 1.0)
            ++shots;
    }

    return shots;
}

void gtk_app::set_progress_bar(double fraction)
{
    progress_bar->set_fraction(fraction);
    Gtk::Main::iteration(false);
    Gtk::Main::iteration(false);
}
