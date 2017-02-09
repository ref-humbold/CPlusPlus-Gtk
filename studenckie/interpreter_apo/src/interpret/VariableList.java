package interpret;

import java.util.*;

/** Klasa przechowujaca liste zmiennych wraz z ich wartosciami. */
class VariableList
{
    private ArrayList<Integer> varTab;

    /** Tworzy nowa pusta liste zmiennych. */
    public VariableList()
    {
        varTab = new ArrayList<Integer>();
    }

    /** Dodaje nowa zmienna do listy i zapisuje jej domyslna wartość 0. */
    void addVar()
    {
        varTab.add(0);
    }

    /**
    Pobiera wartosc okreslonej zmiennej.
    @param indx indeks zmiennej w liscie
    @return wartosc zmiennej
    */
    int getValue(int indx)
    {
        return varTab.get(indx);
    }

    /**
    Przypisuje nowa wartosc do okreslonej zmiennej w liscie.
    @param indx indeks zmiennej w liscie
    @param val wartosc do zapisu
    */
    void setValue(int indx, int val)
    {
        varTab.set(indx, val);
    }
}
