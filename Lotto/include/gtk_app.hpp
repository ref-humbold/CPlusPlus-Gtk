#ifndef GTK_APP_HPP_
#define GTK_APP_HPP_

#include <cstdlib>
#include <vector>
#include <gtkmm.h>
#include "lotto_game.hpp"

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
    void activate_numbers(bool active);
    void run_button_clicked();
    void next_button_clicked();
    void close_button_clicked();
    void number_toggled(size_t number);

    lotto_game game;

    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window_;
    std::vector<Gtk::ToggleButton *> number_buttons;
    Gtk::Button * run_button;
    Gtk::Button * next_button;
    Gtk::Button * close_button;
    Gtk::Label * draw_value_label;
    Gtk::Label * jackpot_value_label;
    Gtk::Label * result_value_label;
    Gtk::Label * matched_value_label;
    Gtk::Label * next_jackpot_value_label;
};

#endif
