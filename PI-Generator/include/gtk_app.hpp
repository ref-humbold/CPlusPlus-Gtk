#ifndef GTK_APP_HPP_
#define GTK_APP_HPP_

#include <cstdlib>
#include <random>
#include <gtkmm.h>

class gtk_app
{
public:
    gtk_app();
    ~gtk_app();
    gtk_app(const gtk_app &) = delete;
    gtk_app(gtk_app &&) = delete;
    gtk_app & operator=(const gtk_app &) = delete;
    gtk_app & operator=(gtk_app &&) = delete;

    Gtk::Window & main_window()
    {
        return *main_window_;
    }

private:
    void get_components();
    void connect_signals();
    void close_button_clicked();
    void generate_button_clicked();
    double count_pi();
    long long int shoot_points(long long int throws);
    void set_progress_bar(double fraction);

    double pi_value;
    std::default_random_engine rand_eng;
    std::uniform_real_distribution<double> distribution;
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window_;
    Gtk::Button * close_button;
    Gtk::Button * generate_button;
    Gtk::ProgressBar * progress_bar;
    Gtk::Label * pi_value_label;
    Gtk::Label * error_value_label;
};

#endif
