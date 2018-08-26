# -*- coding: utf-8 -*-
from gi import require_version

require_version('Gtk', '3.0')

from gi.repository import Gtk
from psycopg2.extensions import AsIs
from .popup import PopUp


class Clients:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą klientów."""

    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        clients_builder = Gtk.Builder()
        clients_builder.add_from_file("glade/clients.glade")

        self.clients_window = clients_builder.get_object("clients_window")

        self.clients_entry1_1b = clients_builder.get_object("clients_entry1_1b")
        self.clients_entry1_2b = clients_builder.get_object("clients_entry1_2b")
        self.clients_entry1_3b = clients_builder.get_object("clients_entry1_3b")
        self.clients_entry1_4b = clients_builder.get_object("clients_entry1_4b")
        self.clients_comboboxtext1_5b = clients_builder.get_object("clients_comboboxtext1_5b")
        self.clients_button1_6b = clients_builder.get_object("clients_button1_6b")

        self.clients_comboboxtext2_1b = clients_builder.get_object("clients_comboboxtext2_1b")
        self.clients_entry2_2b = clients_builder.get_object("clients_entry2_2b")
        self.clients_entry2_3b = clients_builder.get_object("clients_entry2_3b")
        self.clients_entry2_4b = clients_builder.get_object("clients_entry2_4b")
        self.clients_entry2_5b = clients_builder.get_object("clients_entry2_5b")
        self.clients_comboboxtext2_6b = clients_builder.get_object("clients_comboboxtext2_6b")
        self.clients_button2_7b = clients_builder.get_object("clients_button2_7b")

        self.clients_comboboxtext3_1b = clients_builder.get_object("clients_comboboxtext3_1b")
        self.clients_entry3_2b = clients_builder.get_object("clients_entry3_2b")
        self.clients_entry3_3b = clients_builder.get_object("clients_entry3_3b")
        self.clients_entry3_4b = clients_builder.get_object("clients_entry3_4b")
        self.clients_button3_5b = clients_builder.get_object("clients_button3_5b")

        self.clients_comboboxtext3_1b.append_text("-")
        self.__load_ids(self.clients_comboboxtext2_1b)
        self.__load_ids(self.clients_comboboxtext3_1b)

        clients_builder.connect_signals(self)

        self.clients_window.show()

    def __load_ids(self, comboboxtext):
        """Ładuje identyfikatory (klucze główne) z tabeli klientów do zadanego pola wyboru."""
        cur = self.conn.cursor()
        cur.execute("SELECT id FROM clients;")
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
                    cur.execute("UPDATE clients SET imie = %s WHERE id = %s;", args)
                elif fieldname == "nazwisko":
                    cur.execute("UPDATE clients SET nazwisko = %s WHERE id = %s;", args)
                elif fieldname == "telefon":
                    cur.execute("UPDATE clients SET telefon = %s WHERE id = %s;", args)
                elif fieldname == "firma":
                    cur.execute("UPDATE clients SET firma = %s WHERE id = %s;", args)
                elif fieldname == "rabat":
                    cur.execute("UPDATE clients SET rabat = %s WHERE id = %s;", args)
            except:
                self.conn.rollback()
                cur.close()
                popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                popup_window.show()
                return False

        return True

    def clients_button1_6b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku dodania nowego klienta."""
        imie = self.clients_entry1_1b.get_text()  # SQL text
        nazwisko = self.clients_entry1_2b.get_text()  # SQL text
        telefon = self.clients_entry1_3b.get_text()  # SQL integer
        firma = self.clients_entry1_4b.get_text()  # SQL text
        rabat = self.clients_comboboxtext1_5b.get_active_text()  # SQL integer

        args = [None if i == "" else i for i in [imie, nazwisko, telefon, firma]] + [int(rabat)]
        args[2] = None if args[2] == None else int(args[2])

        try:
            cur = self.conn.cursor()
            cur.execute(
                "INSERT INTO clients(imie, nazwisko, telefon, firma, rabat) VALUES (%s, %s, %s, %s, %s);", args)
            cur.execute("SELECT max(id) FROM clients;")
            wynid = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            self.clients_comboboxtext2_1b.append_text(str(wynid))
            self.clients_comboboxtext3_1b.append_text(str(wynid))
            popup_window = PopUp("NOWY KLIENT ZOSTAŁ POMYŚLNIE DODANY.\nID = " + str(wynid))
            popup_window.show()
        finally:
            cur.close()

    def clients_button2_7b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku modyfikacji danych klienta."""
        ident = self.clients_comboboxtext2_1b.get_active_text()  # SQL integer
        imie = self.clients_entry2_2b.get_text()  # SQL text
        nazwisko = self.clients_entry2_3b.get_text()  # SQL text
        telefon = self.clients_entry2_4b.get_text()  # SQL integer
        firma = self.clients_entry2_5b.get_text()  # SQL text
        rabat = self.clients_comboboxtext2_6b.get_active_text()  # SQL integer

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
        popup_window = PopUp("DANE KLIENTA NUMER " + str(ident) + " ZOSTAŁY POMYŚLNIE ZMIENIONE.")
        popup_window.show()

    def clients_button3_5b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyszukania klienta."""
        ident = self.clients_comboboxtext3_1b.get_active_text()  # SQL integer
        imie = self.clients_entry3_2b.get_text()  # SQL text
        nazwisko = self.clients_entry3_3b.get_text()  # SQL text
        telefon = self.clients_entry3_4b.get_text()  # SQL integer

        cur = self.conn.cursor()

        if ident != "-":
            args = [int(ident)]

            try:
                cur.execute(
                    "SELECT id, imie, nazwisko, telefon, firma, rabat FROM clients WHERE id = %s;", args)
                wyn = cur.fetchone()[:]
            except:
                self.conn.rollback()
                popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                popup_window.show()
                return
            else:
                self.conn.commit()
                popup_window = PopUp(", ".join(map(str, wyn)))
                popup_window.show()
            finally:
                cur.close()
        else:
            args = ["%" + str(i) + "%" for i in [imie, nazwisko, telefon]]

            try:
                cur.execute(
                    "SELECT id, imie, nazwisko, telefon, firma, rabat FROM clients WHERE imie LIKE %s AND nazwisko LIKE %s AND CAST(telefon AS text) LIKE %s;", args)
                wyn = cur.fetchall()[:]
            except:
                self.conn.rollback()
                popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                popup_window.show()
                return
            else:
                self.conn.commit()
                res = map(lambda x: ", ".join(map(str, x)), wyn)
                out_str = "BRAK WYNIKÓW!" if wyn == [] else "\n".join(res)
                popup_window = PopUp(out_str)
                popup_window.show()
            finally:
                cur.close()
