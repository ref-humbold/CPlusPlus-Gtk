#ifndef GTK_APP_HPP_
#define GTK_APP_HPP_

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
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

private:
    void get_components();
    void connect_signals();
    void togglebutton_clicked_cb();

    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window;
};

#endif
