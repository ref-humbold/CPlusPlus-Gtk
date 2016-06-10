# -*- coding: utf-8 -*-

import gi
import psycopg2
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
		
		MechBuilder.connect_signals(self)
		
		self.MechWindow.show()
	
	def MechButtonP11_clicked_cb(self, button):
		pass
	
	def MechButtonP21_clicked_cb(self, button):
		pass
	
	def MechButtonP33_clicked_cb(self, button):
		pass

