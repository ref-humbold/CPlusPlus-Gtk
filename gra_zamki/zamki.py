#! /bin/python3
# -*- coding: utf-8 -*-

import pygame
from pygame.locals import *
import dbm.ndbm
import threading
from os import _exit
from random import randint, choice
from math import pi, sqrt, sin, cos, tan

def intervalize(a, x, b):
    return a if x < a else b if x > b else x

class Game:
    """Klasa odpowiadająca za interfejs gry"""

    def __init__(self):
        """Konstruktor gry"""
        pygame.init()
        self.screen = pygame.display.set_mode((1024, 640))
        self.font = pygame.font.SysFont("arial", 24)
        self.angle_label = self.font.render("ANGLE: ", 0, (0, 0, 0))
        self.speed_label = self.font.render("SPEED: ", 0, (0, 0, 0))
        self.text_angle = self.render_value(0)
        self.text_speed = self.render_value(20)
        self.playing = 0
        self.human_won = True
        self.nr_players = 4
        self.background = []
        self.list_players = [Player(self, 0)] + [Bot(self, i) for i in range(1, self.nr_players)]
        self.act_castle = [0] * self.nr_players
        self.semphs = [threading.Semaphore(0) for i in range(self.nr_players)]
        pygame.display.set_caption("GRA W ZAMKI")

    def draw_background(self):
        """Tworzy tło do gry"""
        self.background = []
        self.screen.fill((0, 127, 255))
        castle_pos = [[] for _ in range(len(self.list_players))]
        y = randint(320, 560)

        for x in range(0, 1024, 16):
            d = (randint(0, 2) - 1) * randint(1, 4)

            for r in range(16):
                q = intervalize(54, y + r * d, 586)
                self.background.append([q, ()])

            y = intervalize(54, y + 16 * d, 586)

        castle_imgs = [pygame.image.load("castles/images/zamek_bronze.jpg").convert(),
                       pygame.image.load("castles/images/zamek_green.jpg").convert(),
                       pygame.image.load("castles/images/zamek_red.jpg").convert(),
                       pygame.image.load("castles/images/zamek_violet.jpg").convert()]

        for i, ply in enumerate(self.list_players):
            for j in range(3):
                pos = randint(10, 1013)

                while any([h[0] - 40 <= pos <= h[0] + 40 for g in castle_pos for h in g]):
                    pos = randint(10, 1013)

                z = min(self.background[pos - 10:pos + 11])[0]
                self.background[pos - 10:pos + 11] = [[z, (i, j)] for g in range(21)]
                castle_pos[i].append((pos - 10, z - 10))
                ply.add_castles(castle_imgs[i], (pos - 10, z - 10))

        for x, height in enumerate(self.background):
            pygame.draw.line(self.screen, (255, 255, 0), (x, 640), (x, height[0]))

        for i, cst in enumerate(castle_pos):
            for j in cst:
                self.screen.blit(castle_imgs[i], j)
                armata, arm_pos = self.list_players[i].make_armat(j)
                self.screen.blit(armata, arm_pos)

        self.blit_names()
        self.list_players[0].draw_castle_sign(self.act_castle[0])

        for i in self.list_players[1:]:
            i.draw_castle_sign(self.act_castle[0], (48, 48, 48))

    def modify_after_shot(self, K):
        if K and (not self.list_players[K[0]].castle_pos):
            self.list_players[K[0]] = None

        if all([i is None for i in self.list_players[1:]]):
            self.playing = -1
            self.human_won = True
            return

        self.playing = (self.playing + 1) % self.nr_players

        while not self.list_players[self.playing]:
            self.playing = (self.playing + 1) % self.nr_players

    def blit_names(self):
        self.screen.blit(self.angle_label, (10, 10))
        self.screen.blit(self.speed_label, (10, 40))
        self.screen.blit(self.text_angle, (110, 10))
        self.screen.blit(self.text_speed, (110, 40))

    def render_value(self, val):
        return self.font.render(str(val), 0, (0, 0, 0))

    def play(self):
        """Uruchamia grę i pozwala grać"""
        self.draw_background()
        self.playing = 0
        self.human_won = True

        for i in self.list_players[1:]:
            i.start()

        pygame.display.update()
        can_release = False

        while self.playing >= 0:
            pygame.display.update()
            P = self.list_players[self.playing]

            if self.playing > 0:
                pygame.time.delay(400)
                self.semphs[self.playing].release()
                self.semphs[0].acquire()
                self.blit_names()
            else:
                for event in pygame.event.get():
                    pygame.display.update()

                    if event.type == pygame.QUIT:
                        self.playing = -1
                        human_won = False
                        break

                    if event.type == pygame.MOUSEBUTTONDOWN:
                        x, y = pygame.mouse.get_pos()
                        castle_mouse = [(i, j) for i in range(len(self.list_players)) for j in range(len(self.list_players[i].castle_pos)) if self.list_players[i].castle_pos[j][0] - 5 <= x <= self.list_players[i].castle_pos[j][0] + 26 and self.list_players[i].castle_pos[j][1] - 5 <= y <= self.list_players[i].castle_pos[j][1] + 21]
                        if castle_mouse:
                            p, c = castle_mouse[0]
                            print("ZAMEK NUMER", c, "GRACZA", p, ":")
                            print("\tPOZYCJA NA PLANSZY:", self.list_players[p].castle_pos[c])
                            print("\tDOSTĘPNE ŻYCIE  = ", self.list_players[p].life[c])
                            print("\tMAKSYMALNA DOSTĘPNA PRĘDKOŚĆ POCISKU  = ",
                                  3 * self.list_players[p].life[c] + 100)
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_SPACE:
                            K = P.shoot(self.act_castle[self.playing])
                            self.modify_after_shot(K)
                            can_release = True
                            self.blit_names()
                            break
                        elif event.key == pygame.K_TAB:
                            P.erase_castle_sign(self.act_castle[self.playing])
                            self.act_castle[self.playing] = (
                                self.act_castle[self.playing] + 1) % len(P.castle_pos)
                            P.draw_castle_sign(self.act_castle[self.playing])
                            self.text_angle = self.render_value(
                                P.angles[self.act_castle[self.playing]])
                            self.text_speed = self.render_value(
                                P.speeds[self.act_castle[self.playing]])

                            for x in range(110, 160):
                                pygame.draw.line(self.screen, (0, 127, 255), (x, 80), (x, 0))

                            self.blit_names()
                        elif event.key == pygame.K_UP:
                            P.change_speed(self.act_castle[self.playing], 10)

                            for x in range(110, 160):
                                pygame.draw.line(self.screen, (0, 127, 255), (x, 80), (x, 40))

                            self.text_speed = self.render_value(
                                P.speeds[self.act_castle[self.playing]])
                            self.screen.blit(self.text_speed, (110, 40))
                        elif event.key == pygame.K_DOWN:
                            P.change_speed(self.act_castle[self.playing], -10)

                            for x in range(110, 160):
                                pygame.draw.line(self.screen, (0, 127, 255), (x, 80), (x, 40))

                            self.text_speed = self.render_value(
                                P.speeds[self.act_castle[self.playing]])
                            self.screen.blit(self.text_speed, (110, 40))
                        elif event.key == pygame.K_LEFT:
                            P.change_angle(self.act_castle[self.playing], 5)

                            for x in range(110, 160):
                                pygame.draw.line(self.screen, (0, 127, 255), (x, 40), (x, 0))

                            self.text_angle = self.render_value(
                                P.angles[self.act_castle[self.playing]])
                            self.screen.blit(self.text_angle, (110, 10))
                        elif event.key == pygame.K_RIGHT:
                            P.change_angle(self.act_castle[self.playing], -5)

                            for x in range(110, 160):
                                pygame.draw.line(self.screen, (0, 127, 255), (x, 40), (x, 0))

                            self.text_angle = self.render_value(
                                P.angles[self.act_castle[self.playing]])
                            self.screen.blit(self.text_angle, (110, 10))

        end_font = pygame.font.SysFont("arial", 60)
        endtxt = end_font.render("KONIEC GRY", 0, (0, 0, 0), (255, 255, 255))
        wintxt = end_font.render("WYGRANA", 0, (0, 0, 0), (255, 255, 255)) if human_won and self.list_players[self.playing].castle_pos else end_font.render(
            "PRZEGRANA", 0, (0, 0, 0), (255, 255, 255))
        self.screen.blit(endtxt, (350, 200))
        self.screen.blit(wintxt, (350, 300))
        pygame.display.update()
        pygame.time.delay(1000)
        _exit(0)


