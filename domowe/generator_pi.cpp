#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <ctime>
#include <unistd.h>

using namespace std;

double gen()
{
	int traf=0;
	
	srand( time(0) );

	for(long long int e=0;e<10000000;e++)
	{
		double x=(rand()%32750)/32750.0, y=(rand()%32750)/32750.0, odl=hypot(x, y);

		if(odl<=1)
			traf++;
	}

	return (4.0*traf)/10000000;
}

int main()
{
	double d, pi;
	char c;
	
	cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n\n";
	cout << "\t\tGENERATOR LICZBY PI\n";

	while(true)
	{
		pi=gen();
		d=pi-3.141592;

		cout << "\n\n" << "PI = " << pi << "\n" << "odchylenie wynosi " << d << "\n";
		sleep(3);	
	}

	return 0;
}
