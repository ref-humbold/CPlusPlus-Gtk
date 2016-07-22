# -*- coding: utf-8 -*-

import gi
import psycopg2
from gi.repository import Gtk
from extra import *
from klienci import *
from uslugi import *
from zlecenia import *

class Sprzedawca:
	"""
	Klasa odpowiadająca za działanie okna interakcji sprzedawcy.
	"""
	def __init__(self, conndb):
		"""
		Tworzy nowe okno z połączeniem z bazą danych.
		"""
		self.conn = conndb
		
		SprzBuilder = Gtk.Builder()
		SprzBuilder.add_from_file("sprzedawca.glade")
		
		self.SprzWindow = SprzBuilder.get_object("SprzWindow")
		
		self.SprzButton21 = SprzBuilder.get_object("SprzButton21")
		self.SprzButton22 = SprzBuilder.get_object("SprzButton22")
		self.SprzButton23 = SprzBuilder.get_object("SprzButton23")
		
		SprzBuilder.connect_signals(self)
		
		self.SprzWindow.show()
	
	def SprzWindow_destroy_cb(self, window):
		"""
		Zamyka okno sprzedawcy.
		"""
		self.conn.close()
		Gtk.main_quit()
	
	def SprzButton21_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku zarządania zleceniami.
		"""
		ZleceniaWindow = Zlecenia(self.conn)
	
	def SprzButton22_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku zarządania klientami.
		"""
		KlienciWindow = Klienci(self.conn)
	
	def SprzButton23_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku zarządania usługami.
		"""
		UslugiWindow = Uslugi(self.conn)

