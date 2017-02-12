#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <ctime>
#include <vector>
#include <string>

bool collide(const std::vector<std::string> & vf, int n, int row, int col)
{
    for(int dr = -1; dr <= 1; ++dr)
        for(int dc = -1; dc <= n; ++dc)
            if(row+dr >= 0 && row+dr < vf.size() && col+dc >= 0 && col+dc < vf.size())
                if(vf[row+dr][col+dc] == '#')
                    return true;

    return false;
}

void add_ship(std::vector<std::string> & vf, int n)
{
    int row, col;
    bool cld, vert = rand()%2 == 0;

    do
    {
        row = rand()%10;
        col = rand()%(10-n+1);
        cld = vert ? collide(vf, n, row, col) : collide(vf, n, col, row);
    }
    while(cld);

    for(int dc = 0; dc < n; ++dc)
    {
        if(vert)
            vf[row][col+dc] = '#';
        else
            vf[col+dc][row] = '#';
    }
}

std::pair<int, int> shoot()
{
    std::pair<int, int> coef;

    std::cout << "Podaj współrzędne punktu strzału (od 0 do 9)\n";
    std::cout << "Wiersz: ";
    std::cin >> coef.first;
    std::cout << "Kolumna: ";
    std::cin >> coef.second;

    return coef;
}

bool check_shot(std::vector<std::string> & v, const std::pair<int, int> & coef)
{
    bool hit = false;

    switch( v[coef.first][coef.second] )
    {
        case '#':
            std::cout << "\tTRAFIONY!!!! \n \n";
            v[coef.first][coef.second] = 'X';
            hit = true;
            break;

        case '=':
            std::cout << "\tPUDŁO\n\n";
            v[coef.first][coef.second] = '~';
            break;

        case '~':
        case 'X':
            std::cout << "\tTu oddano już strzał!!!\n\n";
            break;
    }

    return hit;
}

void legend(bool is_game)
{
    std::cout << "\n\n\tLEGENDA PLANSZY\n" << "= - puste miejsce\n";

    if(!is_game)
        std::cout << "# - nietrafiony statek \n";

    std::cout << "~ - Twoje pudlo\n" << "X - trafiony statek\n\n";
}

void board(const std::vector<std::string> & v, bool is_game)
{
    std::cout << "  ";

    for(int i = 0; i < v.size(); ++i)
        std::cout << i << " ";

    std::cout << "\n";

    for(int i = 0; i < v.size(); ++i)
    {
        std::cout << i << " ";

        for( char c : v[i] )
            if(is_game && c == '#')
                std::cout << "= ";
            else
                std::cout << c << " ";

        std::cout << "\n";
    }

    std::cout << "\n";
}

int main()
{
    int limit;
    std::vector<std::string> v(10, "==========");

    std::cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n\n";
    std::cout << "\t\tGRA W STATKI\n\n";

    srand( time(0) );

    for(int i = 4; i >= 1; --i)
        for(int j = 0; j <= 4-i; ++j)
            add_ship(v, i);

    std::cout << "Komputer wylosował statki.\n" << "\t\tZATOP JE WSZYSTKIE!!!!!!\n\n\n";
    std::cout << "Określ swój limit strzałów (zakres 20 - 200)\n";
    std::cin >> limit;

    if(limit < 20 || limit > 200)
        throw std::runtime_error("Zła liczba strzałów\n");

    int shots = 0, hits = 0;

    legend(true);

    do
    {
        std::cout << "\t\tZostało Ci: " << limit-shots << " strzalow \n" << "\t\t\tTrafiono: " << hits << " razy\n\n";

        std::pair<int, int> coef = shoot();

        if(coef.first < 0 || coef.first > 9 || coef.second < 0 || coef.second > 9)
        {
            std::cout << "\tJesteś poza planszą!! \n \n";
            break;
        }

        check_shot(v, coef);
        ++shots;
        std::cout << "\tPLANSZA:\n";
        board(v, true);
    }
    while(hits < 20 && shots < limit);

    std::cout << "\t\tKONIEC\n\n" << "\tStrzelono " << shots << " razy\n\n";
    legend(false);
    std::cout << "\tTwoje próby to:\n\n";
    board(v, false);

    return 0;
}
