# -*- coding: utf-8 -*-

from math import cos, tan, radians
import pygame
from .utils import bound
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


class CannonBallGraphic():
    __COLOUR = (0, 0, 0)

    def __init__(self, screen, castle):
        self.__screen = screen
        self.__angle = castle.angle
        self.__start_pos = (None, None)
        self.__current_pos = [None, None]
        self.__speed = castle.speed * 0.75 * abs(cos(radians(self.__angle)))

    def move(self):
        if self.__angle == 90:
            hmax = max(0, self.__start_pos[1] - int(self.__speed * self.__speed / (2 * 9.81)))

            while self.__current_pos[1] > hmax:
                self.__draw()
                self.__current_pos[1] -= 2

            while self.__current_pos[1] + 2 < self.__start_pos[1]:
                self.__current_pos[1] += 2
                self.__draw()
        else:
            while 0 < self.__current_pos[0] < self.__screen.get_size()[0]:
                if self.__current_pos[1] >= 0:
                    self.__draw()

                self.__make_move()

    def __draw(self):
        self.__draw_shape(self.__COLOUR)
        pygame.display.update()
        pygame.time.delay(50)
        self.__draw_shape(HEAVEN_COLOUR)
        pygame.display.update()

    def __draw_shape(self, colour):
        pygame.draw.line(self.__screen, colour,
                         (self.__current_pos[0] - 2, self.__current_pos[1] - 2),
                         (self.__current_pos[0] - 2, self.__current_pos[1] + 2))
        pygame.draw.line(self.__screen, colour,
                         (self.__current_pos[0] - 1, self.__current_pos[1] - 2),
                         (self.__current_pos[0] - 1, self.__current_pos[1] + 2))
        pygame.draw.line(self.__screen, colour,
                         (self.__current_pos[0], self.__current_pos[1] - 2),
                         (self.__current_pos[0], self.__current_pos[1] + 2))
        pygame.draw.line(self.__screen, colour,
                         (self.__current_pos[0] + 1, self.__current_pos[1] - 2),
                         (self.__current_pos[0] + 1, self.__current_pos[1] + 2))

    def __make_move(self):
        dirsign = 1 if self.__angle < 90 else -1
        self.__current_pos[0] += dirsign * 2
        self.__current_pos[1] = self.__parabola(self.__current_pos[0])

    def __parabola(self, x_pos):
        y_diff = x_pos * tan(radians(self.__angle)) \
            - 9.81 * x_pos * x_pos / (2 * self.__speed * self.__speed)

        return self.__start_pos[1] - int(y_diff)
