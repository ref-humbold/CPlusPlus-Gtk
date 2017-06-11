# -*- coding: utf-8 -*-
from gi import require_version

require_version('Gtk', '3.0')

from gi.repository import Gtk
from psycopg2 import connect
from re import match
from sprzedawca import Sprzedawca
from mechanik import Mechanik
from magazynier import Magazynier
from extra import Extra


class Login:
    """Klasa odpowiadająca za działanie okna logowania do bazy danych."""

    def __init__(self):
        """Tworzy nowe okno logowania."""
        self.is_logged = False

        login_builder = Gtk.Builder()
        login_builder.add_from_file("login.glade")

        self.__login_window = login_builder.get_object("login_window")

        self.__login_entry_1b = login_builder.get_object("login_entry_1b")
        self.__login_entry_2b = login_builder.get_object("login_entry_2b")
        self.__login_button_3b = login_builder.get_object("login_button_3b")

        login_builder.connect_signals(self)

        self.__login_entry_2b.set_invisible_char("#")
        self.__login_entry_2b.set_visibility(False)

        self.__login_window.show()

    def open_error_window(self, msg):
        """Tworzy nowe okno wyświetlające komunikat o błędzie."""
        self.__login_entry_1b.set_text("")
        self.__login_entry_2b.set_text("")
        Extra(msg).show()

    def login_window_destroy_cb(self, window):
        """Zamyka okno logowania."""
        if not self.is_logged:
            Gtk.main_quit()

    def login_button_3b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku zalogowania do bazy danych."""
        user_login = self.__login_entry_1b.get_text()
        user_password = self.__login_entry_2b.get_text()

        if match(r"^[A-Za-z]*$", user_login) is None \
           or match(r"^[A-Za-z0-9]*$", user_password) is None:
            self.open_error_window("NIEPOPRAWNY LOGIN LUB HASŁO.\nSPRÓBUJ PONOWNIE.")

        try:
            conn = connect(database="warsztat",
                                    user=user_login, password=user_password)
        except:
            self.open_error_window("NIEPOPRAWNY LOGIN LUB HASŁO.\nSPRÓBUJ PONOWNIE.")
            return
        else:
            self.is_logged = True

        args = [user_login]

        try:
            cur = conn.cursor()
            cur.execute(
                'SELECT r2.rolname FROM pg_roles AS r1 JOIN pg_auth_members AS m ON r1.oid = m.member JOIN pg_roles AS r2 ON m.roleid = r2.oid WHERE r1.rolname = %s;', args)
        except:
            conn.rollback()
            cur.close()
            conn.close()
            self.open_error_window("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
            return

        try:
            wyn = cur.fetchone()[0]
        except:
            conn.rollback()
            conn.close()
            self.open_error_window(
                "DOSTĘP DO BAZY JEST ZAMKNIĘTY DLA UŻYTKOWNIKA " + user_login + ".")
            return
        else:
            conn.commit()
            self.__login_window.destroy()
        finally:
            cur.close()

        if wyn == "sprzedawca":
            worker_window = Sprzedawca(conn)
        elif wyn == "mechanik":
            worker_window = Mechanik(conn)
        elif wyn == "magazynier":
            worker_window = Magazynier(conn)
        else:
            conn.close()
            self.open_error_window(
                "DOSTĘP DO BAZY JEST ZAMKNIĘTY DLA UŻYTKOWNIKA " + user_login + ".")
