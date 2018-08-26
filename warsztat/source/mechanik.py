# -*- coding: utf-8 -*-
from gi import require_version

require_version("Gtk", "3.0")

from gi.repository import Gtk
from .popup import PopUp


class Mechanik:
    """Klasa odpowiadająca za działanie okna interakcji mechanika z bazą danych."""

    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        mechanik_builder = Gtk.Builder()
        mechanik_builder.add_from_file("glade/mechanik.glade")

        self.mechanik_window = mechanik_builder.get_object("mechanik_window")

        self.mechanik_comboboxtext1_1b = mechanik_builder.get_object("mechanik_comboboxtext1_1b")
        self.mechanik_button1_1c = mechanik_builder.get_object("mechanik_button1_1c")

        self.mechanik_comboboxtext2_1b = mechanik_builder.get_object("mechanik_comboboxtext2_1b")
        self.mechanik_comboboxtext2_2b = mechanik_builder.get_object("mechanik_comboboxtext2_2b")
        self.mechanik_comboboxtext2_3b = mechanik_builder.get_object("mechanik_comboboxtext2_3b")
        self.mechanik_button2_4a = mechanik_builder.get_object("mechanik_button2_4a")
        self.mechanik_button2_4b = mechanik_builder.get_object("mechanik_button2_4b")

        self.mechanik_comboboxtext3_1b = mechanik_builder.get_object("mechanik_comboboxtext3_1b")
        self.mechanik_entry3_2b = mechanik_builder.get_object("mechanik_entry3_2b")
        self.mechanik_button3_3a = mechanik_builder.get_object("mechanik_button3_3a")
        self.mechanik_button3_3b = mechanik_builder.get_object("mechanik_button3_3b")

        self.__load_ids(self.mechanik_comboboxtext1_1b, "zlecenia")
        self.__load_ids(self.mechanik_comboboxtext2_1b, "czesci")
        self.__load_ids(self.mechanik_comboboxtext2_2b, "uslugi")
        self.__load_ids(self.mechanik_comboboxtext2_3b, "samochody")
        self.__load_ids(self.mechanik_comboboxtext3_1b, "czesci")

        mechanik_builder.connect_signals(self)

        self.mechanik_window.show()

    def __load_ids(self, comboboxtext, tablename):
        """Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru."""
        cur = self.conn.cursor()

        if tablename == "czesci":
            cur.execute("SELECT id FROM czesci;")
        elif tablename == "uslugi":
            cur.execute("SELECT nazwa FROM uslugi;")
        elif tablename == "samochody":
            cur.execute("SELECT model FROM samochody;")
        elif tablename == "zlecenia":
            cur.execute("SELECT id FROM zlecenia WHERE data_real IS NULL;")

        idents = cur.fetchall()
        self.conn.commit()
        cur.close()

        for s in [str(i[0]) for i in idents]:
            comboboxtext.append_text(s)

        comboboxtext.set_active(0)

    def mechanik_window_destroy_cb(self, window):
        """Zamyka okno mechanika."""
        self.conn.close()
        Gtk.main_quit()

    def mechanik_button1_1c_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zakończenia zlecenia."""
        ident = self.mechanik_comboboxtext1_1b.get_active_text()  # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE zlecenia SET data_real = now() WHERE id = %s", args)
        except:
            self.conn.rollback()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("ZLECENIE " + str(ident) + " ZOSTAŁO POMYŚLNIE ZAKOŃCZONE.")
            popup_window.show()
        finally:
            cur.close()

    def mechanik_button2_4a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku przypisania części samochodowej do usługi."""
        ident = self.mechanik_comboboxtext2_1b.get_active_text()  # SQL integer
        nazwa = self.mechanik_comboboxtext2_2b.get_active_text()  # SQL text

        args = [int(ident), nazwa]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO czeusl(cze_id, usl_nazwa) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            cur.close()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("POMYŚLNIE PRZYPISANO CZĘŚĆ DO USŁUGI.")
            popup_window.show()
        finally:
            cur.close()

    def mechanik_button2_4b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku przypisania części samochodowej do modelu samochodu."""
        ident = self.mechanik_comboboxtext2_1b.get_active_text()  # SQL integer
        model = self.mechanik_comboboxtext2_3b.get_active_text()  # SQL text

        args = [int(ident), model]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO czesam(cze_id, sam_model) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            cur.close()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("POMYŚLNIE PRZYPISANO CZĘŚĆ DO MODELU SAMOCHODU.")
            popup_window.show()
        finally:
            cur.close()

    def mechanik_button3_3a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyświetlenia ilości części."""
        ident = self.mechanik_comboboxtext3_1b.get_active_text()  # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("SELECT ilosc FROM czesci WHERE id = %s", args)
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("W MAGAZYNIE ZNAJDUJE SIĘ " + str(wyn) +
                                 " CZĘŚCI NUMER " + str(ident) + ".")
            popup_window.show()
        finally:
            cur.close()

    def mechanik_button3_3b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku pobrania określonej ilości części."""
        ident = self.mechanik_comboboxtext3_1b.get_active_text()  # SQL integer
        ilosc = self.mechanik_entry3_2b.get_text()  # SQL integer

        args = [int(ilosc), int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE czesci SET ilosc = ilosc-%s WHERE id = %s", args)
        except:
            self.conn.rollback()
            popup_window = PopUp("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            popup_window.show()
        else:
            self.conn.commit()
            popup_window = PopUp("POBRANO " + str(ilosc) +
                                 " JEDNOSTEK CZĘŚCI NUMER " + str(ident) + ".")
            popup_window.show()
        finally:
            cur.close()
