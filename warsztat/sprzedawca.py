# -*- coding: utf-8 -*-
from gi import require_version

require_version('Gtk', '3.0')

from gi.repository import Gtk
from klienci import Klienci
from uslugi import Uslugi
from zlecenia import Zlecenia


class Sprzedawca:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy."""

    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        sprzedawca_builder = Gtk.Builder()
        sprzedawca_builder.add_from_file("sprzedawca.glade")

        self.__sprzedawca_window = sprzedawca_builder.get_object("sprzedawca_window")

        self.__sprzedawca_button_1 = sprzedawca_builder.get_object("sprzedawca_button_1")
        self.__sprzedawca_button_2 = sprzedawca_builder.get_object("sprzedawca_button_2")
        self.__sprzedawca_button_3 = sprzedawca_builder.get_object("sprzedawca_button_3")

        sprzedawca_builder.connect_signals(self)

        self.__sprzedawca_window.show()

    def sprzedawca_window_destroy_cb(self, window):
        """Zamyka okno sprzedawcy."""
        self.conn.close()
        Gtk.main_quit()

    def sprzedawca_button_1_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zarządania zleceniami."""
        zlecenia_window = Zlecenia(self.conn)

    def sprzedawca_button_2_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zarządania klientami."""
        klienci_window = Klienci(self.conn)

    def sprzedawca_button_3_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zarządania usługami."""
        uslugi_window = Uslugi(self.conn)
