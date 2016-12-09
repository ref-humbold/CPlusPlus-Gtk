#include <cstdlib>
#include <iostream>
#include <exception>
#include <ctime>
#include <vector>

using namespace std;

bool cannot_place(vector < vector <char> > > & vf, int n, int x, int y, bool p)
{
    if( (p&1) == 0 )
    {
        for(int i = -1; i <= 1; ++i)
            for(int j = -1; j <= n; ++j)
                if(x+i >= 0 && x+i < vf.size() && y+j >= 0 && y+j < vf.size())
                    if(vf[x+i][y+j] == '#')
                        return true;
    }
    else
    {
        for(int i = -1;i <= n; ++i)
            for(int j = -1;j <= 1; ++j)
                if(x+i >= 0 && x+i <vf.size() && y+j >= 0 && y+j < vf.size())
                    if(vf[x+i][y+j] == '#')
                        return true;
    }
    
    return false;
}

void gen_statek(vector < vector <char> > > & vf, int n)
{    
    int x, y, p = rand()%10;
    
    do
    {
        x = rand()%10;
        y = rand()%(10-n+1);
    }
    while( cannot_place(vf, n, x, y, p) );
    
    for(int i = 0; i < n; ++i)
    {
        if( (p&1) == 0 )
            vf[x][y] = '#';
        else
            vf[y][x] = '#';
        
        ++y;
    }
}

void print_leg(bool ended)
{
    cout << "\n\n\tLEGENDA PLANSZY\n" << "= - puste miejsce\n";
    
    if(ended)
        cout << "# - nietrafiony statek \n";
    
    cout << "~ - Twoje pudlo\n" << "X - trafiony statek\n\n";
}

int main()
{
    int x, y, wyg, str, strs;
    vector <string> v;

    cout << "\t(C) by Rafał Kaleta, Wrocław, Poland\n" << "\t\tAll rights reserved\n\n\n";
    cout << "\t\tGRA W STATKI\n\n";
    
    srand( time(0) );
    v.resize(10);
    
    for(int i = 0; i < v.size(); ++i)
        for(int j = 0;j < 10; ++j)
            v[i].push_back('=');
    
    for(int i = 4; i >= 1; --i)
        for(int j = 0; j <= 4-i; ++j)
            gen_statek(v, i);

    cout << "Komputer wylosował statki.\n" << "\t\tZATOP JE WSZYSTKIE!!!!!!\n\n\n";
    cout << "Określ swój limit strzałów (zakres 20 - 200)\n";
    cin >> str;

    if(str > 200 || str < 20)
        throw runtime_error("Zła liczba strzałów\n");

    print_leg(false);
    wyg = 0;
    strs = str;

    do
    {
        cout << "\t\tZostało Ci: " << str << " strzalow \n" << "\t\t\tTrafiono: " << wyg << " razy\n\n" << "Podaj współrzędne punktu strzału (od 0 do 9)\n";
        cout << "x = ";
        cin >> x;
        cout << "y = ";
        cin >> y;

        if(x < 0 || x > 9 || y < 1 || y > 9)
        {
            cout << "\tJesteś poza planszą!! \n \n";
            break;
        }
        
        x = 9-x;

        if(v[x][y] == '#')
        {
            cout << "\tTRAFIONY!!!! \n \n";
            v[x][y] = 'X';
            ++wyg;
        }
        else if(v[x][y] == '=')
        {
            cout << "\tPUDŁO\n\n";
            v[x][y] = '~';
        }
        else if(v[x][y] == '~' || v[x][y] == 'X')
                cout << "\tTu oddano już strzał!!!\n\n";

        --str;
        cout << "\tPLANSZA:\n";

        for(int i = 0; i < v.size(); ++i)
        {
            for(int j = 0; j < v[i].size(); ++j)
                if(v[i][j] ==  '#')
                    cout << "= ";
                else
                    cout << v[i][j] << " ";

            cout << "\n";
        }

        cout << "\n";
    }
    while(wyg < 20 && str > 0);

    cout << "\t\tKONIEC\n\n" << "\tStrzelono " << strs-str << " razy\n\n";
    print_leg(true);
    cout << "\tTwoje próby to:\n\n";

    for(int i = 0; i < v.size(); ++i)
    {
        for(int j = 0; j < v[i].size(); ++j)
            cout << v[i][j] << " ";

        cout << "\n";
    }

    return 0;
}

