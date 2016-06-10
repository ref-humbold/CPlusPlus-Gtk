# -*- coding: utf-8 -*-

import gi
import psycopg2
from gi.repository import Gtk
from extra import *

class Klienci:
	def __init__(self, conndb):
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
		self.KlienciEntryP32 = KlienciBuilder.get_object("KlienciEntryP22")
		self.KlienciEntryP33 = KlienciBuilder.get_object("KlienciEntryP23")
		self.KlienciEntryP34 = KlienciBuilder.get_object("KlienciEntryP24")
		self.KlienciButtonP35 = KlienciBuilder.get_object("KlienciButtonP35")
		
		KlienciBuilder.connect_signals(self)
		
		self.KlienciWindow.show()
	
	def modify(self, cur, nonstr, args, convtype):
		if args[1] != nonstr:
			args[1] = convtype( args[1] )
			cur.execute("UPDATE klienci SET %s = %s WHERE id = %s;", args)
	
	def KlienciButtonP16_clicked_cb(self, button):
		imie = self.KlienciEntryP11.get_text()
		nazwisko = self.KlienciEntryP12.get_text()
		telefon = self.KlienciEntryP13.get_text()
		firma = self.KlienciEntryP14.get_text()
		rabat = self.KlienciComboboxtextP15.get_active_text()
		
		cur = self.conn.cursor()
		args = [ None if i == "" else i for i in [imie, nazwisko, telefon, firma] ]+[ None if i == " " else i for i in [rabat] ]
		args = [ None if args[i] == None else int( args[i] ) for i in range(args) if i == 2 or i == 4 ]
		cur.execute("INSERT INTO klienci(imie, nazwisko, telefon, firma, rabat) VALUES (%s, %s, %s, %s, %s);", args)
		cur.execute("SELECT max(id) FROM klienci;")
		self.conn.commit()
		wynid = cur.fetchone()[0]
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label( "NOWY KLIENT ZOSTAŁ POMYŚLNIE DODANY.\nID = "+str(wynid) )
	
	def KlienciButtonP27_clicked_cb(self, button):
		ident = self.KlienciComboboxtextP21.get_active_text()
		imie = self.KlienciEntryP22.get_text()
		nazwisko = self.KlienciEntryP23.get_text()
		telefon = self.KlienciEntryP24.get_text()
		firma = self.KlienciEntryP25.get_text()
		rabat = self.KlienciComboboxtextP26.get_active_text()
		
		cur = self.conn.cursor()
		self.modify(cur, "", ["imie", imie, ident], str)
		self.modify(cur, "", ["nazwisko", nazwisko, ident], str)
		self.modify(cur, "", ["telefon", telefon, ident], int)
		self.modify(cur, "", ["firma", firma, ident], str)
		self.modify(cur, " ", ["rabat", rabat, ident], int)
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("DANE KLIENTA NUMER "+str(ident)+" ZOSTAŁY POMYŚLNIE ZMIENIONE.")
	
	def KlienciButtonP35_clicked_cb(self, button):
		ident = self.KlienciComboboxtextP31.get_active_text()
		imie = self.KlienciEntryP32.get_text()
		nazwisko = self.KlienciEntryP33.get_text()
		telefon = self.KlienciEntryP34.get_text()
		
		cur = self.conn.cursor()
		
		if ident != "":
			args = [ident]
			cur.execute("SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE id = %s;", args)
		else:
			args = [ "%"+i+"%" for i in [imie, nazwisko, telefon] ]
			cur.execute("SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE imie LIKE %s AND nazwisko LIKE %s AND CAST(telefon AS TEXT) LIKE %s;", args)
		
		self.conn.commit()
		
		try:
			wyn = cur.fetchall()
		except ProgrammingError:
			wyn = []
		
		cur.close()
		
		ExtraWindow = Extra()
		wynstr = "BRAK WYNIKÓW!" if wyn == [] else "\n".join( map(lambda x : ", ".join( map(str, x) ), wyn) )
		ExtraWindow.show_label(wynstr)

