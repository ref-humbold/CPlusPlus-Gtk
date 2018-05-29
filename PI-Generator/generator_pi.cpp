#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <gtkmm.h>

class gtk_app
{
private:
    Glib::RefPtr<Gtk::Application> application;
    Glib::RefPtr<Gtk::Builder> builder;

public:
    gtk_app()
        : application{Gtk::Application::create()},
          builder{Gtk::Builder::create_from_file("generator.glade", "main_window")}
    {
    }
};

void exit_button_clicked_cb()
{
}

void continue_button_clicked_cb()
{
}

double pi()
{
    long long int shot = 0;
    const long long int NUMBER = 1LL << 24;
    const int SIZE = 32750;

    for(long long int i = 0LL; i < NUMBER; ++i)
    {
        double pos_x = (rand() % SIZE) / (1.0 * SIZE);
        double pos_y = (rand() % SIZE) / (1.0 * SIZE);
        double radius = sqrt(pos_x * pos_x + pos_y * pos_y);

        if(i % 1000000 == 0)
        {
            for(int j = 0; j < i / 1000000; ++j)
                printf("#");

            printf("\n");
        }

        if(radius <= 1.0)
            ++shot;
    }

    printf("\n");

    return (4.0 * shot) / NUMBER;
}

int main()
{
    char read = ' ';

    printf("\t\tGENERATOR LICZBY PI\n");
    srand(time(nullptr));

    do
    {
        double pi_value = pi();

        printf("    PI = %lf  (absolute error = %lf)\n\n", pi_value, pi_value - M_PI);

        do
        {
            if(read != '\n')
                printf("  Write Q to exit, C to continue and press ENTER\n>>> ");

            scanf("%c", &read);
        } while(read != 'q' && read != 'Q' && read != 'c' && read != 'C');
    } while(read != 'q' && read != 'Q');

    return 0;
}
