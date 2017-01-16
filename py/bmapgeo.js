var Wg = ["=", ".", "-", "*"]
  , Xg = 8388608, Sg = 0, Tg = 1, Ug = 2;

function Yg(a) {
    var b = a.charCodeAt(0);
    return "A" <= a && "Z" >= a ? b - 65 : "a" <= a && "z" >= a ? 26 + b - 97 : "0" <= a && "9" >= a ? 52 + b - 48 : "+" == a ? 62 : "/" == a ? 63 : -1
}

function Zg(a, b) {
    var c = b.length;
    if (2 > c)
        return -1;
    for (var d = 0, e = 0, f = 0, g = 0; 4 > g; g++) {
        f = Yg(a.substr(g, 1));
        if (0 > f)
            return -1 - g;
        d += f << 6 * g;
        f = Yg(a.substr(4 + g, 1));
        if (0 > f)
            return -5 - g;
        e += f << 6 * g
    }
    d > Xg && (d = Xg - d);
    e > Xg && (e = Xg - e);
    b.push(b[c - 2] + d);
    b.push(b[c - 1] + e);
    return 0
}

function Vg(a) {
    var b;
    b = a.charAt(0);
    var c = -1;
    b == Wg[1] ? c = Ug : b == Wg[2] ? c = Tg : b == Wg[3] && (c = Sg);
    b = c;
    for (var c = a.substr(1), d = 0, e = c.length, f = [], a = [], g = []; d < e; )
        if (c.charAt(d) == Wg[0]) {
            if (13 > e - d)
                return 0;
            a: {
                for (var g = c.substr(d, 13), i = f, k = 0, l = 0, m = 0, n = 0; 6 > n; n++) {
                    m = Yg(g.substr(1 + n, 1));
                    if (0 > m) {
                        g = -1 - n;
                        break a
                    }
                    k += m << 6 * n;
                    m = Yg(g.substr(7 + n, 1));
                    if (0 > m) {
                        g = -7 - n;
                        break a
                    }
                    l += m << 6 * n
                }
                i.push(k);
                i.push(l);
                g = 0
            }
            if (0 > g)
                return 0;
            d += 13
        } else if (";" == c.charAt(d))
            a.push(f.slice(0)),
            f.length = 0,
            ++d;
        else {
            if (8 > e - d)
                return 0;
            g = Zg(c.substr(d, 8), f);
            if (0 > g)
                return 0;
            d += 8
        }
    c = 0;
    for (d = a.length; c < d; c++) {
        e = 0;
        for (f = a[c].length; e < f; e++)
            a[c][e] /= 100
    }
    return {
        QW: b,
        Gd: a
    }
}
console.log(Vg(".=PsDtQBzNbuVA;"));
