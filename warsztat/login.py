# -*- coding: utf-8 -*-

import gi
import re
import psycopg2
from gi.repository import Gtk
from sprzedawca import *
from mechanik import *
from magazynier import *
from extra import *

class Login:
    """
    Klasa odpowiadająca za działanie okna logowania do bazy danych.
    """
    def __init__(self):
        """
        Tworzy nowe okno logowania.
        """
        self.is_logged = False
        
        LoginBuilder = Gtk.Builder()
        LoginBuilder.add_from_file("login.glade")
        
        self.LoginWindow = LoginBuilder.get_object("LoginWindow")
        
        self.LoginEntry1b = LoginBuilder.get_object("LoginEntry1b")
        self.LoginEntry2b = LoginBuilder.get_object("LoginEntry2b")
        self.LoginButton3b = LoginBuilder.get_object("LoginButton3b")
        
        LoginBuilder.connect_signals(self)
        
        self.LoginEntry2b.set_invisible_char("#")
        self.LoginEntry2b.set_visibility(False)
        
        self.LoginWindow.show()
    
    def open_error_window(self, msg):
        """
        Tworzy nowe okno wyświetlające komunikat o błedzie.
        """
        self.LoginEntry1b.set_text("")
        self.LoginEntry2b.set_text("")
        ExtraWindow = Extra()
        ExtraWindow.show_label(msg)
    
    def LoginWindow_destroy_cb(self, window):
        """
        Zamyka okno logowania.
        """
        if not self.is_logged:
            Gtk.main_quit()
        
    def LoginButton3b_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku zalogowania do bazy danych.
        """
        lgn = self.LoginEntry1b.get_text()
        pwd = self.LoginEntry2b.get_text()
        
        if re.match(r"^[A-Za-z]*$", lgn) != None and re.match(r"^[A-Za-z0-9]*$", pwd) != None:
            try:
                conn = psycopg2.connect(database = "warsztat", user = lgn, password = pwd)
            except:
                self.open_error_window("NIEPOPRAWNY LOGIN LUB HASŁO.\nSPRÓBUJ PONOWNIE.")
                return
            else:
                self.is_logged = True
            
            args = [lgn]
            
            try:
                cur = conn.cursor()
                cur.execute('SELECT r2.rolname FROM pg_roles AS r1 JOIN pg_auth_members AS m ON r1.oid = m.member JOIN pg_roles AS r2 ON m.roleid = r2.oid WHERE r1.rolname = %s;', args)
            except:
                conn.rollback()
                cur.close()
                conn.close()
                self.open_error_window("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                return
            
            try:
                wyn = cur.fetchone()[0]
            except:
                conn.rollback()
                conn.close()
                self.open_error_window("DOSTĘP DO BAZY JEST ZAMKNIĘTY DLA UŻYTKOWNIKA "+lgn+".")
                return
            else:
                conn.commit()
                self.LoginWindow.destroy()
            finally:
                cur.close()
            
            if wyn == "sprzedawca":
                WorkerWindow = Sprzedawca(conn)
            elif wyn == "mechanik":
                WorkerWindow = Mechanik(conn)
            elif wyn == "magazynier":
                WorkerWindow = Magazynier(conn)
            else:
                conn.close()
                self.open_error_window("DOSTĘP DO BAZY JEST ZAMKNIĘTY DLA UŻYTKOWNIKA "+lgn+".")
        else:
            self.open_error_window("NIEPOPRAWNY LOGIN LUB HASŁO.\nSPRÓBUJ PONOWNIE.")

