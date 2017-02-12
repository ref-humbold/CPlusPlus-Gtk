#include <cstdlib>
#include <iostream>
#include <exception>
#include <algorithm>
#include <vector>
#include <ctime>

void next_wyg(std::vector<long long int> > & wyg, bool reset)
{
    if(reset)
    {
        wyg[0] = 0LL;
        wyg[1] = 1LL;
        wyg[2] = 1LL;
    }
    else if(wyg[2] != wyg[0]+wyg[1] || wyg[1] < 10)
        wyg[2] = wyg[0]+wyg[1];
    else
    {
        wyg[0] = wyg[1];
        wyg[1] = wyg[2];
        wyg[2] = (wyg[0]+wyg[1]+wyg[1])/2;
    }
}

void print_numbs(long long int mask)
{
    for(long long int i = 1; i <= 49; ++i)
        if( ( (1LL<<i)&mask ) != 0 )
            cout << i << "\t";
}

int main()
{
    long long int gra, lt;
    std::vector<long long int> wyg;

    cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n";
    cout << "\t\tDUŻY LOTEK\n" << "\tPODAJ LICZBĘ GIER\n";

    cin >> gra;
    wyg.push_back(0LL);
    wyg.push_back(1LL);
    wyg.push_back(1LL);

    for(long long int e = 0; e < gra; ++e)
    {
        long long int x, gl = 0LL, kl = 0LL, lt = 0LL;

        cout << "\n" << "\tKUMULACJA " << 1000000*wyg[2] << " zł\n" << "\tPodaj 6 roznych liczb od 1 do 49\n";

        for(long long int i = 0; i < 6; ++i)
        {
            cin >> x;

            if(x < 1 || x > 49)
                throw runtime_error("Liczba spoza zakresu 1 - 49\n");

            if( ( (1LL<<x)&gl ) != 0 )
                throw runtime_error("Liczby powtarzają się\n");

            gl |= 1LL<<x;
        }

        srand( time(0) );

        cout << "\nTwoje liczby to:\n";
        print_numbs(gl);

        for(long long int i = 0; i < 6; ++i)
        {
            do
                x = rand()%49+1;
            while( (1LL<<x)&kl != 0 );

            kl |= 1LL<<x;
        }

        cout << "\n\n" << "Losowanie numer" << gra << "\tKumulacja " << 1000000*wyg[2] << " zł\n\n" << "Wylosowane liczby to:\n";
        print_numbs(kl);
        cout << "\n\n";

        for(long long int i = gl&kl; i > 0; i >>= 1)
            if( (i&1) == 1 )
                ++lt;

        switch(lt)
        {
            case 6:
                cout << "\t TRAFILES 6 LICZB!!!\n" << "Wygrana to " << 1000000*wyg[2] << " zł\n";
                next_wyg(wyg, true);
            break;

            case 5:
                cout << "\t TRAFILES 5 LICZB!!!\n" << "Wygrana to " << 5000*wyg[2] << " zł\n";
                next_wyg(wyg, false);
            break;

            case 4:
                cout << "\t TRAFILES 4 LICZBY!!!\n" << "Wygrana to " << 1500*wyg[2] << " zł\n";
                next_wyg(wyg, false);
            break;

            case 3:
                cout << "\tTRAFILES 3 LICZBY!!!\n" << "Wygrana to 20 zł\n";
                next_wyg(wyg, false);
            break;

            case 2:
                cout << "\tTRAFILES 2 LICZBY\n" << "Przegrana\n";
                next_wyg(wyg, false);
            break;

            case 1:
                cout << "\tTRAFILES 1 LICZBE\n" << "Przegrana\n";
                next_wyg(wyg, false);
            break;

            case 0:
                cout << "\tNIC NIE TRAFIONO\n" << "Przegrana\n";
                next_wyg(wyg, false);
            break;
        }

        cout << "\n\n" << "Najblizsza kumulacja wynosi " << 1000000*wyg[2] << " zł\n";
    }

    return 0;
}

