# -*- coding: utf-8 -*-

from random import randint
import pygame


class Graphics:
    """Klasa odpowiadająca za grafikę gry."""
    __HEAVEN_COLOUR = (0, 127, 255)
    __GROUND_COLOUR = (255, 255, 0)
    __CANNONBALL_COLOUR = (0, 0, 0)

    def __init__(self):
        self.__background = []
        self.__screen = pygame.display.set_mode((1024, 640))
        self.__font = pygame.font.SysFont("arial", 24)
        self.__angle_label = self.__render_value("ANGLE: ")
        self.__speed_label = self.__render_value("SPEED: ")
        pygame.display.set_caption("GRA W ZAMKI")

    def draw_background(self):
        """Tworzy tło do gry."""
        self.__screen.fill(self.__HEAVEN_COLOUR)
        self.__set_background()
        self.__arrange_castles()

        for x_pos, height in enumerate(self.__background):
            pygame.draw.line(self.__screen, self.__GROUND_COLOUR, (x_pos, 640), (x_pos, height))

        self.__blit_names(0, 20)
        self.__draw_castles()

        self.list_players[0].draw_castle_sign(self.act_castle[0])

        for player in self.list_players:
            player.draw_castle_sign(self.act_castle[0], (48, 48, 48))

    def move_marker(self, old_castle_pos, new_castle_pos, colour):
        self.__draw_marker(old_castle_pos[0], old_castle_pos[1], self.__GROUND_COLOUR)
        self.__draw_marker(new_castle_pos[0], new_castle_pos[1], colour)

    def draw_shoot(self):
        pass

    def move_cannon(self, castle_img, castle_pos, cannon_img, cannon_pos):
        self.__screen.blit(castle_img, castle_pos)
        self.__screen.blit(cannon_img, cannon_pos)
        pygame.display.update()

    def __set_background(self):
        """Ustawia faktyczne tło gry."""
        y_pos = randint(320, 560)

        for _ in range(0, 1024, 16):
            diff = randint(-1, 1) * randint(1, 4)

            for column in range(16):
                height = self.__intervalize(54, y_pos + column * diff, 586)
                self.__background.append(height)

            y_pos = self.__intervalize(54, y_pos + 16 * diff, 586)

    def __arrange_castles(self):
        """Dopasowuje planszę do umiejscowienia zamków."""
        for i, player in enumerate(self.list_players):
            for j in range(3):
                pos = randint(10, 1013)

                while any([h[0] - 40 <= pos <= h[0] + 40 for cp in self.castle_pos for h in cp]):
                    pos = randint(10, 1013)

                level = min(self.__background[pos - 10:pos + 11])
                self.__background[pos - 10:pos + 11] = [level] * 21
                self.castle_pos[i].append((pos - 10, level - 10))
                player.add_castles(self.castle_imgs[i], (pos - 10, level - 10))

    def __draw_castles(self):
        """Ustawia obrazki zamków na planszy."""
        castles = [[] for _ in range(len(self.list_players))]

        for i, cst in enumerate(castles):
            for j in cst:
                self.__screen.blit(self.castle_imgs[i], j)
                cannon, cannon_pos = self.list_players[i].make_armat(j)
                self.__screen.blit(cannon, cannon_pos)

    def __draw_cannonball(self, x_pos, y_pos, colour):
        """Rysuje kształt kuli armatniej.
        :param x_pos: współrzędna x środka kuli
        :param y_pos: współrzędna y środka kuli
        :param colour: kolor rysunku"""
        pygame.draw.line(self.__screen, colour, (x_pos - 2, y_pos - 2), (x_pos - 2, y_pos + 2))
        pygame.draw.line(self.__screen, colour, (x_pos - 1, y_pos - 2), (x_pos - 1, y_pos + 2))
        pygame.draw.line(self.__screen, colour, (x_pos, y_pos - 2), (x_pos, y_pos + 2))
        pygame.draw.line(self.__screen, colour, (x_pos + 1, y_pos - 2), (x_pos + 1, y_pos + 2))

    def __draw_marker(self, x_pos, y_pos, colour):
        """Rysuje kształt znacznika.
        :param x_pos: współrzędna x zamku gracza
        :param y_pos: współrzędna y zamku gracza
        :param colour: kolor znacznika"""
        x_pos += 10
        y_pos += 24

        for diff in range(7):
            pygame.draw.line(self.__screen, colour, (x_pos + diff, y_pos + 6),
                             (x_pos + diff, y_pos + diff))
            pygame.draw.line(self.__screen, colour, (x_pos - diff, y_pos + 6),
                             (x_pos - diff, y_pos + diff))

    def __blit_names(self, angle, speed):
        """Wyświetla napisy na ekranie
        :param angle: wartość kąta
        :param speed: wartość prędkości"""
        self.__screen.blit(self.__angle_label, (10, 10))
        self.__screen.blit(self.__speed_label, (10, 40))
        self.__screen.blit(self.__render_value(angle), (110, 10))
        self.__screen.blit(self.__render_value(speed), (110, 40))

    def __render_value(self, value):
        return self.__font.render(str(value), 0, (0, 0, 0))

    def __intervalize(self, minim, elem, maxim):
        return minim if elem < minim else maxim if elem > maxim else elem
