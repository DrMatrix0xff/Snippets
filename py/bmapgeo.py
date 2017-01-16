#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Created on Tuesday,27 December 2016.

Wg = ['=', '.', '-', '*']
Xg = 8388608
Sg = 0
Tg = 1
Ug = 2

def Yg(a):
    b = a[0]
    r = 0
    if "A" <= a <= "Z":
        r = ord(b) - 65
    elif "a" <= a <= "z":
        r = 26 + ord(b) - 97
    elif "0" <= a <= "9":
        r = 52 + ord(b) - 48
    elif a == "+":
        r = 62
    elif a == "/":
        r = 63
    else:
        r = -1
    return r

def Zg(a, b):
    r = 0
    c = len(b)
    if c <= 1:
        r = -1
        return r
    d = 0
    e = 0
    f = 0
    g = 0
    while g < 4:
        f = Yg(a[g])
        if f < 0:
            return -1 - g
        d += f << (6 * g)
        f = Yg(a[g+4])
        if f < 0:
            return -5 - g
        e += f << (6 * g)
        g += 1
    if d > Xg:
        d = Xg - d
    if e > Xg:
        e = Xg - e
    b.append(b[c-2] + d)
    b.append(b[c-1] + e)
    return r

def Vg(a):
    b = a[0]
    c = -1
    if b == Wg[1]:
        c = Ug
    elif b == Wg[2]:
        c = Tg
    elif b == Wg[3]:
        c = Sg
    b = c
    cc = a[1:]
    d = 0
    e = len(cc)
    f = []
    aa = []
    while d < e:
        if cc[d] == Wg[0]:
            if e - d < 13:
                return 0
            entry_label_a = True
            gg = cc[d:d+13]
            k = 0
            l = 0
            n = 0
            while n < 6:
                m = Yg(gg[n+1])
                if m < 0:
                    g = -1 - n
                    entry_label_a = False
                    break
                k += m << (6 * n)
                m = Yg(gg[n+7])
                if m < 0:
                    g = -7 - n
                    entry_label_a = False
                    break
                l += m << (6 * n)
                n += 1
            if entry_label_a:
                f.append(k)
                f.append(l)
                g = 0
            if g < 0:
                return 0
            d += 13
        elif cc[d] == ';':
            aa.append(f)
            d += 1
        else:
            if e -d < 8:
                return 0
            g = Zg(cc[d:d+8], f)
            if g < 0:
                return 0
            d += 8
    c = 0
    d = len(aa)
    while c < d:
        e = 0
        f = len(aa[c])
        while e < f:
            aa[c][e] /= 100.0
            e += 1
        c += 1
    return {'QW': b, 'Gd': aa}

if __name__ == '__main__':
    print Vg(".=PsDtQBzNbuVA;")
