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
	
	def KlienciButtonP16_clicked_cb(self, button):
		pass
	
	def KlienciButtonP27_clicked_cb(self, button):
		pass
	
	def KlienciButtonP35_clicked_cb(self, button):
		pass

