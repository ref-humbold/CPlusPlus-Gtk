#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

void next_wyg(std::vector<long long int> & wyg, bool reset)
{
    if(reset)
    {
        wyg[0] = 0LL;
        wyg[1] = 1LL;
        wyg[2] = 1LL;
    }
    else if(wyg[2] != wyg[0] + wyg[1] || wyg[1] < 10)
        wyg[2] = wyg[0] + wyg[1];
    else
    {
        wyg[0] = wyg[1];
        wyg[1] = wyg[2];
        wyg[2] = (wyg[0] + wyg[1] + wyg[1]) / 2;
    }
}

void print_numbs(long long int mask)
{
    for(long long int i = 1; i <= 49; ++i)
        if(((1LL << i) & mask) != 0)
            std::cout << i << "\t";
}

int main()
{
    long long int gra;
    std::vector<long long int> wyg;

    std::cout << "\t\tDUŻY LOTEK\n"
              << "\tPODAJ LICZBĘ GIER\n";

    std::cin >> gra;
    wyg.push_back(0LL);
    wyg.push_back(1LL);
    wyg.push_back(1LL);

    for(long long int e = 0; e < gra; ++e)
    {
        long long int x, gl = 0LL, kl = 0LL, lt = 0LL;

        std::cout << "\n"
                  << "\tKUMULACJA " << 1000000 * wyg[2] << " zł\n"
                  << "\tPodaj 6 roznych liczb od 1 do 49\n";

        for(long long int i = 0; i < 6; ++i)
        {
            std::cin >> x;

            if(x < 1 || x > 49)
                throw std::runtime_error("Liczba spoza zakresu 1 - 49\n");

            if(((1LL << x) & gl) != 0)
                throw std::runtime_error("Liczby powtarzają się\n");

            gl |= 1LL << x;
        }

        srand(time(NULL));

        std::cout << "\nTwoje liczby to:\n";
        print_numbs(gl);

        for(long long int i = 0; i < 6; ++i)
        {
            do
                x = rand() % 49 + 1;
            while(((1LL << x) & kl) != 0);

            kl |= 1LL << x;
        }

        std::cout << "\n\n"
                  << "Losowanie numer" << gra << "\tKumulacja " << 1000000 * wyg[2] << " zł\n\n"
                  << "Wylosowane liczby to:\n";
        print_numbs(kl);
        std::cout << "\n\n";

        for(long long int i = gl & kl; i > 0; i >>= 1)
            if((i & 1) == 1)
                ++lt;

        switch(lt)
        {
            case 6:
                std::cout << "\t TRAFILES 6 LICZB!!!\n"
                          << "Wygrana to " << 1000000 * wyg[2] << " zł\n";
                break;

            case 5:
                std::cout << "\t TRAFILES 5 LICZB!!!\n"
                          << "Wygrana to " << 5000 * wyg[2] << " zł\n";
                break;

            case 4:
                std::cout << "\t TRAFILES 4 LICZBY!!!\n"
                          << "Wygrana to " << 1500 * wyg[2] << " zł\n";
                break;

            case 3:
                std::cout << "\tTRAFILES 3 LICZBY!!!\n"
                          << "Wygrana to 20 zł\n";
                break;

            case 2:
                std::cout << "\tTRAFILES 2 LICZBY\n"
                          << "Przegrana\n";
                break;

            case 1:
                std::cout << "\tTRAFILES 1 LICZBE\n"
                          << "Przegrana\n";
                break;

            case 0:
                std::cout << "\tNIC NIE TRAFIONO\n"
                          << "Przegrana\n";
                break;
        }

        next_wyg(wyg, lt == 6);
        std::cout << "\n\n"
                  << "Najblizsza kumulacja wynosi " << 1000000 * wyg[2] << " zł\n";
    }

    return 0;
}
