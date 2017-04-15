# -*- coding: utf-8 -*-
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from decimal import Decimal
from extra import Extra

class Magazynier:
    """Klasa odpowiadająca za działanie okna interakcji magazyniera z bazą danych."""
    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        MagBuilder = Gtk.Builder()
        MagBuilder.add_from_file("magazynier.glade")

        self.MagWindow = MagBuilder.get_object("MagWindow")

        self.MagEntry11b = MagBuilder.get_object("MagEntry11b")
        self.MagEntry12b = MagBuilder.get_object("MagEntry12b")
        self.MagEntry13b = MagBuilder.get_object("MagEntry13b")
        self.MagComboboxtext14b = MagBuilder.get_object("MagComboboxtext14b")
        self.MagButton15b = MagBuilder.get_object("MagButton15b")

        self.MagComboboxtext21b = MagBuilder.get_object("MagComboboxtext21b")
        self.MagEntry22b = MagBuilder.get_object("MagEntry22b")
        self.MagEntry23b = MagBuilder.get_object("MagEntry23b")
        self.MagEntry24b = MagBuilder.get_object("MagEntry24b")
        self.MagButton25b = MagBuilder.get_object("MagButton25b")

        self.MagComboboxtext31b = MagBuilder.get_object("MagComboboxtext31b")
        self.MagButton31c = MagBuilder.get_object("MagButton31c")

        self.__load_ids(self.MagComboboxtext14b, "czesci")
        self.__load_ids(self.MagComboboxtext21b, "zamowienia")
        self.__load_ids(self.MagComboboxtext31b, "zamowienia_unreal")

        MagBuilder.connect_signals(self)

        self.MagWindow.show()

    def __load_ids(self, comboboxtext, tablename):
        """Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru."""
        cur = self.conn.cursor()

        if tablename == "czesci":
            cur.execute("SELECT id FROM czesci;")
        elif tablename == "zamowienia":
            cur.execute("SELECT id FROM zamowienia;")
        elif tablename == "zamowienia_unreal":
            cur.execute("SELECT id FROM zamowienia WHERE data_real IS NULL;")

        idents = cur.fetchall()
        self.conn.commit()
        cur.close()

        for s in [str(i[0]) for i in idents]:
            comboboxtext.append_text(s)

        comboboxtext.set_active(0)

    def __modify(self, cur, fieldname, args, convtype):
        """Dokonuje modyfikacji wybranej kolumny tabeli zamówień."""
        if args[0] != "":
            getcontext().prec = 2
            args[0] = convtype(args[0])

            try:
                if fieldname == "firma":
                    cur.execute("UPDATE zamowienia SET firma = %s WHERE id = %s;", args)
                elif fieldname == "ilosc":
                    cur.execute("UPDATE zamowienia SET ilosc = %s WHERE id = %s;", args)
                elif fieldname == "cena":
                    cur.execute("UPDATE zamowienia SET cena = %s WHERE id = %s;", args)
            except:
                self.conn.rollback()
                cur.close()
                ExtraWindow = Extra()
                ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                return False

        return True

    def MagWindow_destroy_cb(self, window):
        """Zamyka okno magazyniera."""
        self.conn.close()
        Gtk.main_quit()

    def MagButton15b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wysłania nowego zamówienia."""
        firma = self.MagEntry11b.get_text() # SQL text
        ilosc = self.MagEntry12b.get_text() # SQL integer
        cena = self.MagEntry13b.get_text() # SQL numeric
        cze_id = self.MagComboboxtext14b.get_active_text() # SQL integer

        getcontext().prec = 2
        args = [firma, int(ilosc), Decimal(cena), int(cze_id)]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO zamowienia(data_zamow, firma, ilosc, cena, cze_id) VALUES(now(), %s, %s, %s, %s);", args)
            cur.execute("SELECT max(id) FROM zamowienia;")
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            self.MagComboboxtext21b.append_text(str(wyn))
            self.MagComboboxtext31b.append_text(str(wyn))
            ExtraWindow = Extra()
            ExtraWindow.show_label("ZAMÓWIENIE ZOSTAŁO POMYŚLNIE WYSŁANE.\nID = "+str(wyn))
        finally:
            cur.close()

    def MagButton25b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku modyfikacji zamówienia."""
        ident = self.MagComboboxtext21b.get_active_text() # SQL integer
        firma = self.MagEntry22b.get_text() # SQL text
        ilosc = self.MagEntry23b.get_text() # SQL integer
        cena = self.MagEntry24b.get_text() # SQL numeric

        cur = self.conn.cursor()

        if not self.__modify(cur, "firma", [firma, int(ident)], str):
            return

        if not self.__modify(cur, "ilosc", [ilosc, int(ident)], int):
            return

        if not self.__modify(cur, "cena", [cena, int(ident)], Decimal):
            return

        self.conn.commit()
        cur.close()
        ExtraWindow = Extra()
        ExtraWindow.show_label("ZAMÓWIENIE NUMER "+str(ident)+" ZOSTAŁO POMYŚLNIE ZMIENIONE.")

    def MagButton31c_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku odbioru zamówienia."""
        ident = self.MagComboboxtext31b.get_active_text() # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE zamowienia SET data_real = now() WHERE id = %s", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("POMYŚLNIE ODEBRANO ZAMÓWIENIE NUMER "+str(ident)+".")
        finally:
            cur.close()

