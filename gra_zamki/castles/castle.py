# -*- coding: utf-8 -*-

from .cannon import Cannon
from .utils import bound


class Castle:
    __CANNON_POS = [11, 7]

    def __init__(self, x_pos, y_pos):
        self.position = (x_pos, y_pos)
        self.actual = False
        self.life = 100
        self.speed = 20.0
        self.cannon = Cannon(self.position)

    @property
    def angle(self):
        return self.cannon.angle

    def change_speed(self, diff):
        """Zmienia prędkość wylotową pocisku z zamku.
        :param diff: zmiana prędkości"""
        self.speed = bound(20.0, self.speed + diff, 3.0 * self.life + 100.0)

    def change_angle(self, diff):
        """Zmienia kąt armaty w zamku.
        :param diff: zmiana kąta"""
        self.cannon.change_angle(diff)
