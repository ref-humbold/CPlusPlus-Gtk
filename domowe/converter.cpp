#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

void check_base(int base)
{
	if(base < 2 || base > 16)
		throw runtime_error("Podstawa spoza zakresu 2 - 16.\n");
}

void check_input_number(int decimal)
{
	if(abs(decimal) > 1000000000)
		throw runtime_error("Liczba poza przewidywanym zakresem wejścia.\n");
}

void check_digits(string &number, int base, bool has_sign)
{
	int digits_begin = has_sign ? 1 : 0;
	char max_dec = (char)min(57, base+47);
	char max_big_hex = (char)max(64, base+54);
	char max_small_hex = (char)max(96, base+86);
	
	for(int i = digits_begin; i < number.size(); i++)
	{
		char digit = number[i];
		
		if(digit < '0' || (digit > max_dec && digit < 'A') || (digit > max_big_hex && digit < 'a') || digit > max_small_hex)
			throw runtime_error("Znaki niewłaściwe dla podanego systemu liczbowego.\n");
	}
}

int convert_to_decimal(string &number, int base, bool has_sign)
{
	int digits_begin = has_sign ? 1 : 0, decimal = 0;

	for(int i = digits_begin; i < number.size(); i++)
	{
		int actual_digit;
		
		if( number[i] >= '0' && number[i] <= '9' )
			actual_digit = ( (int)number[i]-'0' );
		else if( number[i] >= 'A' && number[i] <= 'F' )
			actual_digit = ( (int)number[i]-'A'+10 );
		else if( number[i] >= 'a' && number[i] <= 'f' )
			actual_digit = ( (int)number[i]-'a'+10 );
		
		decimal = decimal*base+actual_digit;
	}
	
	return decimal;
}

vector <int> convert_to_output(int decimal, int base)
{
	vector <int> output;
	
	do
	{
		output.push_back(decimal%base);
		decimal = decimal/base;
	}
	while(decimal != 0);
	
	return output;
}

int main()
{
	int base_in;
	string number_in;
	
	cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n\n";
	cout << "\t\tCONVERTER SYSTEMÓW LICZBOWYCH\n\n";
	
	cout << "Podaj podstawę systemu liczby\n";
	cin >> base_in;
	cout << "\n";
	check_base(base_in);
	cout << "Podaj liczbę do zamiany\n";
	cin >> number_in;
	
	bool has_sign = number_in[0] == '-' || number_in[0] == '+';
	
	check_digits(number_in, base_in, has_sign);
	
	int base_out, decimal = convert_to_decimal(number_in, base_in, has_sign);
	
	check_input_number(decimal);
	cout << "\n" << "Podaj podstawę systemu, na który chcesz zamienić tę liczbę\n";
	cin >> base_out;
	cout << "\n\n";
	check_base(base_out);
	
	vector <int> number_out = convert_to_output(decimal, base_out);

	cout << "\tTwoja liczba w systemie o podstawie " << base_out << " wynosi:\n\n" << "\t\t";
	
	if(has_sign && number_in[0] == '-')
		cout << "-";
	
	for(int i = number_out.size()-1; i >= 0; i--)
	{
		int shift = number_out[i] < 10 ? '0' : 'A';
		char out_code = number_out[i]%10+shift;
		
		cout << (char)out_code;
	}
	
	cout << "\n\n";
	
	return 0;
}

