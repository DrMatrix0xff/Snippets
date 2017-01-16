#include <stdio.h>
#include <stdlib.h>

#include "mediumint.h"

int main(int argc, char *argv[]) {
    unsigned long l;
    unsigned char *p;
    int i;

    MediumInt *mii;

    p = (unsigned char *)&l;
    for (i = 0; i < 8; i++)
        p[i] = '\xff';

    mii = MediumIntFromUnsignedLong(l);
    fprintf(stdout, "[ primitive ] value of l: %lu\n", l);

    p = (unsigned char *)MediumIntToString(mii);
    fprintf(stdout, "[ diy ] value of l: %s\n", (char *)p);
    free(mii);

    mii = AllocMediumInt(18);
    for (i = 0; i <= 16; i++)
        mii->digits[i] = MASK30;
    mii->digits[17] = (1 << 2) - 1;
    mii->size *= -1;

    p = (unsigned char *)MediumIntToString(mii);
    fprintf(stdout, "[ diy ] value of l: %s\n", (char *)p);
    free(mii);

    return 0;
}

