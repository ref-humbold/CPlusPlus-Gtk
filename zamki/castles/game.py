# -*- coding: utf-8 -*-

import pygame


class Game:
    def __init__(self):
        pygame.init()
        self.__screen = pygame.display.set_mode((1024, 640))
        pygame.display.set_caption("GRA W ZAMKI")

    @property
    def screen(self):
        return self.__screen
