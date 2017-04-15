#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <unistd.h>

double gen()
{
    int traf = 0, number = 1LL<<24;

    srand(time(NULL));

    for(long long int i = 0; i < number; ++i)
    {
        double x = (rand()%32750)/32750.0, y = (rand()%32750)/32750.0;
        double odl = sqrt(x*x+y*y);

        if(odl <= 1)
            ++traf;
    }

    return (4.0*traf)/number;
}

int main()
{
    double pi;

    std::cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n\n";
    std::cout << "\t\tGENERATOR LICZBY PI\n";

    while(true)
    {
        pi = gen();
        std::cout << "\n\n" << "PI = " << pi << "\n" << "odchylenie wynosi " << pi-3.141592 << "\n";
        sleep(3);
    }

    return 0;
}
