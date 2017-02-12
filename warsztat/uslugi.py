# -*- coding: utf-8 -*-

import gi
import psycopg2
from gi.repository import Gtk
from extra import *

class Uslugi:
    """
    Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą usług.
    """
    def __init__(self, conndb):
        """
        Tworzy nowe okno z połączeniem z bazą danych.
        """
        self.conn = conndb
        
        UslugiBuilder = Gtk.Builder()
        UslugiBuilder.add_from_file("uslugi.glade")
        
        self.UslugiWindow = UslugiBuilder.get_object("UslugiWindow")
        
        self.UslugiComboboxtext11b = UslugiBuilder.get_object("UslugiComboboxtext11b")
        self.UslugiButton11c = UslugiBuilder.get_object("UslugiButton11c")
        
        self.UslugiEntry21b = UslugiBuilder.get_object("UslugiEntry21b")
        self.UslugiEntry22b = UslugiBuilder.get_object("UslugiEntry22b")
        self.UslugiButton23b = UslugiBuilder.get_object("UslugiButton23b")
        
        self.UslugiComboboxtext31b = UslugiBuilder.get_object("UslugiComboboxtext31b")
        self.UslugiEntry32b = UslugiBuilder.get_object("UslugiEntry32b")
        self.UslugiButton33b = UslugiBuilder.get_object("UslugiButton33b")
        
        self.__load_ids(self.UslugiComboboxtext11b)
        self.__load_ids(self.UslugiComboboxtext31b)
        
        UslugiBuilder.connect_signals(self)
        
        self.UslugiWindow.show()
    
    def __load_ids(self, comboboxtext):
        """
        Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru.
        """
        cur = self.conn.cursor()
        cur.execute("SELECT nazwa FROM uslugi;")
        idents = cur.fetchall()
        self.conn.commit()
        cur.close()
        
        for s in [ i[0] for i in idents ]:
            comboboxtext.append_text(s)
        
        comboboxtext.set_active(0)
    
    def UslugiButton11c_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku wyszukania ceny za usługę.
        """
        nazwa = self.UslugiComboboxtext11b.get_active_text() # SQL text
        
        args = [nazwa]
        
        try:
            cur = self.conn.cursor()
            cur.execute("SELECT cena FROM uslugi WHERE nazwa = %s;", args)
            wyn = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("CENA USLUGI "+nazwa+" WYNOSI "+str(wyn)+" zł.")
        finally:
            cur.close()
    
    def UslugiButton23b_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku dodania usługi.
        """
        nazwa = self.UslugiEntry21b.get_text() # SQL text
        cena = self.UslugiEntry22b.get_text() # SQL numeric
        
        getcontext().prec = 2
        args = [ nazwa, Decimal(cena) ]
        
        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO uslugi(nazwa, cena) VALUES(%s, %s);", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            self.UslugiComboboxtext11b.append_text(nazwa)
            self.UslugiComboboxtext31b.append_text(nazwa)
            ExtraWindow = Extra()
            ExtraWindow.show_label("USŁUGA "+nazwa+" ZOSTAŁA POMYŚLNIE DODANA.")
        finally:
            cur.close()
    
    def UslugiButton33b_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku zmiany ceny za usługę.
        """
        nazwa = self.UslugiComboboxtext31b.get_active_text() # SQL text
        nowa_cena = self.UslugiEntry32b.get_text() # SQL numeric
        
        getcontext().prec = 2
        args = [Decimal(nowa_cena), nazwa]
        
        try:
            cur = self.conn.cursor()
            cur.execute("UPDATE TABLE uslugi SET cena = %s WHERE nazwa = %s;", args)
        except:
            self.conn.rollback()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            ExtraWindow = Extra()
            ExtraWindow.show_label("CENA USŁUGI "+nazwa+" ZOSTAŁA POMYŚNIE ZMIENIONA.")
        finally:
            cur.close()

