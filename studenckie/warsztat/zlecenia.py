# -*- coding: utf-8 -*-

import gi
import psycopg2
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from decimal import *
from extra import *

class Zlecenia:
    """
    Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą zleceń.
    """
    def __init__(self, conndb):
        """
        Tworzy nowe okno z połączeniem z bazą danych.
        """
        self.conn = conndb
        
        ZleceniaBuilder = Gtk.Builder()
        ZleceniaBuilder.add_from_file("zlecenia.glade")
        
        self.ZleceniaWindow = ZleceniaBuilder.get_object("ZleceniaWindow")
        
        self.ZleceniaEntryP11 = ZleceniaBuilder.get_object("ZleceniaEntryP11")
        self.ZleceniaComboboxtextP12 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP12")
        self.ZleceniaComboboxtextP13 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP13")
        self.ZleceniaComboboxtextP14 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP14")
        self.ZleceniaButtonP15 = ZleceniaBuilder.get_object("ZleceniaButtonP15")
        
        self.ZleceniaComboboxtextP21 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP21")
        self.ZleceniaComboboxtextP22 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP22")
        self.ZleceniaButtonP23 = ZleceniaBuilder.get_object("ZleceniaButtonP23")
        
        self.ZleceniaComboboxtextP31 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP31")
        self.ZleceniaButtonP31 = ZleceniaBuilder.get_object("ZleceniaButtonP31")
        
        self.__load_ids(self.ZleceniaComboboxtextP13, "klienci")
        self.__load_ids(self.ZleceniaComboboxtextP14, "samochody")
        self.__load_ids(self.ZleceniaComboboxtextP21, "zlecenia")
        self.__load_ids(self.ZleceniaComboboxtextP22, "uslugi")
        self.__load_ids(self.ZleceniaComboboxtextP31, "zlecenia")
        
        ZleceniaBuilder.connect_signals(self)
        
        self.ZleceniaWindow.show()
    
    def __load_ids(self, comboboxtext, tablename):
        """
        Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru.
        """
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
        
        for s in [ str( i[0] ) for i in idents ]:
            comboboxtext.append_text(s)
        
        comboboxtext.set_active(0)
    
    def ZleceniaButtonP15_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku dodania nowego zlecenia.
        """
        nr_rej = self.ZleceniaEntryP11.get_text() # SQL text
        faktura = self.ZleceniaComboboxtextP12.get_active_text() # SQL boolean
        kli_id = self.ZleceniaComboboxtextP13.get_active_text() # SQL integer
        sam_model = self.ZleceniaComboboxtextP14.get_active_text() # SQL text
        
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
            self.ZleceniaComboboxtextP21.append_text( str(wyn) )
            self.ZleceniaComboboxtextP31.append_text( str(wyn) )
            ExtraWindow = Extra()
            ExtraWindow.show_label( "ZLECENIE ZOSTAŁO POMYŚLNIE ZŁOŻONE.\nID = "+str(wyn) )
        finally:
            cur.close()
    
    def ZleceniaButtonP23_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku powiązania zlecenia z usługą.
        """
        ident = self.ZleceniaComboboxtextP21.get_active_text() # SQL integer
        nazwa = self.ZleceniaComboboxtextP22.get_active_text() # SQL text
        
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
            self.ZleceniaComboboxtextP21.append_text( str(wyn) )
            self.ZleceniaComboboxtextP31.append_text( str(wyn) )
            ExtraWindow = Extra()
            ExtraWindow.show_label("POMYŚLNIE DODANO USŁUGĘ DO ZLECENIA.")
        finally:
            cur.close()
        
        ExtraWindow = Extra()
        ExtraWindow.show_label("ZLECENIE "+str(ident)+" ZOSTAŁO POMYŚLNIE ZMIENIONE.")
    
    def ZleceniaButtonP31_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku wyszukania zlecenia.
        """
        ident = self.ZleceniaComboboxtextP31.get_active_text() # SQL integer
        
        args = [ int(ident) ]
        
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
            ExtraWindow.show_label( ", ".join( map(str, wyn) ) )
        finally:
            cur.close()

