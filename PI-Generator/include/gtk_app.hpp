#ifndef GTK_APP_HPP_
#define GTK_APP_HPP_

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <gtkmm.h>

class gtk_app
{
public:
    explicit gtk_app(std::string path);
    ~gtk_app();
    gtk_app(const gtk_app &) = delete;
    gtk_app(gtk_app &&) = delete;
    gtk_app & operator=(const gtk_app &) = delete;
    gtk_app & operator=(gtk_app &&) = delete;

    Gtk::Window & get_main_window()
    {
        return *main_window;
    }

private:
    void get_components();
    void connect_signals();
    void exit_button_clicked_cb();
    void continue_button_clicked_cb();
    double count_pi();
    long long int shoot_points(long long int throws);

    double pi_value;
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window;
    Gtk::Button * exit_button;
    Gtk::Button * continue_button;
    Gtk::ProgressBar * progress_bar;
    Gtk::Label * label_B1;
    Gtk::Label * label_B2;
};

#endif