# -*- coding: utf-8 -*-

import gi
import psycopg2
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from decimal import *
from extra import *

class Zlecenia:
	def __init__(self, conndb):
		self.conn = conndb
		
		ZleceniaBuilder = Gtk.Builder()
		ZleceniaBuilder.add_from_file("zlecenia.glade")
		
		self.ZleceniaWindow = ZleceniaBuilder.get_object("ZleceniaWindow")
		
		self.ZleceniaEntryP11 = ZleceniaBuilder.get_object("ZleceniaEntryP11")
		self.ZleceniaComboboxtextP12 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP12")
		self.ZleceniaEntryP13 = ZleceniaBuilder.get_object("ZleceniaEntryP13")
		self.ZleceniaComboboxtextP14 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP14")
		self.ZleceniaComboboxtextP15 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP15")
		self.ZleceniaButtonP16 = ZleceniaBuilder.get_object("ZleceniaButtonP16")
		
		self.ZleceniaComboboxtextP21 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP21")
		self.ZleceniaEntryP22 = ZleceniaBuilder.get_object("ZleceniaEntryP22")
		self.ZleceniaComboboxtextP23 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP23")
		self.ZleceniaButtonP24 = ZleceniaBuilder.get_object("ZleceniaButtonP24")
		
		self.ZleceniaComboboxtextP31 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP31")
		self.ZleceniaButtonP31 = ZleceniaBuilder.get_object("ZleceniaButtonP31")
		
		self.load_ids(self.ZleceniaComboboxtextP21, "id", "zlecenia")
		self.load_ids(self.ZleceniaComboboxtextP31, "id", "zlecenia")
		self.load_ids(self.ZleceniaComboboxtextP14, "id", "klienci")
		self.load_ids(self.ZleceniaComboboxtextP15, "model", "samochody")
		
		ZleceniaBuilder.connect_signals(self)
		
		self.ZleceniaWindow.show()
	
	def load_ids(self, comboboxtext, fieldname, tablename):
		cur = self.conn.cursor()
		cur.execute( "SELECT %s FROM %s;", [ AsIs(fieldname), AsIs(tablename) ] )
		idents = cur.fetchall()
		self.conn.commit()
		cur.close()
		
		for s in [ str( i[0] ) for i in idents ]:
			comboboxtext.append_text(s)
	
	def modify(self, nonstr, args, convtype):
		if args[1] != None and args[1] != nonstr:
			args[1] = convtype( args[1] )
			cur = self.conn.cursor()
			
			try:
				cur.execute("UPDATE zlecenia SET %s = %s WHERE id = %s;", args)
			except psycopg2.Error:
				self.conn.rollback()
				ExtraWindow = Extra()
				ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
				return False
			else:
				self.conn.commit()
			finally:
				cur.close()
			
		return True
	
	def ZleceniaButtonP16_clicked_cb(self, button):
		nr_rej = self.ZleceniaEntryP11.get_text() # SQL text
		faktura = self.ZleceniaComboboxtextP12.get_active_text() # SQL boolean
		uslugi = self.ZleceniaEntryP13.get_text() # SQL text
		kli_id = self.ZleceniaComboboxtextP14.get_active_text() # SQL integer
		sam_model = self.ZleceniaComboboxtextP15.get_active_text() # SQL text
		
		uslugi = [ i.strip() for i in uslugi.split(",") ]
		faktura = True if faktura == "TAK" else False
		
		cur = self.conn.cursor()
		args = [ nr_rej, faktura, int(kli_id), sam_model ]
		
		try:
			cur.execute("INSERT INTO zlecenia(nr_rej, faktura, kli_id, sam_model) VALUES(%s, %s, %s, %s);", args)
			cur.execute("SELECT max(id) FROM zlecenia;")
			wyn = cur.fetchone()[0]
			
			for args in [ [int(wyn), i] for i in uslugi ]:
				cur.execute("INSERT INTO zle_usl(zle_id, usl_nazwa) VALUES(%s, %s);", args)
			
		except (psycopg2.Error, TypeError):
			self.conn.rollback()
			ExtraWindow = Extra()
			ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
			return
		else:
			self.conn.commit()
			self.ZleceniaComboboxtextP21.append_text( str(wyn) )
			self.ZleceniaComboboxtextP31.append_text( str(wyn) )
			ExtraWindow = Extra()
			ExtraWindow.show_label( "ZLECENIE ZOSTAŁO POMYŚLNIE ZŁOŻONE.\nID = "+str(wyn) )
		finally:
			cur.close()
	
	def ZleceniaButtonP24_clicked_cb(self, button):
		ident = self.ZleceniaComboboxtextP21.get_active_text() # SQL integer
		nr_rej = self.ZleceniaEntryP22.get_text() # SQL text
		faktura = self.ZleceniaComboboxtextP23.get_active_text() # SQL boolean
		
		faktura = True if faktura == "TAK" else False
		
		if not self.modify("", [ AsIs("nr_rej"), nr_rej, int(ident) ], str):
			return
		
		if not self.modify("-", [ AsIs("faktura"), faktura, int(ident) ], bool):
			return
		
		ExtraWindow = Extra()
		ExtraWindow.show_label("ZLECENIE "+str(ident)+" ZOSTAŁO POMYŚLNIE ZMIENIONE.")
	
	def ZleceniaButtonP31_clicked_cb(self, button):
		ident = self.ZleceniaComboboxtextP31.get_active_text() # SQL integer
		
		cur = self.conn.cursor()
		args = [ int(ident) ]
		
		try:
			cur.execute("SELECT id, data_zlec, data_real, nr_rej, faktura, kli_id, sam_model, koszt FROM zlecenia WHERE id = %s", args)
			wyn = cur.fetchone()[:]
		except (psycopg2.Error, TypeError):
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

