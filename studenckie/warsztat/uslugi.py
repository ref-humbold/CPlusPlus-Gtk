# -*- coding: utf-8 -*-

import gi
import psycopg2
from gi.repository import Gtk
from extra import *

class Uslugi:
	def __init__(self, conndb):
		self.conn = conndb
		
		UslugiBuilder = Gtk.Builder()
		UslugiBuilder.add_from_file("uslugi.glade")
		
		self.UslugiWindow = UslugiBuilder.get_object("UslugiWindow")
		
		self.UslugiComboboxtextP11 = UslugiBuilder.get_object("UslugiComboboxtextP11")
		self.UslugiButtonP11 = UslugiBuilder.get_object("UslugiButtonP11")
		
		self.UslugiEntryP21 = UslugiBuilder.get_object("UslugiEntryP21")
		self.UslugiEntryP22 = UslugiBuilder.get_object("UslugiEntryP22")
		self.UslugiButtonP23 = UslugiBuilder.get_object("UslugiButtonP23")
		
		self.UslugiComboboxtextP31 = UslugiBuilder.get_object("UslugiComboboxtextP31")
		self.UslugiEntryP32 = UslugiBuilder.get_object("UslugiEntryP32")
		self.UslugiButtonP33 = UslugiBuilder.get_object("UslugiButtonP33")
		
		UslugiBuilder.connect_signals(self)
		
		self.UslugiWindow.show()
	
	def UslugiButtonP11_clicked_cb(self, button):
		nazwa = self.UslugiComboboxtextP11.get_active_text()
		
		cur = self.conn.cursor()
		args = [nazwa]
		cur.execute("SELECT cena FROM uslugi WHERE nazwa = %s;", args)
		wyn = cur.fetchone()[0]
		self.conn.commit()
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("CENA USLUGI "+nazwa+" WYNOSI "+str(wyn)+" zł.")
	
	def UslugiButtonP23_clicked_cb(self, button):
		nazwa = self.UslugiEntryP21.get_text()
		cena = self.UslugiEntryP22.get_text()
		
		cur = self.conn.cursor()
		args = [ nazwa, int(cena) ]
		cur.execute("INSERT INTO cena VALUES(%s, %s);", args)
		self.conn.commit()
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("USŁUGA "+nazwa+" ZOSTAŁA POMYŚLNIE DODANA.")
	
	def UslugiButtonP33_clicked_cb(self, button):
		nazwa = self.UslugiComboboxtextP31.get_active_text()
		nowa_cena = self.UslugiEntryP32.get_text()
		
		cur = self.conn.cursor()
		args = [int(nowa_cena), nazwa]
		cur.execute("UPDATE TABLE uslugi SET cena = %s WHERE nazwa = %s;", args)
		self.conn.commit()
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("CENA USŁUGI "+nazwa+" ZOSTAŁA POMYŚNIE ZMIENIONA.")

