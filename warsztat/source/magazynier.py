# -*- coding: utf-8 -*-
from gi import require_version

require_version('Gtk', '3.0')

from gi.repository import Gtk
from decimal import Decimal
from .extra import Extra


class Magazynier:
    """Klasa odpowiadająca za działanie okna interakcji magazyniera z bazą danych."""

    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        magazynier_builder = Gtk.Builder()
        magazynier_builder.add_from_file("glade/magazynier.glade")

        self.magazynier_window = magazynier_builder.get_object("magazynier_window")

        self.magazynier_entry1_1b = magazynier_builder.get_object("magazynier_entry1_1b")
        self.magazynier_entry1_2b = magazynier_builder.get_object("magazynier_entry1_2b")
        self.magazynier_entry1_3b = magazynier_builder.get_object("magazynier_entry1_3b")
        self.magazynier_comboboxtext1_4b = magazynier_builder.get_object("magazynier_comboboxtext1_4b")
        self.magazynier_button1_5b = magazynier_builder.get_object("magazynier_button1_5b")

        self.magazynier_comboboxtext2_1b = magazynier_builder.get_object("magazynier_comboboxtext2_1b")
        self.magazynier_entry2_2b = magazynier_builder.get_object("magazynier_entry2_2b")
        self.magazynier_entry2_3b = magazynier_builder.get_object("magazynier_entry2_3b")
        self.magazynier_entry2_4b = magazynier_builder.get_object("magazynier_entry2_4b")
        self.magazynier_button2_5b = magazynier_builder.get_object("magazynier_button2_5b")

        self.magazynier_comboboxtext3_1b = magazynier_builder.get_object("magazynier_comboboxtext3_1b")
        self.magazynier_button3_1c = magazynier_builder.get_object("magazynier_button3_1c")

        self.__load_ids(self.magazynier_comboboxtext1_4b, "czesci")
        self.__load_ids(self.magazynier_comboboxtext2_1b, "zamowienia")
        self.__load_ids(self.magazynier_comboboxtext3_1b, "zamowienia_unreal")

        magazynier_builder.connect_signals(self)

        self.magazynier_window.show()

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
                ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                ExtraWindow.show()
                return False

        return True

    def magazynier_window_destroy_cb(self, window):
        """Zamyka okno magazyniera."""
        self.conn.close()
        Gtk.main_quit()

    def magazynier_button1_5b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wysłania nowego zamówienia."""
        firma = self.magazynier_entry1_1b.get_text()  # SQL text
        ilosc = self.magazynier_entry1_2b.get_text()  # SQL integer
        cena = self.magazynier_entry1_3b.get_text()  # SQL numeric
        cze_id = self.magazynier_comboboxtext1_4b.get_active_text()  # SQL integer

        getcontext().prec = 2
        args = [firma, int(ilosc), Decimal(cena), int(cze_id)]

        try:
            cur = self.conn.cursor()
            cur.execute(
                "INSERT INTO zamowienia(data_zamow, firma, ilosc, cena, cze_id) VALUES(now(), %s, %s, %s, %s);", args)
            cur.execute("SELECT max(id) FROM zamowienia;")
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            ExtraWindow.show()
        else:
            self.conn.commit()
            self.magazynier_comboboxtext2_1b.append_text(str(wyn))
            self.magazynier_comboboxtext3_1b.append_text(str(wyn))
            ExtraWindow = Extra("ZAMÓWIENIE ZOSTAŁO POMYŚLNIE WYSŁANE.\nID = " + str(wyn))
            ExtraWindow.show()
        finally:
            cur.close()

    def magazynier_button2_5b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku modyfikacji zamówienia."""
        ident = self.magazynier_comboboxtext2_1b.get_active_text()  # SQL integer
        firma = self.magazynier_entry2_2b.get_text()  # SQL text
        ilosc = self.magazynier_entry2_3b.get_text()  # SQL integer
        cena = self.magazynier_entry2_4b.get_text()  # SQL numeric

        cur = self.conn.cursor()

        if not self.__modify(cur, "firma", [firma, int(ident)], str):
            return

        if not self.__modify(cur, "ilosc", [ilosc, int(ident)], int):
            return

        if not self.__modify(cur, "cena", [cena, int(ident)], Decimal):
            return

        self.conn.commit()
        cur.close()
        ExtraWindow = Extra("ZAMÓWIENIE NUMER " + str(ident) + " ZOSTAŁO POMYŚLNIE ZMIENIONE.")
        ExtraWindow.show()

    def magazynier_button3_1c_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku odbioru zamówienia."""
        ident = self.magazynier_comboboxtext3_1b.get_active_text()  # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE zamowienia SET data_real = now() WHERE id = %s", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            ExtraWindow.show()
        else:
            self.conn.commit()
            ExtraWindow = Extra("POMYŚLNIE ODEBRANO ZAMÓWIENIE NUMER " + str(ident) + ".")
            ExtraWindow.show()
        finally:
            cur.close()
