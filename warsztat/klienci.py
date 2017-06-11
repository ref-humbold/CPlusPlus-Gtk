# -*- coding: utf-8 -*-
from gi import require_version

require_version('Gtk', '3.0')

from gi.repository import Gtk
from psycopg2.extensions import AsIs
from extra import Extra


class Klienci:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą klientów."""

    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        klienci_builder = Gtk.Builder()
        klienci_builder.add_from_file("klienci.glade")

        self.klienci_window = klienci_builder.get_object("klienci_window")

        self.klienci_entry1_1b = klienci_builder.get_object("klienci_entry1_1b")
        self.klienci_entry1_2b = klienci_builder.get_object("klienci_entry1_2b")
        self.klienci_entry1_3b = klienci_builder.get_object("klienci_entry1_3b")
        self.klienci_entry1_4b = klienci_builder.get_object("klienci_entry1_4b")
        self.klienci_comboboxtext1_5b = klienci_builder.get_object("klienci_comboboxtext1_5b")
        self.klienci_button1_6b = klienci_builder.get_object("klienci_button1_6b")

        self.klienci_comboboxtext2_1b = klienci_builder.get_object("klienci_comboboxtext2_1b")
        self.klienci_entry2_2b = klienci_builder.get_object("klienci_entry2_2b")
        self.klienci_entry2_3b = klienci_builder.get_object("klienci_entry2_3b")
        self.klienci_entry2_4b = klienci_builder.get_object("klienci_entry2_4b")
        self.klienci_entry2_5b = klienci_builder.get_object("klienci_entry2_5b")
        self.klienci_comboboxtext2_6b = klienci_builder.get_object("klienci_comboboxtext2_6b")
        self.klienci_button2_7b = klienci_builder.get_object("klienci_button2_7b")

        self.klienci_comboboxtext3_1b = klienci_builder.get_object("klienci_comboboxtext3_1b")
        self.klienci_entry3_2b = klienci_builder.get_object("klienci_entry3_2b")
        self.klienci_entry3_3b = klienci_builder.get_object("klienci_entry3_3b")
        self.klienci_entry3_4b = klienci_builder.get_object("klienci_entry3_4b")
        self.klienci_button3_5b = klienci_builder.get_object("klienci_button3_5b")

        self.klienci_comboboxtext3_1b.append_text("-")
        self.__load_ids(self.klienci_comboboxtext2_1b)
        self.__load_ids(self.klienci_comboboxtext3_1b)

        klienci_builder.connect_signals(self)

        self.klienci_window.show()

    def __load_ids(self, comboboxtext):
        """Ładuje identyfikatory (klucze główne) z tabeli klientów do zadanego pola wyboru."""
        cur = self.conn.cursor()
        cur.execute("SELECT id FROM klienci;")
        idents = cur.fetchall()
        self.conn.commit()
        cur.close()

        for s in [str(i[0]) for i in idents]:
            comboboxtext.append_text(s)

        comboboxtext.set_active(0)

    def __modify(self, cur, nonstr, fieldname, args, convtype):
        """Dokonuje modyfikacji wybranej kolumny tabeli klientów."""
        if args[0] != nonstr:
            args[0] = convtype(args[0])

            try:
                if fieldname == "imie":
                    cur.execute("UPDATE klienci SET imie = %s WHERE id = %s;", args)
                elif fieldname == "nazwisko":
                    cur.execute("UPDATE klienci SET nazwisko = %s WHERE id = %s;", args)
                elif fieldname == "telefon":
                    cur.execute("UPDATE klienci SET telefon = %s WHERE id = %s;", args)
                elif fieldname == "firma":
                    cur.execute("UPDATE klienci SET firma = %s WHERE id = %s;", args)
                elif fieldname == "rabat":
                    cur.execute("UPDATE klienci SET rabat = %s WHERE id = %s;", args)
            except:
                self.conn.rollback()
                cur.close()
                ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                ExtraWindow.show()
                return False

        return True

    def klienci_button1_6b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku dodania nowego klienta."""
        imie = self.klienci_entry1_1b.get_text()  # SQL text
        nazwisko = self.klienci_entry1_2b.get_text()  # SQL text
        telefon = self.klienci_entry1_3b.get_text()  # SQL integer
        firma = self.klienci_entry1_4b.get_text()  # SQL text
        rabat = self.klienci_comboboxtext1_5b.get_active_text()  # SQL integer

        args = [None if i == "" else i for i in [imie, nazwisko, telefon, firma]] + [int(rabat)]
        args[2] = None if args[2] == None else int(args[2])

        try:
            cur = self.conn.cursor()
            cur.execute(
                "INSERT INTO klienci(imie, nazwisko, telefon, firma, rabat) VALUES (%s, %s, %s, %s, %s);", args)
            cur.execute("SELECT max(id) FROM klienci;")
            wynid = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            ExtraWindow.show()
        else:
            self.conn.commit()
            self.klienci_comboboxtext2_1b.append_text(str(wynid))
            self.klienci_comboboxtext3_1b.append_text(str(wynid))
            ExtraWindow = Extra("NOWY KLIENT ZOSTAŁ POMYŚLNIE DODANY.\nID = " + str(wynid))
            ExtraWindow.show()
        finally:
            cur.close()

    def klienci_button2_7b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku modyfikacji danych klienta."""
        ident = self.klienci_comboboxtext2_1b.get_active_text()  # SQL integer
        imie = self.klienci_entry2_2b.get_text()  # SQL text
        nazwisko = self.klienci_entry2_3b.get_text()  # SQL text
        telefon = self.klienci_entry2_4b.get_text()  # SQL integer
        firma = self.klienci_entry2_5b.get_text()  # SQL text
        rabat = self.klienci_comboboxtext2_6b.get_active_text()  # SQL integer

        cur = self.conn.cursor()

        if not self.__modify(cur, "", "imie", [imie, int(ident)], str):
            return

        if not self.__modify(cur, "", "nazwisko", [nazwisko, int(ident)], str):
            return

        if not self.__modify(cur, "", "telefon", [telefon, int(ident)], int):
            return

        if not self.__modify(cur, "", "firma", [firma, int(ident)], str):
            return

        if not self.__modify(cur, "-", "rabat", [rabat, int(ident)], int):
            return

        self.conn.commit()
        cur.close()
        ExtraWindow = Extra("DANE KLIENTA NUMER " + str(ident) + " ZOSTAŁY POMYŚLNIE ZMIENIONE.")
        ExtraWindow.show()

    def klienci_button3_5b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyszukania klienta."""
        ident = self.klienci_comboboxtext3_1b.get_active_text()  # SQL integer
        imie = self.klienci_entry3_2b.get_text()  # SQL text
        nazwisko = self.klienci_entry3_3b.get_text()  # SQL text
        telefon = self.klienci_entry3_4b.get_text()  # SQL integer

        cur = self.conn.cursor()

        if ident != "-":
            args = [int(ident)]

            try:
                cur.execute(
                    "SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE id = %s;", args)
                wyn = cur.fetchone()[:]
            except:
                self.conn.rollback()
                ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                ExtraWindow.show()
                return
            else:
                self.conn.commit()
                ExtraWindow = Extra(", ".join(map(str, wyn)))
                ExtraWindow.show()
            finally:
                cur.close()
        else:
            args = ["%" + str(i) + "%" for i in [imie, nazwisko, telefon]]

            try:
                cur.execute(
                    "SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE imie LIKE %s AND nazwisko LIKE %s AND CAST(telefon AS text) LIKE %s;", args)
                wyn = cur.fetchall()[:]
            except:
                self.conn.rollback()
                ExtraWindow = Extra("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                ExtraWindow.show()
                return
            else:
                self.conn.commit()
                res = map(lambda x: ", ".join(map(str, x)), wyn)
                out_str = "BRAK WYNIKÓW!" if wyn == [] else "\n".join(res)
                ExtraWindow = Extra(out_str)
                ExtraWindow.show()
            finally:
                cur.close()
