#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MLEN 0x20

static char gbuf[MLEN] = {0};

/* static char *strrelay(char buf[], int ss, int c, int space) {

    int i = ss;
    buf[i++] = c + '0';
    if (space)
        buf[i++] = ' ';
    buf[i] = '\0';
    return buf;

} */

#define strrelay(buf, ss, c, sp) do {\
    int i__ = ss;\
    buf[i__++] = c + '0';\
    if (sp)\
        buf[i__++] = ' ';\
    while (i__ < MLEN)\
        buf[i__++] = '\0';\
} while (0)

#define str_endln(buf) do {\
    int i__ = 0;\
    while (buf[i__])\
        i__++;\
    buf[i__] = '\n';\
    while (++i__ < MLEN)\
        buf[i__] = '\0';\
} while (0)

void permutatecc(int ia[], int n, char buf[]) {

    int i, j, k, l;
    int *suba;
    l = strnlen(buf, MLEN - 1);
    if (n <= 1 && n > 0) {
        strrelay(buf, l, ia[0], 0);
        str_endln(buf);
        fprintf(stdout, "%s", buf);
        return;
    }
    for (i = 0; i < n; i++) {
        strrelay(buf, l, ia[i], 1);
        suba = (int *) calloc(n - 1, sizeof(int));
        for (j = 0, k = 0; j < n; j++) {
            if (j == i)
                continue;
            suba[k++] = ia[j];
        }
        permutatecc(suba, n - 1, buf);
        free(suba);
    }

}

int test_permutate() {
    int a[] = {1, 2, 3, 4, 5};
    permutatecc(a, sizeof(a)/sizeof(int), gbuf);
    return 0;
}

int main(int argc, char *argv[]) {
    return test_permutate();
}

