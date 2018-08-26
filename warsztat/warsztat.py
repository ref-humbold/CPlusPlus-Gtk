#! /bin/python3
# -*- coding: utf-8 -*-
from gi import require_version

require_version("Gtk", "3.0")

from gi.repository import Gtk
from .source.login import Login

login = Login()
Gtk.main()
