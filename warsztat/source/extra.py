# -*- coding: utf-8 -*-
from gi import require_version

require_version('Gtk', '3.0')

from gi.repository import Gtk


class Extra:
    """Klasa odpowiadająca za działanie okna przekazywania dodatkowych informacji."""

    def __init__(self, text):
        """Tworzy nowe okno."""
        extra_builder = Gtk.Builder()
        extra_builder.add_from_file("glade/extra.glade")

        self.__extra_window = extra_builder.get_object("extra_window")
        self.__extra_label = extra_builder.get_object("extra_label")
        self.__extra_button = extra_builder.get_object("extra_button")

        extra_builder.connect_signals(self)

        self.__extra_label.set_label(text)

    def show(self):
        """Wyświetla okno wraz z tekstem."""
        self.__extra_window.show()

    def extra_button_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zatwierdzenia."""
        self.__extra_window.destroy()
