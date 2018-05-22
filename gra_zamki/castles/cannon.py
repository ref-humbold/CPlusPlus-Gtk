# -*- coding: utf-8 -*-

from math import cos
import pygame
from .utils import bound, radians
from .graphics import HEAVEN_COLOUR


class Cannon():
    __IMAGE = pygame.image.load("images/armata.jpg").convert_alpha()

    def __init__(self, position):
        self.__image = self.__IMAGE
        self.position = (position[0] + 11, position[1] + 7)
        self.angle = 0.0

    @property
    def size(self):
        return self.__image.get_size()

    def change_angle(self, diff):
        """Zmienia kąt armaty w zamku.
        :param diff: zmiana kąta"""
        self.angle = bound(0.0, self.angle + diff, 180.0)
        self.__image = pygame.transform.rotate(self.__IMAGE, self.angle)


class CannonBall():
    __COLOUR = (0, 0, 0)

    def __init__(self, screen, castle):
        self.__screen = screen
        self.__pos = [None, None]
        self.__speed_x = castle.speed * 0.75 * abs(cos(radians(castle.angle)))

    def draw(self):
        """Rysuje kształt kuli armatniej."""
        self.__draw_shape(self.__COLOUR)

    def erase(self):
        """Usuwa narysowany kształt kuli armatniej."""
        self.__draw_shape(HEAVEN_COLOUR)

    def __draw_shape(self, colour):
        pygame.draw.line(self.__screen, colour,
                         (self.__pos[0] - 2, self.__pos[1] - 2),
                         (self.__pos[0] - 2, self.__pos[1] + 2))
        pygame.draw.line(self.__screen, colour,
                         (self.__pos[0] - 1, self.__pos[1] - 2),
                         (self.__pos[0] - 1, self.__pos[1] + 2))
        pygame.draw.line(self.__screen, colour,
                         (self.__pos[0], self.__pos[1] - 2),
                         (self.__pos[0], self.__pos[1] + 2))
        pygame.draw.line(self.__screen, colour,
                         (self.__pos[0] + 1, self.__pos[1] - 2),
                         (self.__pos[0] + 1, self.__pos[1] + 2))
