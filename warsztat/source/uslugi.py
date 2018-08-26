# -*- coding: utf-8 -*-
from gi import require_version

require_version("Gtk", "3.0")

from gi.repository import Gtk
from .popup import PopUp


class Uslugi:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą usług."""

    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        uslugi_builder = Gtk.Builder()
        uslugi_builder.add_from_file("glade/uslugi.glade")

        self.uslugi_window = uslugi_builder.get_object("uslugi_window")

        self.uslugi_comboboxtext1_1b = uslugi_builder.get_object("uslugi_comboboxtext1_1b")
        self.uslugi_button1_1c = uslugi_builder.get_object("uslugi_button1_1c")

        self.uslugi_entry2_1b = uslugi_builder.get_object("uslugi_entry2_1b")
        self.uslugi_entry2_2b = uslugi_builder.get_object("uslugi_entry2_2b")
        self.uslugi_button2_3b = uslugi_builder.get_object("uslugi_button2_3b")

        self.uslugi_comboboxtext3_1b = uslugi_builder.get_object("uslugi_comboboxtext3_1b")
        self.uslugi_entry3_2b = uslugi_builder.get_object("uslugi_entry3_2b")
        self.uslugi_button3_3b = uslugi_builder.get_object("uslugi_button3_3b")

        self.__load_ids(self.uslugi_comboboxtext1_1b)
        self.__load_ids(self.uslugi_comboboxtext3_1b)

        uslugi_builder.connect_signals(self)

        self.uslugi_window.show()

    def __load_ids(self, comboboxtext):
        """Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru."""
        cur = self.conn.cursor()
        cur.execute("SELECT nazwa FROM uslugi;")
        idents = cur.fetchall()
        self.conn.commit()
        cur.close()

        for s in [i[0] for i in idents]:
            comboboxtext.append_text(s)

        comboboxtext.set_active(0)

    def uslugi_button1_1c_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyszukania ceny za usługę."""
        nazwa = self.uslugi_comboboxtext1_1b.get_active_text()  # SQL text
        args = [nazwa]

        try:
            cur = self.conn.cursor()
            cur.execute("SELECT cena FROM uslugi WHERE nazwa = %s;", args)
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("CENA USLUGI " + nazwa + " WYNOSI " + str(wyn) + " zł.")
            popup_window.show()
        finally:
            cur.close()

    def uslugi_button2_3b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku dodania usługi."""
        nazwa = self.uslugi_entry2_1b.get_text()  # SQL text
        cena = self.uslugi_entry2_2b.get_text()  # SQL numeric
        args = [nazwa, Decimal(cena)]
        getcontext().prec = 2

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO uslugi(nazwa, cena) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            self.uslugi_comboboxtext1_1b.append_text(nazwa)
            self.uslugi_comboboxtext3_1b.append_text(nazwa)
            popup_window = PopUp("USŁUGA " + nazwa + " ZOSTAŁA POMYŚLNIE DODANA.")
            popup_window.show()
        finally:
            cur.close()

    def uslugi_button3_3b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zmiany ceny za usługę."""
        nazwa = self.uslugi_comboboxtext3_1b.get_active_text()  # SQL text
        nowa_cena = self.uslugi_entry3_2b.get_text()  # SQL numeric
        args = [Decimal(nowa_cena), nazwa]
        getcontext().prec = 2

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE uslugi SET cena = %s WHERE nazwa = %s;", args)
        except:
            self.conn.rollback()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("CENA USŁUGI " + nazwa + " ZOSTAŁA POMYŚNIE ZMIENIONA.")
            popup_window.show()
        finally:
            cur.close()
