# -*- coding: utf-8 -*-

from psycopg2.extensions import AsIs
from gi.repository import Gtk
from decimal import Decimal
from extra import Extra

class Zlecenia:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą zleceń."""
    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        ZleceniaBuilder = Gtk.Builder()
        ZleceniaBuilder.add_from_file("zlecenia.glade")

        self.ZleceniaWindow = ZleceniaBuilder.get_object("ZleceniaWindow")

        self.ZleceniaEntry11ba = ZleceniaBuilder.get_object("ZleceniaEntry11ba")
        self.ZleceniaEntry11bc = ZleceniaBuilder.get_object("ZleceniaEntry11bc")
        self.ZleceniaComboboxtext12b = ZleceniaBuilder.get_object("ZleceniaComboboxtext12b")
        self.ZleceniaComboboxtext13b = ZleceniaBuilder.get_object("ZleceniaComboboxtext13b")
        self.ZleceniaComboboxtext14b = ZleceniaBuilder.get_object("ZleceniaComboboxtext14b")
        self.ZleceniaButton15b = ZleceniaBuilder.get_object("ZleceniaButton15b")

        self.ZleceniaComboboxtext21b = ZleceniaBuilder.get_object("ZleceniaComboboxtext21b")
        self.ZleceniaComboboxtext22b = ZleceniaBuilder.get_object("ZleceniaComboboxtext22b")
        self.ZleceniaButton23b = ZleceniaBuilder.get_object("ZleceniaButton23b")

        self.ZleceniaComboboxtext31b = ZleceniaBuilder.get_object("ZleceniaComboboxtext31b")
        self.ZleceniaButton31c = ZleceniaBuilder.get_object("ZleceniaButton31c")

        self.__load_ids(self.ZleceniaComboboxtext13b, "klienci")
        self.__load_ids(self.ZleceniaComboboxtext14b, "samochody")
        self.__load_ids(self.ZleceniaComboboxtext21b, "zlecenia")
        self.__load_ids(self.ZleceniaComboboxtext22b, "uslugi")
        self.__load_ids(self.ZleceniaComboboxtext31b, "zlecenia")

        ZleceniaBuilder.connect_signals(self)

        self.ZleceniaWindow.show()

    def __load_ids(self, comboboxtext, tablename):
        """Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru."""
        cur = self.conn.cursor()

        if tablename == "zlecenia":
            cur.execute("SELECT id FROM zlecenia;")
        elif tablename == "klienci":
            cur.execute("SELECT id FROM klienci;")
        elif tablename == "samochody":
            cur.execute("SELECT model FROM samochody;")
        elif tablename == "uslugi":
            cur.execute("SELECT nazwa FROM uslugi;")

        idents = cur.fetchall()
        self.conn.commit()
        cur.close()

        for s in [str(i[0]) for i in idents]:
            comboboxtext.append_text(s)

        comboboxtext.set_active(0)

    def ZleceniaButton15b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku dodania nowego zlecenia."""
        nr_rej = self.ZleceniaEntry11ba.get_text()+":"+self.ZleceniaEntry11bc.get_text() # SQL text
        faktura = self.ZleceniaComboboxtext12b.get_active_text() # SQL boolean
        kli_id = self.ZleceniaComboboxtext13b.get_active_text() # SQL integer
        sam_model = self.ZleceniaComboboxtext14b.get_active_text() # SQL text

        faktura = True if faktura == "TAK" else False
        args = [nr_rej, faktura, int(kli_id), sam_model]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO zlecenia(nr_rej, faktura, kli_id, sam_model) VALUES(%s, %s, %s, %s);", args)
            cur.execute("SELECT max(id) FROM zlecenia;")
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            return
        else:
            self.conn.commit()
            self.ZleceniaComboboxtext21b.append_text(str(wyn))
            self.ZleceniaComboboxtext31b.append_text(str(wyn))
            ExtraWindow = Extra()
            ExtraWindow.show_label("ZLECENIE ZOSTAŁO POMYŚLNIE ZŁOŻONE.\nID = "+str(wyn))
        finally:
            cur.close()

    def ZleceniaButton23b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku powiązania zlecenia z usługą."""
        ident = self.ZleceniaComboboxtext21b.get_active_text() # SQL integer
        nazwa = self.ZleceniaComboboxtext22b.get_active_text() # SQL text

        args = [int(ident), nazwa]

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO zle_usl(zle_id, usl_nazwa) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            return
        else:
            self.conn.commit()
            self.ZleceniaComboboxtext21b.append_text(str(wyn))
            self.ZleceniaComboboxtext31b.append_text(str(wyn))
            ExtraWindow = Extra()
            ExtraWindow.show_label("POMYŚLNIE DODANO USŁUGĘ DO ZLECENIA.")
        finally:
            cur.close()

        ExtraWindow = Extra()
        ExtraWindow.show_label("ZLECENIE "+str(ident)+" ZOSTAŁO POMYŚLNIE ZMIENIONE.")

    def ZleceniaButton31c_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyszukania zlecenia."""
        ident = self.ZleceniaComboboxtext31b.get_active_text() # SQL integer

        args = [int(ident)]

        try:
            cur = self.conn.cursor()
            cur.execute("SELECT id, data_zlec, data_real, nr_rej, faktura, kli_id, sam_model, koszt FROM zlecenia WHERE id = %s", args)
            wyn = cur.fetchone()[:]
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            return
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label(", ".join(map(str, wyn)))
        finally:
            cur.close()

