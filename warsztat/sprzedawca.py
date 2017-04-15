# -*- coding: utf-8 -*-

from gi.repository import Gtk
from extra import Extra
from klienci import Klienci
from uslugi import Uslugi
from zlecenia import Zlecenia

class Sprzedawca:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy."""
    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        SprzBuilder = Gtk.Builder()
        SprzBuilder.add_from_file("sprzedawca.glade")

        self.SprzWindow = SprzBuilder.get_object("SprzWindow")

        self.SprzButton1a = SprzBuilder.get_object("SprzButton1a")
        self.SprzButton2a = SprzBuilder.get_object("SprzButton2a")
        self.SprzButton3a = SprzBuilder.get_object("SprzButton3a")

        SprzBuilder.connect_signals(self)

        self.SprzWindow.show()

    def SprzWindow_destroy_cb(self, window):
        """Zamyka okno sprzedawcy."""
        self.conn.close()
        Gtk.main_quit()

    def SprzButton1a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zarządania zleceniami."""
        ZleceniaWindow = Zlecenia(self.conn)

    def SprzButton2a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zarządania klientami."""
        KlienciWindow = Klienci(self.conn)

    def SprzButton3a_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zarządania usługami."""
        UslugiWindow = Uslugi(self.conn)

