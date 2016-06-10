# -*- coding: utf-8 -*-

import gi
import psycopg2
from gi.repository import Gtk
from extra import *

class Magazynier:
	def __init__(self, conndb):
		self.conn = conndb
		
		MagBuilder = Gtk.Builder()
		MagBuilder.add_from_file("magazynier.glade")
		
		self.MagWindow = MagBuilder.get_object("MagWindow")
		
		self.MagEntryP11 = MagBuilder.get_object("MagEntryP11")
		self.MagEntryP12 = MagBuilder.get_object("MagEntryP12")
		self.MagEntryP13 = MagBuilder.get_object("MagEntryP13")
		self.MagButtonP14 = MagBuilder.get_object("MagButtonP14")
		
		self.MagComboboxtextP21 = MagBuilder.get_object("MagComboboxtextP21")
		self.MagEntryP22 = MagBuilder.get_object("MagEntryP22")
		self.MagEntryP23 = MagBuilder.get_object("MagEntryP23")
		self.MagEntryP24 = MagBuilder.get_object("MagEntryP24")
		self.MagButtonP25 = MagBuilder.get_object("MagButtonP25")
		
		self.MagComboboxtextP31 = MagBuilder.get_object("MagComboboxtextP31")
		self.MagButtonP31 = MagBuilder.get_object("MagButtonP31")
		
		MagBuilder.connect_signals(self)
		
		self.MagWindow.show()
	
	def modify(self, cur, args, convtype):
		if args[1] != "":
			args[1] = convtype( args[1] )
			cur.execute("UPDATE zamowienia SET %s = %s WHERE id = %s;", args)
	
	def MagButtonP14_clicked_cb(self, button):
		firma = self.MagEntryP11.get_text()
		ilosc = self.MagEntryP12.get_text()
		cena = self.MagEntryP13.get_text()
		
		cur = self.conn.cursor()
		args = [ firma, int(ilosc), int(cena) ]
		cur.execute("INSERT INTO zamowienia() VALUES(now(), %s, %s, %s);", args)
		self.conn.commit()
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label( "ZAMÓWIENIE ZOSTAŁO POMYŚLNIE WYSŁANE.\nID = "+str(wynid) )
		
	def MagButtonP25_clicked_cb(self, button):
		ident = self.MagComboboxtextP21.get_active_text()
		firma = self.MagEntryP22.get_text()
		ilosc = self.MagEntryP23.get_text()
		cena = self.MagEntryP24.get_text()
		
		cur = self.conn.cursor()
		modify(cur, [ "firma", firma, int(ident) ], str)
		modify(cur, [ "ilosc", ilosc, int(ident) ], int)
		modify(cur, [ "cena", cena, int(ident) ], float)
		self.conn.commit()
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("ZAMÓWIENIE NUMER "+str(ident)+" ZOSTAŁO POMYŚLNIE ZMIENIONE.")
	
	def MagButtonP31_clicked_cb(self, button):
		ident = self.MagComboboxtextP31.get_active_text()
		
		cur = self.conn.cursor()
		args = [ int(ident) ]
		cur.execute("UPDATE TABLE zamowienia SET data_real = now() WHERE id = %s", args)
		self.conn.commit()
		cur.close()
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("POMYŚLNIE ODEBRANO ZAMÓWIENIE NUMER "+str(ident)+".")

