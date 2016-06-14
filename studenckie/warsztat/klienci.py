# -*- coding: utf-8 -*-

import gi
import psycopg2
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from extra import *

class Klienci:
	"""
	Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą klientów.
	"""
	def __init__(self, conndb):
		"""
		Tworzy nowe okno z połączeniem z bazą danych.
		"""
		self.conn = conndb
		
		KlienciBuilder = Gtk.Builder()
		KlienciBuilder.add_from_file("klienci.glade")
		
		self.KlienciWindow = KlienciBuilder.get_object("KlienciWindow")
		
		self.KlienciEntryP11 = KlienciBuilder.get_object("KlienciEntryP11")
		self.KlienciEntryP12 = KlienciBuilder.get_object("KlienciEntryP12")
		self.KlienciEntryP13 = KlienciBuilder.get_object("KlienciEntryP13")
		self.KlienciEntryP14 = KlienciBuilder.get_object("KlienciEntryP14")
		self.KlienciComboboxtextP15 = KlienciBuilder.get_object("KlienciComboboxtextP15")
		self.KlienciButtonP16 = KlienciBuilder.get_object("KlienciButtonP16")
		
		self.KlienciComboboxtextP21 = KlienciBuilder.get_object("KlienciComboboxtextP21")
		self.KlienciEntryP22 = KlienciBuilder.get_object("KlienciEntryP22")
		self.KlienciEntryP23 = KlienciBuilder.get_object("KlienciEntryP23")
		self.KlienciEntryP24 = KlienciBuilder.get_object("KlienciEntryP24")
		self.KlienciEntryP25 = KlienciBuilder.get_object("KlienciEntryP25")
		self.KlienciComboboxtextP26 = KlienciBuilder.get_object("KlienciComboboxtextP26")
		self.KlienciButtonP27 = KlienciBuilder.get_object("KlienciButtonP27")
		
		self.KlienciComboboxtextP31 = KlienciBuilder.get_object("KlienciComboboxtextP31")
		self.KlienciEntryP32 = KlienciBuilder.get_object("KlienciEntryP32")
		self.KlienciEntryP33 = KlienciBuilder.get_object("KlienciEntryP33")
		self.KlienciEntryP34 = KlienciBuilder.get_object("KlienciEntryP34")
		self.KlienciButtonP35 = KlienciBuilder.get_object("KlienciButtonP35")
		
		self.KlienciComboboxtextP31.append_text("-")
		self.__load_ids(self.KlienciComboboxtextP21)
		self.__load_ids(self.KlienciComboboxtextP31)
		
		KlienciBuilder.connect_signals(self)
		
		self.KlienciWindow.show()
	
	def __load_ids(self, comboboxtext):
		"""
		Ładuje identyfikatory (klucze główne) z tabeli klientów do zadanego pola wyboru.
		"""
		cur = self.conn.cursor()
		cur.execute("SELECT id FROM klienci;")
		idents = cur.fetchall()
		self.conn.commit()
		cur.close()
		
		for s in [ str( i[0] ) for i in idents ]:
			comboboxtext.append_text(s)
		
		comboboxtext.set_active(0)
	
	def __modify(self, cur, nonstr, fieldname, args, convtype):
		"""
		Dokonuje modyfikacji wybranej kolumny tabeli klientów.
		"""
		if args[0] != nonstr:
			args[0] = convtype( args[0] )
			
			try:
				if fieldname == "imie":
					cur.execute("UPDATE klienci SET imie = %s WHERE id = %s;", args)
				elif fieldname == "nazwisko":
					cur.execute("UPDATE klienci SET nazwisko = %s WHERE id = %s;", args)
				elif fieldname == "telefon":
					cur.execute("UPDATE klienci SET telefon = %s WHERE id = %s;", args)
				elif fieldname == "firma":
					cur.execute("UPDATE klienci SET firma = %s WHERE id = %s;", args)
				elif fieldname == "rabat":
					cur.execute("UPDATE klienci SET rabat = %s WHERE id = %s;", args)
			except:
				self.conn.rollback()
				cur.close()
				ExtraWindow = Extra()
				ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
				return False
		
		return True
	
	def KlienciButtonP16_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku dodania nowego klienta.
		"""
		imie = self.KlienciEntryP11.get_text() # SQL text
		nazwisko = self.KlienciEntryP12.get_text() # SQL text
		telefon = self.KlienciEntryP13.get_text() # SQL integer
		firma = self.KlienciEntryP14.get_text() # SQL text
		rabat = self.KlienciComboboxtextP15.get_active_text() # SQL integer
		
		args = [ None if i == "" else i for i in [imie, nazwisko, telefon, firma] ]+[ int(rabat) ]
		args[2] = None if args[2] == None else int( args[2] )
		
		try:
			cur = self.conn.cursor()
			cur.execute("INSERT INTO klienci(imie, nazwisko, telefon, firma, rabat) VALUES (%s, %s, %s, %s, %s);", args)
			cur.execute("SELECT max(id) FROM klienci;")
			wynid = cur.fetchone()[0]
		except:
			self.conn.rollback()
			cur.close()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
		else:
			self.conn.commit()
			self.KlienciComboboxtextP21.append_text( str(wynid) )
			self.KlienciComboboxtextP31.append_text( str(wynid) )
			ExtraWindow = Extra()
			ExtraWindow.show_label( "NOWY KLIENT ZOSTAŁ POMYŚLNIE DODANY.\nID = "+str(wynid) )
		finally:
			cur.close()
	
	def KlienciButtonP27_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku modyfikacji danych klienta.
		"""
		ident = self.KlienciComboboxtextP21.get_active_text() # SQL integer
		imie = self.KlienciEntryP22.get_text() # SQL text
		nazwisko = self.KlienciEntryP23.get_text() # SQL text
		telefon = self.KlienciEntryP24.get_text() # SQL integer
		firma = self.KlienciEntryP25.get_text() # SQL text
		rabat = self.KlienciComboboxtextP26.get_active_text() # SQL integer
		
		cur = self.conn.cursor()
		
		if not self.__modify(cur, "", "imie", [ imie, int(ident) ], str):
			return
		
		if not self.__modify(cur, "", "nazwisko", [ nazwisko, int(ident) ], str):
			return
		
		if not self.__modify(cur, "", "telefon", [ telefon, int(ident) ], int):
			return
		
		if not self.__modify(cur, "", "firma", [ firma, int(ident) ], str):
			return
		
		if not self.__modify(cur, "-", "rabat", [ rabat, int(ident) ], int):
			return
		
		self.conn.commit()
		cur.close()
		ExtraWindow = Extra()
		ExtraWindow.show_label("DANE KLIENTA NUMER "+str(ident)+" ZOSTAŁY POMYŚLNIE ZMIENIONE.")
	
	def KlienciButtonP35_clicked_cb(self, button):
		"""
		Reaguje na kliknięcie przycisku wyszukania klienta.
		"""
		ident = self.KlienciComboboxtextP31.get_active_text() # SQL integer
		imie = self.KlienciEntryP32.get_text() # SQL text
		nazwisko = self.KlienciEntryP33.get_text() # SQL text
		telefon = self.KlienciEntryP34.get_text() # SQL integer
		
		cur = self.conn.cursor()
		
		if ident != "-":
			args = [ int(ident) ]
			
			try:
				cur.execute("SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE id = %s;", args)
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
		else:
			args = [ "%"+str(i)+"%" for i in [imie, nazwisko, telefon] ]
			
			try:
				cur.execute("SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE imie LIKE %s AND nazwisko LIKE %s AND CAST(telefon AS text) LIKE %s;", args)
				wyn = cur.fetchall()[:]
			except:
				self.conn.rollback()
				ExtraWindow = Extra()
				ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
				return
			else:
				self.conn.commit()
				out_str = "BRAK WYNIKÓW!" if wyn == [] else "\n".join( map(lambda x : ", ".join( map(str, x) ), wyn) )
				ExtraWindow = Extra()
				ExtraWindow.show_label(out_str)
			finally:
				cur.close()

