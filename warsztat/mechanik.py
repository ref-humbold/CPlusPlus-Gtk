# -*- coding: utf-8 -*-

import gi
import psycopg2
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from extra import Extra

class Mechanik:
    """Klasa odpowiadająca za działanie okna interakcji mechanika z bazą danych."""
    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        MechBuilder = Gtk.Builder()
        MechBuilder.add_from_file("mechanik.glade")

        self.MechWindow = MechBuilder.get_object("MechWindow")

        self.MechComboboxtext11b = MechBuilder.get_object("MechComboboxtext11b")
        self.MechButton11c = MechBuilder.get_object("MechButton11c")

        self.MechComboboxtext21b = MechBuilder.get_object("MechComboboxtext21b")
        self.MechComboboxtext22b = MechBuilder.get_object("MechComboboxtext22b")
        self.MechComboboxtext23b = MechBuilder.get_object("MechComboboxtext23b")
        self.MechButton24a = MechBuilder.get_object("MechButton24a")
        self.MechButton24b = MechBuilder.get_object("MechButton24b")

        self.MechComboboxtext31b = MechBuilder.get_object("MechComboboxtext31b")
        self.MechEntry32b = MechBuilder.get_object("MechEntry32b")
        self.MechButton33a = MechBuilder.get_object("MechButton33a")
        self.MechButton33b = MechBuilder.get_object("MechButton33b")

        self.__load_ids(self.MechComboboxtext11b, "zlecenia")
        self.__load_ids(self.MechComboboxtext21b, "czesci")
        self.__load_ids(self.MechComboboxtext22b, "uslugi")
        self.__load_ids(self.MechComboboxtext23b, "samochody")
        self.__load_ids(self.MechComboboxtext31b, "czesci")

        MechBuilder.connect_signals(self)

        self.MechWindow.show()

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

    def MechWindow_destroy_cb(self, window):
        """Zamyka okno mechanika."""
        self.conn.close()
        Gtk.main_quit()

    def MechButton11c_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zakończenia zlecenia."""
        ident = self.MechComboboxtext11b.get_active_text() # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE zlecenia SET data_real = now() WHERE id = %s", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("ZLECENIE "+str(ident)+" ZOSTAŁO POMYŚLNIE ZAKOŃCZONE.")
        finally:
            cur.close()

    def MechButton24a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku przypisania części samochodowej do usługi."""
        ident = self.MechComboboxtext21b.get_active_text() # SQL integer
        nazwa = self.MechComboboxtext22b.get_active_text() # SQL text

        args = [ int(ident), nazwa ]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO czeusl(cze_id, usl_nazwa) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            cur.close()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("POMYŚLNIE PRZYPISANO CZĘŚĆ DO USŁUGI.")
        finally:
            cur.close()

    def MechButton24b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku przypisania części samochodowej do modelu samochodu."""
        ident = self.MechComboboxtext21b.get_active_text() # SQL integer
        model = self.MechComboboxtext23b.get_active_text() # SQL text

        args = [ int(ident), model ]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO czesam(cze_id, sam_model) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            cur.close()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("POMYŚLNIE PRZYPISANO CZĘŚĆ DO MODELU SAMOCHODU.")
        finally:
            cur.close()

    def MechButton33a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyświetlenia ilości części."""
        ident = self.MechComboboxtext31b.get_active_text() # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("SELECT ilosc FROM czesci WHERE id = %s", args)
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("W MAGAZYNIE ZNAJDUJE SIĘ "+str(wyn)+" CZĘŚCI NUMER "+str(ident)+".")
        finally:
            cur.close()

    def MechButton33b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku pobrania określonej ilości części."""
        ident = self.MechComboboxtext31b.get_active_text() # SQL integer
        ilosc = self.MechEntry32b.get_text() # SQL integer

        args = [int(ilosc), int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE czesci SET ilosc = ilosc-%s WHERE id = %s", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("POBRANO "+str(ilosc)+" JEDNOSTEK CZĘŚCI NUMER "+str(ident)+".")
        finally:
            cur.close()

