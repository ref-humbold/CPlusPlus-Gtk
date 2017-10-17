# -*- coding: utf-8 -*-

from math import pi, sin, cos, tan
import pygame


class Castle:
    __CANNON = pygame.image.load("images/armata.jpg").convert_alpha()

    def __init__(self, x_pos, y_pos):
        self.position = (x_pos, y_pos)
        self.actual = False
        self.speed = 20.0
        self.angle = 0.0
        self.life = 100
        self.cannon_pos = (x_pos + 11, y_pos + 7)
        self.cannon_img = self.__CANNON

    def change_speed(self, diff):
        """Zmienia prędkość wylotową pocisku z zamku.
        :param diff: zmiana prędkości"""
        self.speed = self.__intervalize(20.0, self.speed + diff, 3.0 * self.life + 100.0)

    def change_angle(self, diff):
        """Zmienia kąt armaty z zamku.
        :param diff: zmiana kąta"""
        self.angle = self.__intervalize(0.0, self.angle + diff, 180.0)
        self.__cannon_img = pygame.transform.rotate(self.__CANNON, self.angle)
        rads = self.angle * pi / 180.0

        if self.angle <= 90.0:
            self.cannon_pos = (self.cannon_pos[0], int(self.cannon_pos[1] - 6 * sin(rads)))
        else:
            self.cannon_pos = (int(self.cannon_pos[0] + 6.0 * cos(rads)),
                               int(self.cannon_pos[1] - 6.0 * sin(rads)))

    def __intervalize(self, minim, elem, maxim):
        return minim if elem < minim else maxim if elem > maxim else elem
