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
    delete main_window;
    delete exit_button;
    delete continue_button;
    delete progress_bar;
    delete label_B1;
    delete label_B2;
}

void gtk_app::get_components()
{
    builder->get_widget("main_window", main_window);
    builder->get_widget("exit_button", exit_button);
    builder->get_widget("continue_button", continue_button);
    builder->get_widget("progress_bar", progress_bar);
    builder->get_widget("label_B1", label_B1);
    builder->get_widget("label_B2", label_B2);
}

void gtk_app::connect_signals()
{
    exit_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::exit_button_clicked_cb));
    continue_button->signal_clicked().connect(
            sigc::mem_fun(*this, &gtk_app::continue_button_clicked_cb));
}

void gtk_app::exit_button_clicked_cb()
{
    main_window->hide();
}

void gtk_app::continue_button_clicked_cb()
{
    progress_bar->set_fraction(0.0);
    pi_value = count_pi();
    label_B1->set_text(std::to_string(pi_value));
    label_B2->set_text(std::to_string(pi_value - M_PI));
}

double gtk_app::count_pi()
{
    long long int shots = 0LL;
    const long long int NUMBER = 1LL << 24;
    const long long int STEP = NUMBER >> 5;

    for(long long int j = 1LL; j <= NUMBER / STEP; ++j)
    {
        shots += shoot_points(STEP);
        progress_bar->set_fraction(j * STEP * 100.0 / NUMBER);
    }

    return (4.0 * shots) / NUMBER;
}

long long int gtk_app::shoot_points(long long int throws)
{
    long long int shots = 0LL;
    const int SIZE = 32750;

    for(long long int i = 0LL; i < throws; ++i)
    {
        double pos_x = (rand() % SIZE) / (1.0 * SIZE);
        double pos_y = (rand() % SIZE) / (1.0 * SIZE);
        double radius = sqrt(pos_x * pos_x + pos_y * pos_y);

        if(radius <= 1.0)
            ++shots;
    }

    return shots;
}
