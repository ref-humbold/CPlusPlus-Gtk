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
		self.MechComboboxtextP22 = MechBuilder.get_object("MechComboboxtextP22")
		self.MechComboboxtextP23 = MechBuilder.get_object("MechComboboxtextP23")
		self.MechButtonP24L = MechBuilder.get_object("MechButtonP24L")
		self.MechButtonP24P = MechBuilder.get_object("MechButtonP24P")
		
		self.MechComboboxtextP31 = MechBuilder.get_object("MechComboboxtextP31")
		self.MechEntryP32 = MechBuilder.get_object("MechEntryP32")
		self.MechButtonP33L = MechBuilder.get_object("MechButtonP33L")
		self.MechButtonP33P = MechBuilder.get_object("MechButtonP33P")
		
		self.load_ids(self.MechComboboxtextP11, "zlecenia")
		self.load_ids(self.MechComboboxtextP21, "czesci")
		self.load_ids(self.MechComboboxtextP22, "uslugi")
		self.load_ids(self.MechComboboxtextP23, "samochody")
		self.load_ids(self.MechComboboxtextP31, "czesci")
		
		MechBuilder.connect_signals(self)
		
		self.MechWindow.show()
	
	def load_ids(self, comboboxtext, tablename):
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
			
		for s in [ str( i[0] ) for i in idents ]:
			comboboxtext.append_text(s)
		
		comboboxtext.set_active(0)
	
	def MechWindow_destroy_cb(self, window):
		self.conn.close()
		Gtk.main_quit()
	
	def MechButtonP11_clicked_cb(self, button):
		ident = self.MechComboboxtextP11.get_active_text() # SQL integer
		
		args = [ int(ident) ]
		
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
	
	def MechButtonP24L_clicked_cb(self, button):
		ident = self.MechComboboxtextP21.get_active_text() # SQL integer
		nazwa = self.MechComboboxtextP22.get_active_text() # SQL text
		
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
	
	def MechButtonP24P_clicked_cb(self, button):
		ident = self.MechComboboxtextP21.get_active_text() # SQL integer
		model = self.MechComboboxtextP23.get_active_text() # SQL text
		
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
	
	def MechButtonP33L_clicked_cb(self, button):
		ident = self.MechComboboxtextP31.get_active_text() # SQL integer
		
		args = [ int(ident) ]
		
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
	
	def MechButtonP33P_clicked_cb(self, button):
		ident = self.MechComboboxtextP31.get_active_text() # SQL integer
		ilosc = self.MechEntryP32.get_text() # SQL integer
		
		args = [ int(ilosc), int(ident) ]
		
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

