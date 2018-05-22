# -*- coding: utf-8 -*-

from random import randint
import pygame
from ..utils import bound

HEAVEN_COLOUR = (0, 127, 255)
GROUND_COLOUR = (255, 255, 0)


class Background:
    """Klasa odpowiadająca za grafikę tła gry."""

    def __init__(self, screen):
        self.__screen = screen
        self.__heights = []
        self.__font = pygame.font.SysFont("arial", 24)
        self.__angle_label = self.__render_value("ANGLE: ")
        self.__speed_label = self.__render_value("SPEED: ")

    def draw(self):
        """Rysuje tło do gry."""
        self.__screen.fill(HEAVEN_COLOUR)
        self.__create()

        for x_pos, height in enumerate(self.__heights):
            pygame.draw.line(self.__screen, GROUND_COLOUR, (x_pos, 640), (x_pos, height))

        self.__blit_labels(0, 20)

    def __create(self):
        """Ustawia wysokości na tle."""
        current_height = randint(320, 560)

        for _ in range(0, 1024, 16):
            diff = randint(-4, 4)

            for column in range(1, 17):
                current_height = bound(54, current_height + column * diff, 586)
                self.__heights.append(current_height)

    def __blit_labels(self, angle, speed):
        """Wyświetla etykiety na ekranie
        :param angle: wartość kąta
        :param speed: wartość prędkości"""
        self.__screen.blit(self.__angle_label, (10, 10))
        self.__screen.blit(self.__speed_label, (10, 40))
        self.__screen.blit(self.__render_value(angle), (110, 10))
        self.__screen.blit(self.__render_value(speed), (110, 40))

    def __render_value(self, value):
        return self.__font.render(str(value), 0, (0, 0, 0))
