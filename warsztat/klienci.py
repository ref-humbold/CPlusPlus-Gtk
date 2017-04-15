# -*- coding: utf-8 -*-
from psycopg2.extensions import AsIs
from gi.repository import Gtk
from extra import Extra

class Klienci:
    """Klasa odpowiadająca za działanie okna interakcji sprzedawcy z tabelą klientów."""
    def __init__(self, conndb):
        """Tworzy nowe okno z połączeniem z bazą danych."""
        self.conn = conndb

        KlienciBuilder = Gtk.Builder()
        KlienciBuilder.add_from_file("klienci.glade")

        self.KlienciWindow = KlienciBuilder.get_object("KlienciWindow")

        self.KlienciEntry11b = KlienciBuilder.get_object("KlienciEntry11b")
        self.KlienciEntry12b = KlienciBuilder.get_object("KlienciEntry12b")
        self.KlienciEntry13b = KlienciBuilder.get_object("KlienciEntry13b")
        self.KlienciEntry14b = KlienciBuilder.get_object("KlienciEntry14b")
        self.KlienciComboboxtext15b = KlienciBuilder.get_object("KlienciComboboxtext15b")
        self.KlienciButton16b = KlienciBuilder.get_object("KlienciButton16b")

        self.KlienciComboboxtext21b = KlienciBuilder.get_object("KlienciComboboxtext21b")
        self.KlienciEntry22b = KlienciBuilder.get_object("KlienciEntry22b")
        self.KlienciEntry23b = KlienciBuilder.get_object("KlienciEntry23b")
        self.KlienciEntry24b = KlienciBuilder.get_object("KlienciEntry24b")
        self.KlienciEntry25b = KlienciBuilder.get_object("KlienciEntry25b")
        self.KlienciComboboxtext26b = KlienciBuilder.get_object("KlienciComboboxtext26b")
        self.KlienciButton27b = KlienciBuilder.get_object("KlienciButton27b")

        self.KlienciComboboxtext31b = KlienciBuilder.get_object("KlienciComboboxtext31b")
        self.KlienciEntry32b = KlienciBuilder.get_object("KlienciEntry32b")
        self.KlienciEntry33b = KlienciBuilder.get_object("KlienciEntry33b")
        self.KlienciEntry34b = KlienciBuilder.get_object("KlienciEntry34b")
        self.KlienciButton35b = KlienciBuilder.get_object("KlienciButton35b")

        self.KlienciComboboxtext31b.append_text("-")
        self.__load_ids(self.KlienciComboboxtext21b)
        self.__load_ids(self.KlienciComboboxtext31b)

        KlienciBuilder.connect_signals(self)

        self.KlienciWindow.show()

    def __load_ids(self, comboboxtext):
        """Ładuje identyfikatory (klucze główne) z tabeli klientów do zadanego pola wyboru."""
        cur = self.conn.cursor()
        cur.execute("SELECT id FROM klienci;")
        idents = cur.fetchall()
        self.conn.commit()
        cur.close()

        for s in [str(i[0]) for i in idents]:
            comboboxtext.append_text(s)

        comboboxtext.set_active(0)

    def __modify(self, cur, nonstr, fieldname, args, convtype):
        """Dokonuje modyfikacji wybranej kolumny tabeli klientów."""
        if args[0] != nonstr:
            args[0] = convtype(args[0])

            try:
                if fieldname == "imie":
                    cur.execute("UPDATE klienci SET imie = %s WHERE id = %s;", args)
                elif fieldname == "nazwisko":
                    cur.execute("UPDATE klienci SET nazwisko = %s WHERE id = %s;", args)
                elif fieldname == "telefon":
                    cur.execute("UPDATE klienci SET telefon = %s WHERE id = %s;", args)
                elif fieldname == "firma":
                    cur.execute("UPDATE klienci SET firma = %s WHERE id = %s;", args)
                elif fieldname == "rabat":
                    cur.execute("UPDATE klienci SET rabat = %s WHERE id = %s;", args)
            except:
                self.conn.rollback()
                cur.close()
                ExtraWindow = Extra()
                ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                return False

        return True

    def KlienciButton16b_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku dodania nowego klienta.
        """
        imie = self.KlienciEntry11b.get_text() # SQL text
        nazwisko = self.KlienciEntry12b.get_text() # SQL text
        telefon = self.KlienciEntry13b.get_text() # SQL integer
        firma = self.KlienciEntry14b.get_text() # SQL text
        rabat = self.KlienciComboboxtext15b.get_active_text() # SQL integer

        args = [ None if i == "" else i for i in [imie, nazwisko, telefon, firma] ]+[ int(rabat) ]
        args[2] = None if args[2] == None else int(args[2])

        try:
            cur = self.conn.cursor()
            cur.execute("INSERT INTO klienci(imie, nazwisko, telefon, firma, rabat) VALUES (%s, %s, %s, %s, %s);", args)
            cur.execute("SELECT max(id) FROM klienci;")
            wynid = cur.fetchone()[0]
        except:
            self.conn.rollback()
            cur.close()
            ExtraWindow = Extra()
            ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
        else:
            self.conn.commit()
            self.KlienciComboboxtext21b.append_text(str(wynid))
            self.KlienciComboboxtext31b.append_text(str(wynid))
            ExtraWindow = Extra()
            ExtraWindow.show_label("NOWY KLIENT ZOSTAŁ POMYŚLNIE DODANY.\nID = "+str(wynid))
        finally:
            cur.close()

    def KlienciButton27b_clicked_cb(self, button):
        """
        Reaguje na kliknięcie przycisku modyfikacji danych klienta.
        """
        ident = self.KlienciComboboxtext21b.get_active_text() # SQL integer
        imie = self.KlienciEntry22b.get_text() # SQL text
        nazwisko = self.KlienciEntry23b.get_text() # SQL text
        telefon = self.KlienciEntry24b.get_text() # SQL integer
        firma = self.KlienciEntry25b.get_text() # SQL text
        rabat = self.KlienciComboboxtext26b.get_active_text() # SQL integer

        cur = self.conn.cursor()

        if not self.__modify(cur, "", "imie", [ imie, int(ident) ], str):
            return

        if not self.__modify(cur, "", "nazwisko", [ nazwisko, int(ident) ], str):
            return

        if not self.__modify(cur, "", "telefon", [ telefon, int(ident) ], int):
            return

        if not self.__modify(cur, "", "firma", [ firma, int(ident) ], str):
            return

        if not self.__modify(cur, "-", "rabat", [ rabat, int(ident) ], int):
            return

        self.conn.commit()
        cur.close()
        ExtraWindow = Extra()
        ExtraWindow.show_label("DANE KLIENTA NUMER "+str(ident)+" ZOSTAŁY POMYŚLNIE ZMIENIONE.")

    def KlienciButton35b_clicked_cb(self, button):
        """Reaguje na kliknięcie przycisku wyszukania klienta."""
        ident = self.KlienciComboboxtext31b.get_active_text() # SQL integer
        imie = self.KlienciEntry32b.get_text() # SQL text
        nazwisko = self.KlienciEntry33b.get_text() # SQL text
        telefon = self.KlienciEntry34b.get_text() # SQL integer

        cur = self.conn.cursor()

        if ident != "-":
            args = [int(ident)]

            try:
                cur.execute("SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE id = %s;", args)
                wyn = cur.fetchone()[:]
            except:
                self.conn.rollback()
                ExtraWindow = Extra()
                ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                return
            else:
                self.conn.commit()
                ExtraWindow = Extra()
                ExtraWindow.show_label(", ".join(map(str, wyn)))
            finally:
                cur.close()
        else:
            args = ["%"+str(i)+"%" for i in [imie, nazwisko, telefon]]

            try:
                cur.execute("SELECT id, imie, nazwisko, telefon, firma, rabat FROM klienci WHERE imie LIKE %s AND nazwisko LIKE %s AND CAST(telefon AS text) LIKE %s;", args)
                wyn = cur.fetchall()[:]
            except:
                self.conn.rollback()
                ExtraWindow = Extra()
                ExtraWindow.show_label("WYSTĄPIŁ BŁĄD WEWNĘTRZNY BAZY. PRZERWANO.")
                return
            else:
                self.conn.commit()
                res = map(lambda x: ", ".join(map(str, x)), wyn)
                out_str = "BRAK WYNIKÓW!" if wyn == [] else "\n".join(res)
                ExtraWindow = Extra()
                ExtraWindow.show_label(out_str)
            finally:
                cur.close()

