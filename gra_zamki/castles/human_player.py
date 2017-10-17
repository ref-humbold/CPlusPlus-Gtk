# -*- coding: utf-8 -*-

from .player import Player


class HumanPlayer(Player):
    _MARKER_COLOUR = (128, 128, 128)

    def __init__(self, number, image, graphic):
        super().__init__(number, image, graphic)
