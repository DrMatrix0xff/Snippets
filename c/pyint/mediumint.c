#include <stdlib.h>
#include <assert.h>

#include "mediumint.h"

MediumInt *AllocMediumInt(int size) {
    MediumInt *mi;
    int j;
    mi = (MediumInt *) malloc(sizeof (MediumInt) + size * sizeof(int));
    assert(mi != NULL);
    mi->size = size;
    if (size == 0) {
        mi->digits = NULL;
    } else {
        mi->digits = (int *)(mi + 1);
        for (j = 0; j < size; j++)
            mi->digits[j] = 0;
    }

    return mi;

}

MediumInt *MediumIntFromInt(int i) {
    int j;
    unsigned int u;
    MediumInt *mi;
    u = (unsigned int)i;
    if (u != UISIGNBIT) {
        j = ABS(i);
        u = (unsigned int)j;
    }
    mi = MediumIntFromUnsignedInt(u);
    if (i < 0)
        mi->size *= -1;
    return mi;
}

MediumInt *MediumIntFromUnsignedInt(unsigned int u) {
    int sz = 0;
    unsigned int t = u;
    MediumInt *mi;
    int j;
    if (u == 0) {
        mi = AllocMediumInt(0);
        return mi;
    }
    while (t != 0) {
        sz += 1;
        t >>= SHIFTB;
    }
    mi = AllocMediumInt(sz);
    for (j = 0; j < sz; j++) {
        mi->digits[j] = (int)(u & MASK30);
        u >>= SHIFTB;
    }
    return mi;
}

MediumInt *MediumIntFromLong(long l) {
    long j;
    unsigned long ul;
    MediumInt *mi;
    ul = (unsigned long)l;
    if (ul != ULSIGNBIT) {
        j = ABS(l);
        ul = (unsigned int)j;
    }
    mi = MediumIntFromUnsignedLong(ul);
    if (l < 0)
        mi->size *= -1;
    return mi;
}

/*
 * Place more significant byte at higher index of internal array
 */
MediumInt *MediumIntFromUnsignedLong(unsigned long ul) {
    int sz = 0;
    unsigned long t = ul;
    MediumInt *mi;
    int j;
    if (ul == 0) {
        mi = AllocMediumInt(0);
        return mi;
    }
    while (t != 0) {
        sz += 1;
        t >>= SHIFTB;
    }
    mi = AllocMediumInt(sz);
    for (j = 0; j < sz; j++) {
        mi->digits[j] = (int)(ul & MASK30);
        ul >>= SHIFTB;
    }
    return mi;
}

#define NumberOfBuf(buf, si, dest) do { \
    int i__; \
    dest = 0; \
    for (i__ = (si) + 9; --i__ >= (si); ) \
        dest = 10 * dest + (buf[i__] - '0'); \
} while (0)

#define NumberToBuf(buf, si, source) do { \
    int i__ = (si); \
    int q__, r__, src__ = (source); \
    while (src__ != 0) { \
        q__ = src__ / 10; \
        r__ = src__ - 10 * q__; \
        buf[i__++] = r__ + '0'; \
        src__ = q__; \
    } \
    for (; i__ < (si) + 9; i__++) \
        buf[i__] = '0'; \
} while (0)

char *MediumIntToString(MediumInt *mi) {
    static char decbuf[DECBUFSZ];
    int i, s;
    int num, md, ry;
    long tmp;
    int sz = ABS(mi->size);
    for (i = 0; i < DECBUFSZ; i++)
        decbuf[i] = '\0';
    i = 0;
    if (! sz) {
        decbuf[i] = '0';
        return decbuf;
    }
    for (s = sz; --s >= 0; ) {
        md = mi->digits[s];
        for (i = 0; decbuf[i]; i += 9) {
            NumberOfBuf(decbuf, i, num);
            tmp = (long)num << SHIFTB | md;
            md = (int)(tmp / DECBASE);
            ry = (int)(tmp - md * DECBASE);
            NumberToBuf(decbuf, i, ry);
        }
        NumberToBuf(decbuf, i, md);
        i += 9;
    }
    // strip trailing zeros
    for ( ; decbuf[i - 1] == '0'; i--)
        decbuf[i - 1] = '\0';
    if (mi->size < 0)
        decbuf[i++] = '-';
    for (s = 0; s < --i; s++) {
        char c;
        c = decbuf[s];
        decbuf[s] = decbuf[i];
        decbuf[i] = c;
    }
    return decbuf;
}
