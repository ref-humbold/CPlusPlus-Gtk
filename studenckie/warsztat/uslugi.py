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
		
		self.load_ids(self.UslugiComboboxtextP11)
		self.load_ids(self.UslugiComboboxtextP31)
		
		UslugiBuilder.connect_signals(self)
		
		self.UslugiWindow.show()
	
	def load_ids(self, comboboxtext):
		cur = self.conn.cursor()
		cur.execute("SELECT nazwa FROM uslugi;")
		idents = cur.fetchall()
		self.conn.commit()
		cur.close()
		
		for s in [ i[0] for i in idents ]:
			comboboxtext.append_text(s)
	
	def UslugiButtonP11_clicked_cb(self, button):
		nazwa = self.UslugiComboboxtextP11.get_active_text() # SQL text
		
		cur = self.conn.cursor()
		args = [nazwa]
		
		try:
			cur.execute("SELECT cena FROM uslugi WHERE nazwa = %s;", args)
			wyn = cur.fetchone()[0]
		except (psycopg2.Error, TypeError):
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
	
	def UslugiButtonP23_clicked_cb(self, button):
		nazwa = self.UslugiEntryP21.get_text() # SQL text
		cena = self.UslugiEntryP22.get_text() # SQL numeric
		
		getcontext().prec = 2
		
		cur = self.conn.cursor()
		args = [ nazwa, Decimal(cena) ]
		
		try:
			cur.execute("INSERT INTO uslugi(nazwa, cena) VALUES(%s, %s);", args)
		except psycopg2.Error:
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			self.UslugiComboboxtextP11.append_text(nazwa)
			self.UslugiComboboxtextP31.append_text(nazwa)
			ExtraWindow = Extra()
			ExtraWindow.show_label("USŁUGA "+nazwa+" ZOSTAŁA POMYŚLNIE DODANA.")
		finally:
			cur.close()
	
	def UslugiButtonP33_clicked_cb(self, button):
		nazwa = self.UslugiComboboxtextP31.get_active_text() # SQL text
		nowa_cena = self.UslugiEntryP32.get_text() # SQL numeric
		
		getcontext().prec = 2
		
		cur = self.conn.cursor()
		args = [Decimal(nowa_cena), nazwa]
		
		try:
			cur.execute("UPDATE TABLE uslugi SET cena = %s WHERE nazwa = %s;", args)
		except psycopg2.Error:
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			ExtraWindow = Extra()
			ExtraWindow.show_label("CENA USŁUGI "+nazwa+" ZOSTAŁA POMYŚNIE ZMIENIONA.")
		finally:
			cur.close()

