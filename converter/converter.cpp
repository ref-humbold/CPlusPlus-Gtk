#include <cstdlib>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include <gtkmm.h>

class converter_exception : public std::logic_error
{
public:
    explicit converter_exception(const std::string & s) : std::logic_error(s)
    {
    }

    explicit converter_exception(const char * s) : std::logic_error(s)
    {
    }
};

#pragma region converter

class converter
{
    std::string number_in;
    int base_in, base_out;
    bool has_sign;

public:
    converter(std::string number_in, int base_in, int base_out)
        : number_in{number_in}, base_in{base_in}, base_out{base_out}
    {
        this->has_sign = number_in[0] == '-' || number_in[0] == '+';
        this->validate_digits();
    }

    ~converter() = default;
    converter(converter &&) = delete;
    converter(const converter &) = delete;
    converter & operator=(converter &&) = delete;
    converter & operator=(const converter &) = delete;

    std::string convert();

private:
    void validate_digits();
    int to_decimal();
    void validate_size(int decimal);
    std::vector<int> to_base_out(int decimal);
    std::string build_number(const std::vector<int> & number);
};

std::string converter::convert()
{
    if(base_in == base_out)
        return number_in;

    int decimal = to_decimal();

    validate_size(decimal);

    std::vector<int> number_out = to_base_out(decimal);

    return build_number(number_out);
}

void converter::validate_digits()
{
    size_t digits_begin = has_sign ? 1 : 0;
    char max_dec = (char)std::min(57, base_in + 47);
    char max_big_hex = (char)std::max(64, base_in + 54);
    char max_small_hex = (char)std::max(96, base_in + 86);

    if(number_in.length() == digits_begin)
        throw converter_exception("Nie podano żadnej liczby.");

    for(auto it = number_in.begin() + digits_begin; it != number_in.end(); ++it)
    {
        if(*it < '0' || (*it > max_dec && *it < 'A') || (*it > max_big_hex && *it < 'a')
           || *it > max_small_hex)
            throw converter_exception("Znak \'" + std::string(1, *it)
                                      + "\' niewłaściwy dla podanego systemu liczbowego.");
    }
}

void converter::validate_size(int decimal)
{
    if(abs(decimal) > 2000000000)
        throw converter_exception("Liczba poza przewidywanym zakresem wejścia.\n");
}

int converter::to_decimal()
{
    auto actual_digit = [](const char & d) {
        if(d >= '0' && d <= '9')
            return +d - '0';

        if(d >= 'A' && d <= 'F')
            return +d - 'A' + 10;

        if(d >= 'a' && d <= 'f')
            return +d - 'a' + 10;

        return 0;
    };

    return std::accumulate(number_in.begin(), number_in.end(), 0, [=](int decimal, const char & d) {
        return decimal * base_in + actual_digit(d);
    });
}

std::vector<int> converter::to_base_out(int decimal)
{
    std::vector<int> output;

    do
    {
        output.push_back(decimal % base_out);
        decimal /= base_out;
    } while(decimal != 0);

    return output;
}

std::string converter::build_number(const std::vector<int> & number)
{
    std::string result;

    if(has_sign && number_in[0] == '-')
        result.push_back('-');

    for(auto it = number.rbegin(); it != number.rend(); ++it)
    {
        int shift = *it < 10 ? '0' : 'A';
        char out_code = *it % 10 + shift;

        result.push_back(out_code);
    }

    return result;
}

#pragma endregion
#pragma region gtk_app

class gtk_app
{
private:
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window * main_window;
    Gtk::Button * convert_button;
    Gtk::Button * exit_button;
    Gtk::Label * result_label;
    Gtk::Entry * entry1b;
    Gtk::SpinButton * spinbutton2b;
    Gtk::SpinButton * spinbutton3b;

public:
    gtk_app() : builder{Gtk::Builder::create_from_file("../converter.glade")}
    {
        this->get_components();
        this->connect_signals();
    }

    ~gtk_app()
    {
        delete this->main_window;
        delete this->exit_button;
        delete this->convert_button;
        delete this->result_label;
        delete this->entry1b;
        delete this->spinbutton2b;
        delete this->spinbutton3b;
    }

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
};

void gtk_app::get_components()
{
    this->builder->get_widget("main_window", this->main_window);
    this->builder->get_widget("exit_button", this->exit_button);
    this->builder->get_widget("convert_button", this->convert_button);
    this->builder->get_widget("result_label", this->result_label);
    this->builder->get_widget("entry1b", this->entry1b);
    this->builder->get_widget("spinbutton2b", this->spinbutton2b);
    this->builder->get_widget("spinbutton3b", this->spinbutton3b);
}

void gtk_app::connect_signals()
{
    exit_button->signal_clicked().connect(sigc::mem_fun(*this, &gtk_app::exit_button_clicked_cb));
    convert_button->signal_clicked().connect(
        sigc::mem_fun(*this, &gtk_app::convert_button_clicked_cb));
}

void gtk_app::exit_button_clicked_cb()
{
    main_window->hide();
}

void gtk_app::convert_button_clicked_cb()
{
    std::string result;

    try
    {
        converter conv(entry1b->get_text(), spinbutton2b->get_value_as_int(),
                       spinbutton3b->get_value_as_int());

        result = conv.convert();
    }
    catch(const converter_exception & e)
    {
        result = "ERROR!\n" + std::string(e.what());
    }

    entry1b->set_text("");
    result_label->set_text(result);
}

#pragma endregion

int main()
{
    Glib::RefPtr<Gtk::Application> application = Gtk::Application::create("converter.liczbowy");
    gtk_app app_window;

    application->run(app_window.get_main_window());

    return 0;
}
