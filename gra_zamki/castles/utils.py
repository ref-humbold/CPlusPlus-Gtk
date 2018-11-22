# -*- coding: utf-8 -*-


def bound(minimum, elem, maximum):
    return minimum if elem < minimum else maximum if elem > maximum else elem
