#ifndef GTK_APP_HPP_
#define GTK_APP_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <gtkmm.h>
#include "converter.hpp"

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
    void convert_button_clicked();

    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window_;
    Gtk::Button * convert_button;
    Gtk::Button * close_button;
    Gtk::Label * result_label;
    Gtk::Entry * value_entry;
    Gtk::SpinButton * base_value_spinbutton;
    Gtk::SpinButton * base_result_spinbutton;
};

#endif
