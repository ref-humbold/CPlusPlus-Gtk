# -*- coding: utf-8 -*-

from abc import ABCMeta
import dbm.ndbm
import pygame
from .castle import Castle


class Player(metaclass=ABCMeta):
    """Klasa odpowiadająca za pojedynczego gracza"""
    _MARKER_COLOUR = None

    def __init__(self, number, image, graphic):
        """Tworzy nowego gracza.
        :param number: numer gracza
        :param image: ściezka do pliku obrazka zamku"""
        self.number = str(number)
        self.castles = []
        self.castle_img = pygame.image.load(image).convert()
        self._graphic = graphic
