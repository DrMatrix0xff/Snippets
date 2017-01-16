#!/usr/bin/env python
# coding: utf-8

# Magic Constants from Baidu Map api
uG = (1.289059486E7, 8362377.87, 5591021, 3481989.83, 1678043.12, 0)

rP = (
    (1.410526172116255E-8, 8.98305509648872E-6, -1.9939833816331, 200.9824383106796, -187.2403703815547, 91.6087516669843, -23.38765649603339, 2.57121317296198, -0.03801003308653, 1.73379812E7),
    (-7.435856389565537E-9, 8.983055097726239E-6, -0.78625201886289, 96.32687599759846, -1.85204757529826, -59.36935905485877, 47.40033549296737, -16.50741931063887, 2.28786674699375, 1.026014486E7),
    (-3.030883460898826E-8, 8.98305509983578E-6, 0.30071316287616, 59.74293618442277, 7.357984074871, -25.38371002664745, 13.45380521110908, -3.29883767235584, 0.32710905363475, 6856817.37),
    (-1.981981304930552E-8, 8.983055099779535E-6, 0.03278182852591, 40.31678527705744, 0.65659298677277, -4.44255534477492, 0.85341911805263, 0.12923347998204, -0.04625736007561, 4482777.06),
    (3.09191371068437E-9, 8.983055096812155E-6, 6.995724062E-5, 23.10934304144901, -2.3663490511E-4, -0.6321817810242, -0.00663494467273, 0.03430082397953, -0.00466043876332, 2555164.4),
    (2.890871144776878E-9, 8.983055095805407E-6, -3.068298E-8, 7.47137025468032, -3.53937994E-6, -0.02145144861037, -1.234426596E-5, 1.0322952773E-4, -3.23890364E-6, 826088.5)
)

class BaiduMapPoi:
    global uG
    global rP
    def __init__(self, lng, lat):
        self.lng = round(float(lng), 6)
        self.lat = round(float(lat), 6)

    # The `convert` method simulates the corresponding function in Baidu Map api
    def convert(self):
        t = ()
        for i, g in enumerate(uG):
            if abs(self.lat) >= g:
                t = rP[i]
                break
        if t:
            lng = t[0] + t[1] * abs(self.lng)
            b = abs(self.lat)/t[9]
            lat = 0
            for i in range(8, 1, -1):
                lat = lat * b + t[i]
            if self.lng < 0:
                lng *= -1
            if self.lat < 0:
                lat *= -1
            return (round(lng, 6), round(lat, 6))

if __name__ == '__main__':
    # 申江路新金桥路路口, Mark Point A
    point = BaiduMapPoi(13540140.62, 3645044.97)
    r = point.convert()
    assert (isinstance(r, tuple))
    print (tuple(map(lambda x: str(x), r)))