# -*- coding: utf-8 -*-

from math import pi


def bound(minim, elem, maxim):
    return minim if elem < minim else maxim if elem > maxim else elem


def radians(degrees):
    return degrees * pi / 180
