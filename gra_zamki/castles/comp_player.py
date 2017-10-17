# -*- coding: utf-8 -*-

from .player import Player


class CompPlayer(Player):
    _MARKER_COLOUR = (48, 48, 48)

    def __init__(self, number, image, graphic):
        super().__init__(number, image, graphic)