class Player:
    """Klasa odpowiadająca za pojedynczego gracza"""

    def __init__(self, g, nr):
        """Tworzy nowego gracza
        :param g: referencja do klasy gry
        :param nr: numer gracza"""
        db = dbm.ndbm.open("players", "c")
        self.game = g
        self.numer = str(nr)
        self.speeds = [20] * 3
        self.angles = [0] * 3
        self.life = [100] * 3
        self.castle_pos = []
        self.armat_pos = []
        self.all_armats = []
        self.was_hit = False
        db[self.numer] = "_@_".join([repr(self.life), repr(self.castle_pos)])
        db.close()

    def add_castles(self, img, pos):
        """
        Dodaje zamek dla gracza
        :param img: obrazek zamku
        :param pos: pozycja zamku na planszy
        """
        self.castle_img = img
        self.castle_pos.append(pos)
        db = dbm.ndbm.open("players", "c")
        db[self.numer] = "_@_".join([repr(self.life), repr(self.castle_pos)])
        db.close()

    def make_armat(self, cpos):
        """Tworzy obraz armaty dla zamku
        :param cpos: pozycja zamku gracza"""
        img = pygame.image.load("castles/images/armata.jpg").convert_alpha()
        pos = (cpos[0] + 11, cpos[1] + 7)
        self.armat_img = img
        self.armat_pos.append(pos)
        self.all_armats.append((img, pos))
        return img, pos

    def change_speed(self, castle, diff):
        """Zmienia prędkość wylotową pocisku z zamku
        :param castle: numer zamku gracza
        :param diff: zmiana prędkości"""
        max_sp = 3 * self.life[castle] + 100
        self.speeds[castle] = intervalize(20, self.speeds[castle] + diff, max_sp)

    def change_angle(self, castle, diff):
        """Zmienia kąt armaty z zamku
        :param castle: numer zamku gracza
        :param diff: zmiana kąta"""
        if self.angles[castle] + diff > 180:
            self.angles[castle] = 180
        elif self.angles[castle] + diff < 0:
            self.angles[castle] = 0
        else:
            self.angles[castle] = self.angles[castle] + diff
            rads = self.angles[castle] * pi / 180
            new_arm_img = pygame.transform.rotate(self.armat_img, self.angles[castle])
            new_arm_pos = (self.armat_pos[castle][0], int(self.armat_pos[castle][1] - 6 * sin(rads))) if self.angles[castle] <= 90 else (int(self.armat_pos[castle][0] + 6 * cos(rads)), int(self.armat_pos[castle][1] - 6 * sin(rads)))
            self.all_armats[castle] = (new_arm_img, new_arm_pos)
            self.game.screen.blit(self.castle_img, self.castle_pos[castle])
            self.game.screen.blit(new_arm_img, new_arm_pos)
            pygame.display.update()

    def draw_castle_sign(self, castle, farbe=(128, 128, 128)):
        """Rysuje znacznik pod aktualnie używanym zamkiem gracza
        :param castle: numer zamku gracza
        :param farbe: kolor znacznika"""
        x = self.castle_pos[castle][0] + 10
        y = self.castle_pos[castle][1] + 24

        for d in range(7):
            pygame.draw.line(self.game.screen, farbe, (x + d, y + 6), (x + d, y + d))
            pygame.draw.line(self.game.screen, farbe, (x - d, y + 6), (x - d, y + d))

    def erase_castle_sign(self, castle):
        """Usuwa znacznik pod zamkiem gracza
        :param castle: numer zamku gracza"""
        x = self.castle_pos[castle][0] + 10
        y = self.castle_pos[castle][1] + 24

        for d in range(7):
            pygame.draw.line(self.game.screen, (255, 255, 0), (x + d, y + 6), (x + d, y + d))
            pygame.draw.line(self.game.screen, (255, 255, 0), (x - d, y + 6), (x - d, y + d))

    def draw_bullet(self, x, y):
        """Rysuje kulę armatnią
        :param x: współrzędna x środka kuli
        :param y: współrzędna y środka kuli"""
        pygame.draw.line(self.game.screen, (0, 0, 0), (x - 2, y - 2), (x - 2, y + 2))
        pygame.draw.line(self.game.screen, (0, 0, 0), (x - 1, y - 2), (x - 1, y + 2))
        pygame.draw.line(self.game.screen, (0, 0, 0), (x, y - 2), (x, y + 2))
        pygame.draw.line(self.game.screen, (0, 0, 0), (x + 1, y - 2), (x + 1, y + 2))

    def erase_bullet(self, x, y):
        """Usuwa rysunek kuli armatniej
        :param x: współrzędna x środka kuli
        :param y: współrzędna y środka kuli"""
        pygame.draw.line(self.game.screen, (0, 127, 255), (x - 2, y - 2), (x - 2, y + 2))
        pygame.draw.line(self.game.screen, (0, 127, 255), (x - 1, y - 2), (x - 1, y + 2))
        pygame.draw.line(self.game.screen, (0, 127, 255), (x, y - 2), (x, y + 2))
        pygame.draw.line(self.game.screen, (0, 127, 255), (x + 1, y - 2), (x + 1, y + 2))

    def shoot(self, castle):
        """Wykonuje strzał z armaty zamku
        :param castle: numer zamku gracza"""
        db = dbm.ndbm.open("players", "c")
        db[self.numer] = "_@_".join([repr(self.life), repr(self.castle_pos)])
        db.close()

        if self.speeds[castle] > 0:
            if self.angles[castle] != 90:
                rads = self.angles[castle] * pi / 180
                start_x = int(self.armat_pos[castle][0] + 6 * cos(rads))
                start_y = int(self.armat_pos[castle][1] - 6 * sin(rads))
                speed_x = self.speeds[castle] * abs(cos(rads)) * 0.75

                def fdist(x):
                    return start_y - int(x * tan(rads) - 9.81 * x * x / (2 * speed_x * speed_x))

                x = -8 if self.angles[castle] > 90 else 8

                while self.game.background[start_x + x][1] != ():
                    x = x - 2 if self.angles[castle] > 90 else x + 2

                y = fdist(x)

                while 0 < start_x + x < len(self.game.background) and self.game.background[start_x + x][0] - int(bool(self.game.background[start_x + x][1])) * 16 > y:
                    if y >= 0:
                        self.draw_bullet(start_x + x, y)
                        pygame.display.update()
                        pygame.time.delay(50)
                        self.erase_bullet(start_x + x, y)
                        pygame.display.update()

                    x = x - 2 if self.angles[castle] > 90 else x + 2
                    y = fdist(x)

                self.game.screen.blit(self.castle_img, self.castle_pos[castle])
                self.game.screen.blit(self.all_armats[castle][0], self.all_armats[castle][1])
                pygame.display.update()

                if 0 < start_x + x < len(self.game.background) and self.game.background[start_x + x][0] - 16 < y < self.game.background[start_x + x][0] and self.game.background[start_x + x][1] != ():
                    i = self.game.background[start_x + x][1][0]
                    j = self.game.background[start_x + x][1][1]
                    self.game.screen.blit(
                        self.game.list_players[i].castle_img, self.game.list_players[i].castle_pos[j])
                    self.game.screen.blit(
                        self.game.list_players[i].all_armats[j][0], self.game.list_players[i].all_armats[j][1])
                    pygame.display.update()
                    self.game.list_players[i].hit(j, self.speeds[castle])

                    if i != int(self.numer):
                        self.was_hit = True

                    if i == 0:
                        print("\t\tTWÓJ ZAMEK NUMER", j, "ZOSTAŁ TRAFIONY - TRACI",
                              int(self.speeds[castle] / 5), "Z ŻYCIA")

                    if self.numer == "0":
                        print("\t\tTRAFIŁEŚ ZAMEK", j, "GRACZA", i, " - TRACI ON",
                              int(self.speeds[castle] / 5), "Z ŻYCIA")

                    return i, j
            else:
                x = self.armat_pos[castle][0]
                y = self.castle_pos[castle][1] - 4
                hmax = max(0, y - int(self.speeds[castle] * self.speeds[castle] / (2 * 9.81)))

                while y > hmax:
                    self.draw_bullet(x, y)
                    pygame.display.update()
                    pygame.time.delay(50)
                    self.erase_bullet(x, y)
                    pygame.display.update()
                    y -= 2

                y +=  4

                while y + 2 < self.game.background[x][0] - 16:
                    self.draw_bullet(x, y)
                    pygame.display.update()
                    pygame.time.delay(50)
                    self.erase_bullet(x, y)
                    pygame.display.update()
                    y += 2

                if self.numer == "0":
                    print("\t\tTWÓJ ZAMEK NUMER", castle, "ZOSTAŁ TRAFIONY - TRACI",
                          int(self.speeds[castle] / 5), "Z ŻYCIA")

                self.hit(castle, self.speeds[castle])

                return 0, castle

        self.was_hit = False

        return ()

    def hit(self, castle, sp):
        """Modyfikuje dane trafionego zamku
        :param castle: numer zamku gracza
        :param sp: prędkość wylotowa kuli, która trafiła w zamek"""
        self.life[castle] = self.life[castle] - int(sp / 5)
        self.speeds[castle] = min(self.speeds[castle], 3 * self.life[castle] + 100)

        if self.life[castle] < 0:
            for i in range(self.castle_pos[castle][0], self.castle_pos[castle][0] + 22):
                x = self.game.background[i]
                pygame.draw.line(self.game.screen, (0, 127, 255), (i, x[0]), (i, x[0] - 16))
                x[1] = ()

            self.erase_castle_sign(self.game.act_castle[int(self.numer)])
            self.game.act_castle[int(self.numer)] = 0
            pygame.display.update()
            del self.castle_pos[castle]
            del self.all_armats[castle]
            del self.armat_pos[castle]
            del self.life[castle]
            del self.angles[castle]
            del self.speeds[castle]

            for i, cst in enumerate(self.castle_pos):
                for j in range(21):
                    self.game.background[cst + j][1] = (int(self.numer), i)

            if self.numer == "0":
                self.draw_castle_sign(self.game.act_castle[int(self.numer)])
                print("\t\tSTRACIŁEŚ ZAMEK NUMER", castle)
            else:
                self.draw_castle_sign(self.game.act_castle[int(self.numer)], (48, 48, 48))

            pygame.display.update()

        db = dbm.ndbm.open("players", "c")
        db[self.numer] = "_@_".join([repr(self.life), repr(self.castle_pos)])
        db.close()


