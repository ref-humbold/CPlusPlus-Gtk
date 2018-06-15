#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <gtkmm.h>

class gtk_app
{
private:
    double pi_value;
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window;
    Gtk::Button * exit_button;
    Gtk::Button * continue_button;
    Gtk::ProgressBar * progress_bar;
    Gtk::Label * label_1b;
    Gtk::Label * label_2b;

public:
    gtk_app() : builder{Gtk::Builder::create_from_file("generator.glade")}
    {
        srand(time(nullptr));
        this->get_components();
        this->connect_signals();
    }

    ~gtk_app()
    {
        delete this->main_window;
        delete this->exit_button;
        delete this->continue_button;
        delete this->progress_bar;
        delete this->label_1b;
        delete this->label_2b;
    }

    Gtk::Window & get_main_window()
    {
        return *(this->main_window);
    }

private:
    void get_components();
    void connect_signals();
    void exit_button_clicked_cb();
    void continue_button_clicked_cb();
    double count_pi();
};

void gtk_app::get_components()
{
    this->builder->get_widget("main_window", this->main_window);
    this->builder->get_widget("exit_button", this->exit_button);
    this->builder->get_widget("continue_button", this->continue_button);
    this->builder->get_widget("progress_bar", this->progress_bar);
    this->builder->get_widget("label_1b", this->label_1b);
    this->builder->get_widget("label_2b", this->label_2b);
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
    label_1b->set_text(std::to_string(pi_value));
    label_2b->set_text(std::to_string(pi_value - M_PI));
}

double gtk_app::count_pi()
{
    long long int shot = 0;
    const long long int NUMBER = 1LL << 24;
    const long long int STEP = NUMBER >> 5;
    const int SIZE = 32750;

    for(long long int j = 1LL; j <= NUMBER / STEP; ++j)
    {
        for(long long int i = 0LL; i < STEP; ++i)
        {
            double pos_x = (rand() % SIZE) / (1.0 * SIZE);
            double pos_y = (rand() % SIZE) / (1.0 * SIZE);
            double radius = sqrt(pos_x * pos_x + pos_y * pos_y);

            if(radius <= 1.0)
                ++shot;
        }

        progress_bar->set_fraction(j * STEP * 100.0 / NUMBER);
    }

    return (4.0 * shot) / NUMBER;
}

int main()
{
    Glib::RefPtr<Gtk::Application> application = Gtk::Application::create("generator.liczby.pi");
    gtk_app app_window;

    application->run(app_window.get_main_window());

    return 0;
}
