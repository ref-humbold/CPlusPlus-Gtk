# -*- coding: utf-8 -*-

import gi
import psycopg2
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from extra import *

class Mechanik:
	def __init__(self, conndb):
		self.conn = conndb
		
		MechBuilder = Gtk.Builder()
		MechBuilder.add_from_file("mechanik.glade")
		
		self.MechWindow = MechBuilder.get_object("MechWindow")
		
		self.MechComboboxtextP11 = MechBuilder.get_object("MechComboboxtextP11")
		self.MechButtonP11 = MechBuilder.get_object("MechButtonP11")
		
		self.MechComboboxtextP21 = MechBuilder.get_object("MechComboboxtextP21")
		self.MechButtonP21 = MechBuilder.get_object("MechButtonP21")
		
		self.MechComboboxtextP31 = MechBuilder.get_object("MechComboboxtextP31")
		self.MechEntryP32 = MechBuilder.get_object("MechEntryP32")
		self.MechButtonP33 = MechBuilder.get_object("MechButtonP33")
		
		self.load_unreal_ids(self.MechComboboxtextP11)
		self.load_ids(self.MechComboboxtextP21)
		self.load_ids(self.MechComboboxtextP31)
		
		MechBuilder.connect_signals(self)
		
		self.MechWindow.show()
	
	def load_ids(self, comboboxtext):
		cur = self.conn.cursor()
		cur.execute("SELECT id FROM czesci;")
		idents = cur.fetchall()
		self.conn.commit()
		cur.close()
			
		for s in [ str( i[0] ) for i in idents ]:
			comboboxtext.append_text(s)
	
	def load_unreal_ids(self, comboboxtext):
		cur = self.conn.cursor()
		cur.execute("SELECT id FROM zlecenia WHERE data_real IS NULL;")
		idents = cur.fetchall()
		self.conn.commit()
		cur.close()
		
		for s in [ str( i[0] ) for i in idents ]:
			comboboxtext.append_text(s)
	
	def MechWindow_destroy_cb(self, window):
		self.conn.close()
		Gtk.main_quit()
	
	def MechButtonP11_clicked_cb(self, button):
		ident = self.MechComboboxtextP11.get_active_text() # SQL integer
		
		cur = self.conn.cursor()
		args = [ int(ident) ]
		
		try:
			cur.execute("UPDATE TABLE zlecenia SET data_real = now() WHERE id = %s", args)
		except psycopg2.Error:
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			ExtraWindow = Extra()
			ExtraWindow.show_label("ZLECENIE "+str(ident)+" ZOSTAŁO POMYŚLNIE ZAKOŃCZONE.")
		finally:
			cur.close()
	
	def MechButtonP21_clicked_cb(self, button):
		ident = self.MechComboboxtextP21.get_active_text() # SQL integer
		
		cur = self.conn.cursor()
		args = [ int(ident) ]
		
		try:
			cur.execute("SELECT ilosc FROM czesci WHERE id = %s", args)
			wyn = cur.fetchone()[0]
		except (psycopg2.Error, TypeError):
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
	
	def MechButtonP33_clicked_cb(self, button):
		ident = self.MechComboboxtextP31.get_active_text() # SQL integer
		ilosc = self.MechEntryP32.get_text() # SQL integer
		
		cur = self.conn.cursor()
		args = [ int(ilosc), int(ident) ]
		
		try:
			cur.execute("UPDATE TABLE czesci SET ilosc = ilosc-%s WHERE id = %s", args)
		except psycopg2.Error:
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			ExtraWindow = Extra()
			ExtraWindow.show_label("POBRANO "+str(ilosc)+" JEDNOSTEK CZĘŚCI NUMER "+str(ident)+".")
		finally:
			cur.close()

