#ifndef _GTK_APP_HPP_
#define _GTK_APP_HPP_

#include <cstdlib>
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
        return *(this->main_window);
    }

private:
    void get_components();
    void connect_signals();
    void exit_button_clicked_cb();
    void convert_button_clicked_cb();

    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window;
    Gtk::Button * convert_button;
    Gtk::Button * exit_button;
    Gtk::Label * result_label;
    Gtk::Entry * entry_B1;
    Gtk::SpinButton * spinbutton_B2;
    Gtk::SpinButton * spinbutton_B3;
};

#endif
