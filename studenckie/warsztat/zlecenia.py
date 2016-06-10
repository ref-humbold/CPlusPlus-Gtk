# -*- coding: utf-8 -*-

import gi
import psycopg2
from gi.repository import Gtk
from extra import *

class Zlecenia:
	def __init__(self, conndb):
		self.conn = conndb
		
		ZleceniaBuilder = Gtk.Builder()
		ZleceniaBuilder.add_from_file("zlecenia.glade")
		
		self.ZleceniaWindow = ZleceniaBuilder.get_object("ZleceniaWindow")
		
		self.ZleceniaEntryP11 = UslugiBuilder.get_object("ZleceniaEntryP11")
		self.ZleceniaComboboxtextP12 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP12")
		self.ZleceniaEntryP13 = UslugiBuilder.get_object("ZleceniaEntryP13")
		self.ZleceniaComboboxtextP14 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP14")
		self.ZleceniaComboboxtextP15 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP15")
		self.ZleceniaButtonP16 = ZleceniaBuilder.get_object("ZleceniaButtonP16")
		
		self.ZleceniaComboboxtextP21 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP21")
		self.ZleceniaEntryP22 = UslugiBuilder.get_object("ZleceniaEntryP22")
		self.ZleceniaComboboxtextP23 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP23")
		self.ZleceniaEntryP24 = UslugiBuilder.get_object("ZleceniaEntryP24")
		self.ZleceniaButtonP25 = ZleceniaBuilder.get_object("ZleceniaButtonP25")
		
		self.ZleceniaComboboxtextP31 = ZleceniaBuilder.get_object("ZleceniaComboboxtextP31")
		self.ZleceniaButtonP31 = ZleceniaBuilder.get_object("ZleceniaButtonP31")
		
		ZleceniaBuilder.connect_signals(self)
		
		self.ZleceniaWindow.show()
	
	def ZleceniaButtonP16_clicked_cb(self, button):
		ExtraWindow = Extra()
		ExtraWindow.show_label("ZLECENIE ZOSTAŁO POMYŚLNIE ZŁOŻONE.")
	
	def ZleceniaButtonP25_clicked_cb(self, button):
		ExtraWindow = Extra()
		ExtraWindow.show_label("ZLECENIE ZOSTAŁO POMYŚLNIE ZMIENIONE.")
	
	def ZleceniaButtonP31_clicked_cb(self, button):
		pass

