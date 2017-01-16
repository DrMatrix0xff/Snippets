#include <stdio.h>

char *prefix_to_postfix(const char s[]) {
    int i = 0;
    static char buf[3000] = {0};
    int bi = 0; /* buf index */
    struct {
        char op;
        int nnum;
    } stack[100];
    int sp = 0;
    int nnum = 0; /* current number of digit */
    while (s[i] != '\0') {
        i += 1;
    }
    if (i >= 3000)
        return NULL;
    for (i = 0; s[i] != '\0'; i++) {
        switch (s[i]) {
            case '+':
            case '-':
            case '*':
                stack[sp].op = s[i];
                stack[sp].nnum = 0;
                sp += 1;
                nnum = 0;
                break;
            default:
                if (nnum == 0) {
                    buf[bi++] = s[i];
                    nnum += 1;
                    if (sp >= 1)
                        stack[sp - 1].nnum = nnum;
                } else {
                    if (sp <= 0) {
                        fprintf(stderr, "leftover digit: %c\n", s[i]);
                        return NULL;
                    }
                    buf[bi++] = s[i];
                    nnum += 1;
                    while (sp >= 1 && nnum >= 2) {
                        sp -= 1;
                        buf[bi++] = stack[sp].op;
                        if (sp >= 1) {
                            nnum = stack[sp-1].nnum + 1;
                            stack[sp-1].nnum = nnum;
                        } else {
                            nnum -= 1;
                            if (s[i + 1] != '\0') {
                                fprintf(stderr, "leftover prefix expression: %s\n", s + (i+1));
                                return NULL;
                            }
                        }
                    }
                }
        }
    }
    if (sp == 0 && nnum == 1)
        return buf;
    else {
        fprintf(stderr, "final check failed, sp=%d, nnum=%d\n", sp, nnum);
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    char *exp = "+1*2+34";
    char *resbuf;
    int valstack[100];
    int sp = 0;
    int i;
    int rand1, rand2;
    int result;
    resbuf = prefix_to_postfix(exp);
    fprintf(stdout, "prefix: %s\npostfix: %s\n", exp, resbuf);
    if (!resbuf) {
        return 1;
    }
    for (i = 0; resbuf[i]; i++) {
        switch (resbuf[i]) {
            case '+':
                rand1 = valstack[--sp];
                rand2 = valstack[--sp];
                valstack[sp++] = rand2 + rand1;
                break;
            case '-':
                rand1 = valstack[--sp];
                rand2 = valstack[--sp];
                valstack[sp++] = rand2 - rand1;
                break;
            case '*':
                rand1 = valstack[--sp];
                rand2 = valstack[--sp];
                valstack[sp++] = rand2 * rand1;
                break;
            default:
                valstack[sp++] = resbuf[i] - '0';
        }
    }
    if (sp == 1) {
        result = valstack[0];
        printf("result of expression: %d\n", result);
    }
    return 0;
}



