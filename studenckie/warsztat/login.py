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
	def __init__(self):
		self.is_logged = False
		
		LoginBuilder = Gtk.Builder()
		LoginBuilder.add_from_file("login.glade")
		
		self.LoginWindow = LoginBuilder.get_object("LoginWindow")
		
		self.LoginEntry21 = LoginBuilder.get_object("LoginEntry21")
		self.LoginEntry22 = LoginBuilder.get_object("LoginEntry22")
		self.LoginButton23 = LoginBuilder.get_object("LoginButton23")
		
		LoginBuilder.connect_signals(self)
		
		self.LoginEntry22.set_invisible_char("#")
		self.LoginEntry22.set_visibility(False)
		
		self.LoginWindow.show()
	
	def open_error_window(self, msg):
		self.LoginEntry21.set_text("")
		self.LoginEntry22.set_text("")
		ExtraWindow = Extra()
		ExtraWindow.show_label(msg)
	
	def LoginWindow_destroy_cb(self, window):
		if not self.is_logged:
			Gtk.main_quit()
		
	def LoginButton23_clicked_cb(self, button):
		lgn = self.LoginEntry21.get_text()
		pwd = self.LoginEntry22.get_text()
		
		if re.match(r"^[A-Za-z0-9]*$", pwd) != None:
			try:
				conn = psycopg2.connect(database = "warsztat", user = lgn, password = pwd)
			except psycopg2.Error:
				self.open_error_window("NIEPOPRAWNY LOGIN LUB HASŁO.\nSPRÓBUJ PONOWNIE.")
				return
			else:
				self.is_logged = True
			
			cur = conn.cursor()
			args = [lgn]
			
			try:
				cur.execute('SELECT r2.rolname FROM pg_roles AS r1 JOIN pg_auth_members AS m ON r1.oid = m.member JOIN pg_roles AS r2 ON m.roleid = r2.oid WHERE r1.rolname = %s;', args)
			except psycopg2.Error:
				conn.rollback()
				cur.close()
				conn.close()
				self.open_error_window("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
				return
			
			try:
				wyn = cur.fetchone()[0]
			except (psycopg2.Error, TypeError):
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

