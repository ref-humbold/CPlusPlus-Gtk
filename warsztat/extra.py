# -*- coding: utf-8 -*-

import gi
from gi.repository import Gtk

class Extra:
    """
    Klasa odpowiadająca za działanie okna przekazywania dodatkowych informacji.
    """
    def __init__(self):
        """
        Tworzy nowe okno.
        """
        ExtraBuilder = Gtk.Builder()
        ExtraBuilder.add_from_file("extra.glade")
        
        self.ExtraWindow = ExtraBuilder.get_object("ExtraWindow")
        self.ExtraLabel = ExtraBuilder.get_object("ExtraLabel")
        self.ExtraButton = ExtraBuilder.get_object("ExtraButton")
        
        ExtraBuilder.connect_signals(self)
        
    def show_label(self, text):
        """
        Wyświetla okno wraz z tekstem.
        """
        self.ExtraLabel1.set_label(text)
        self.ExtraWindow.show()
    
    def ExtraButton_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku zatwierdzenia.
        """
        self.ExtraWindow.destroy()

