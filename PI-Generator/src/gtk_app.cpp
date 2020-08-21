#include "gtk_app.hpp"
#include "files/generator_glade.hpp"

gtk_app::gtk_app()
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
    delete main_window_;
    delete exit_button;
    delete continue_button;
    delete progress_bar;
    delete pi_value_label;
    delete error_value_label;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window_);
    builder->get_widget("exit_button", exit_button);
    builder->get_widget("continue_button", continue_button);
    builder->get_widget("progress_bar", progress_bar);
    builder->get_widget("pi_value_label", pi_value_label);
    builder->get_widget("error_value_label", error_value_label);
}

void gtk_app::connect_signals()
{
    exit_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::exit_button_clicked_cb));
    continue_button->signal_clicked().connect(
            sigc::mem_fun(*this, &gtk_app::continue_button_clicked_cb));
}

void gtk_app::exit_button_clicked_cb()
{
    main_window_->hide();
}

void gtk_app::continue_button_clicked_cb()
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
    constexpr int size = 32750;

    for(long long int i = 0LL; i < throws; ++i)
    {
        double pos_x = (rand() % size) / (1.0 * size);
        double pos_y = (rand() % size) / (1.0 * size);
        double radius = sqrt(pos_x * pos_x + pos_y * pos_y);

        if(radius <= 1.0)
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
