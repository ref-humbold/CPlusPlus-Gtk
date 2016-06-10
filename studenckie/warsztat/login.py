# -*- coding: utf-8 -*-

import gi
import re
import psycopg2
from gi.repository import Gtk
from extra import *

class Login:
	def __init__(self):
		LoginBuilder = Gtk.Builder()
		LoginBuilder.add_from_file("login.glade")
		
		self.LoginWindow = LoginBuilder.get_object("LoginWindow")
		
		self.LoginEntry21 = LoginBuilder.get_object("LoginEntry21")
		self.LoginEntry22 = LoginBuilder.get_object("LoginEntry22")
		self.LoginButton23 = LoginBuilder.get_object("LoginButton23")
		
		LoginBuilder.connect_signals(self)
		
		self.LoginEntry22.set_invisible_char("#")
		self.LoginEntry22.set_visibility(False)
		
		self.LoginWindow.show()
	
	def open_error_window(self):
		pass
	
	def LoginButton23_clicked_cb(self, button):
		pass

