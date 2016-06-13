# -*- coding: utf-8 -*-

import gi
import psycopg2
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from decimal import *
from extra import *

class Magazynier:
	"""
	Klasa odpowiadająca za działanie okna interakcji magazyniera z bazą danych.
	"""
	def __init__(self, conndb):
		"""
		Tworzy nowe okno z połączeniem z bazą danych.
		"""
		self.conn = conndb
		
		MagBuilder = Gtk.Builder()
		MagBuilder.add_from_file("magazynier.glade")
		
		self.MagWindow = MagBuilder.get_object("MagWindow")
		
		self.MagEntryP11 = MagBuilder.get_object("MagEntryP11")
		self.MagEntryP12 = MagBuilder.get_object("MagEntryP12")
		self.MagEntryP13 = MagBuilder.get_object("MagEntryP13")
		self.MagComboboxtextP14 = MagBuilder.get_object("MagComboboxtextP14")
		self.MagButtonP15 = MagBuilder.get_object("MagButtonP15")
		
		self.MagComboboxtextP21 = MagBuilder.get_object("MagComboboxtextP21")
		self.MagEntryP22 = MagBuilder.get_object("MagEntryP22")
		self.MagEntryP23 = MagBuilder.get_object("MagEntryP23")
		self.MagEntryP24 = MagBuilder.get_object("MagEntryP24")
		self.MagButtonP25 = MagBuilder.get_object("MagButtonP25")
		
		self.MagComboboxtextP31 = MagBuilder.get_object("MagComboboxtextP31")
		self.MagButtonP31 = MagBuilder.get_object("MagButtonP31")
		
		self.__load_ids(self.MagComboboxtextP14, "czesci")
		self.__load_ids(self.MagComboboxtextP21, "zamowienia")
		self.__load_ids(self.MagComboboxtextP31, "zamowienia_unreal")
		
		MagBuilder.connect_signals(self)
		
		self.MagWindow.show()
	
	def __load_ids(self, comboboxtext, tablename):
		"""
		Ładuje identyfikatory (klucze główne) z określonej tabeli do zadanego pola wyboru.
		"""
		cur = self.conn.cursor()
		
		if tablename == "czesci":
			cur.execute("SELECT id FROM czesci;")
		elif tablename == "zamowienia":
			cur.execute("SELECT id FROM zamowienia;")
		elif tablename == "zamowienia_unreal":
			cur.execute("SELECT id FROM zamowienia WHERE data_real IS NULL;")
		
		idents = cur.fetchall()
		self.conn.commit()
		cur.close()
		
		for s in [ str( i[0] ) for i in idents ]:
			comboboxtext.append_text(s)
		
		comboboxtext.set_active(0)
	
	def __modify(self, fieldname, args, convtype):
		"""
		Dokonuje modyfikacji wybranej kolumny tabeli zamówień.
		"""
		if args[1] != "":
			getcontext().prec = 2
			args[1] = convtype( args[1] )
			
			try:
				cur = self.conn.cursor()
				
				if fieldname == "firma":
					cur.execute("UPDATE zamowienia SET firma = %s WHERE id = %s;", args)
				elif fieldname == "ilosc":
					cur.execute("UPDATE zamowienia SET ilosc = %s WHERE id = %s;", args)
				elif fieldname == "cena":
					cur.execute("UPDATE zamowienia SET cena = %s WHERE id = %s;", args)
			except:
				self.conn.rollback()
				ExtraWindow = Extra()
				ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
				return False
			else:
				self.conn.commit()
			finally:
				cur.close()
		
		return True
	
	def MagWindow_destroy_cb(self, window):
		"""
		Zamyka okno magazyniera.
		"""
		self.conn.close()
		Gtk.main_quit()
	
	def MagButtonP15_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku wysłania nowego zamówienia.
		"""
		firma = self.MagEntryP11.get_text() # SQL text
		ilosc = self.MagEntryP12.get_text() # SQL integer
		cena = self.MagEntryP13.get_text() # SQL numeric
		cze_id = self.MagComboboxtextP14.get_active_text() # SQL integer
		
		getcontext().prec = 2
		args = [ firma, int(ilosc), Decimal(cena), int(cze_id) ]
		
		try:
			cur = self.conn.cursor()
			cur.execute("INSERT INTO zamowienia(data_zamow, firma, ilosc, cena, cze_id) VALUES(now(), %s, %s, %s, %s);", args)
			cur.execute("SELECT max(id) FROM zamowienia;")
			wyn = cur.fetchone()[0]
		except:
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			self.MagComboboxtextP21.append_text( str(wyn) )
			self.MagComboboxtextP31.append_text( str(wyn) )
			ExtraWindow = Extra()
			ExtraWindow.show_label( "ZAMÓWIENIE ZOSTAŁO POMYŚLNIE WYSŁANE.\nID = "+str(wyn) )
		finally:
			cur.close()
		
	def MagButtonP25_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku modyfikacji zamówienia.
		"""
		ident = self.MagComboboxtextP21.get_active_text() # SQL integer
		firma = self.MagEntryP22.get_text() # SQL text
		ilosc = self.MagEntryP23.get_text() # SQL integer
		cena = self.MagEntryP24.get_text() # SQL numeric
		
		if not self.__modify("firma", [ firma, int(ident) ], str):
			return
		
		if not self.__modify("ilosc", [ ilosc, int(ident) ], int):
			return
		
		if not self.__modify("cena", [ cena, int(ident) ], Decimal):
			return
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("ZAMÓWIENIE NUMER "+str(ident)+" ZOSTAŁO POMYŚLNIE ZMIENIONE.")
	
	def MagButtonP31_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku odbioru zamówienia.
		"""
		ident = self.MagComboboxtextP31.get_active_text() # SQL integer
		
		args = [ int(ident) ]
		
		try:
			cur = self.conn.cursor()
			cur.execute("UPDATE TABLE zamowienia SET data_real = now() WHERE id = %s", args)
		except:
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			ExtraWindow = Extra()
			ExtraWindow.show_label("POMYŚLNIE ODEBRANO ZAMÓWIENIE NUMER "+str(ident)+".")
		finally:
			cur.close()
		
