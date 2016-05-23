#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int base_in, base_out, dz, w;
	bool czy;
	vector <int> nsys;
	string num;
	
	cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n\n";
	cout << "\t\tCONVERTER SYSTEMÓW LICZBOWYCH\n\n";

	do
	{
		do
		{
			cout << "Podaj liczbę dodatnią do zamiany\n";
			cin >> num;
			czy=true;

			do
			{
				cout << "Podaj podstawę systemu Twojej liczby\n";
				cin >> base_in;
				cout << "\n";

				if(base_in<2 || base_in>16)
					cout << "Podaj podstawe z zakresu 2 - 16\n";
			}
			while(base_in<2 || base_in>16);

			for(int i=0;i<num.length();i++)
				if( num[i]<'0' || (num[i]>(char)min(57, base_in+47) && num[i]<'A') || (num[i]>(char)max(64, base_in+54) && num[i]<'a') || num[i]>(char)max(96, base_in+86) )
				{
					cout << "Podano niewłaściwą liczbę\n\n";
					czy=false;
					break;
				}
		}
		while(!czy);
		
		w=1;
		dz=0;

		for(int i=num.length()-1;i>=0;i--)
		{			
			if( (int)num[i]>='0' && (int)num[i]<='9' )
				dz=dz+((int)num[i]-'0')*w;
			else if( (int)num[i]>='A' && (int)num[i]<='F' )
				dz=dz+((int)num[i]-'A'+10)*w;
			else if( (int)num[i]>='a' && (int)num[i]<='f' )
				dz=dz+((int)num[i]-'a'+10)*w;
			
			w=w*base_in;
		}

		if(dz<0 || dz>1000000000)
			cout << "Liczba jest poza zakresem\n\n";
	}
	while(dz<0 || dz>1000000000);

	do
	{
		cout << "\n" << "Podaj podstawę systemu, na który chcesz zamienić tę liczbę\n";
		cin >> base_out;
		cout << "\n\n";

		if(base_out<2 || base_out>16)
			cout << "Podaj podstawe z zakresu 2 - 16\n";
	}
	while(base_out<2 || base_out>16);

	do
	{
		nsys.push_back(dz%base_out);
		dz=dz/base_out;
	}
	while(dz!=0);

	cout << "\tTwoja liczba w systemie o podstawie " << base_out << " wynosi:\n\n" << "\t\t";

	for(int i=nsys.size()-1;i>=0;i--)
		if(nsys[i]<10)
			cout << (char)(nsys[i]+48);
		else
			cout << (char)(nsys[i]+55);

	cout << "\n\n";
	
	return 0;
}