class Bot(Player, threading.Thread):
    """Klasa odpowiadająca za pojedynczego gracza komputerowego"""

    def __init__(self, g, nr):
        """Tworzy nowego gracza komputerowego
        :param g: referencja do klasy gry
        :param nr: numer gracza"""
        Player.__init__(self, g, nr)
        threading.Thread.__init__(self)

    def run(self):
        """Działanie wątku gracza komputerowego"""
        castle_chosen = len(self.castle_pos)

        while self.castle_pos:
            if not self.was_hit:
                db = dbm.ndbm.open("players", "c")
                all_castles = [db[i] for i in db.keys() if i != self.numer]
                db.close()
                min_life_enemy = 101
                CP = []
                castles_to_attack = []

                for i in all_castles:
                    CL, CP = map(eval, i.split(b"_@_"))

                    for j, clj in enumerate(CL):
                        if clj < min_life_enemy:
                            castles_to_attack = [CP[j]]
                            min_life_enemy = clj
                        elif clj == min_life_enemy:
                            castles_to_attack.append(CP[j])

            self.game.semphs[int(self.numer)].acquire()

            if not self.was_hit or castle_chosen >= len(self.castle_pos):
                x, y = choice(castles_to_attack)
                dist = 1025

                for i, cst in enumerate(self.castle_pos):
                    if abs(cst[0] - x) < abs(dist):
                        castle_chosen = i
                        dist = cst[0] - x

                angle_chosen = randint(95, 150) if dist > 0 else randint(30, 85)
                rads = angle_chosen * pi / 180
                max_sp = 3 * self.life[castle_chosen] + 100
                speed_chosen = intervalize(
                    50, int(sqrt(-dist * 9.81 / sin(2 * rads) * randint(75, 125) / 100.0)), max_sp)

            self.erase_castle_sign(self.game.act_castle[int(self.numer)])
            self.game.act_castle[int(self.numer)] = castle_chosen
            self.draw_castle_sign(self.game.act_castle[int(self.numer)], (48, 48, 48))
            self.change_angle(castle_chosen, angle_chosen - self.angles[castle_chosen])
            self.change_speed(castle_chosen, speed_chosen - self.speeds[castle_chosen])
            K = self.shoot(castle_chosen)
            self.game.modify_after_shot(K)
            self.game.semphs[0].release()


g = Game()
g.play()
