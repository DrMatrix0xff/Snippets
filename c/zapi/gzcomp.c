#include <stdio.h>
#include <stdlib.h>

#include <zlib.h>

static const int CHUNK = 16384;

int gzsave(FILE *source, const char *gzfilename)
{
    unsigned int rbytes;
    unsigned char in[CHUNK];

    gzFile gzf = gzopen(gzfilename, "wb1h");
    if (! gzf) {
        (void) fprintf(stderr, "fail to open %s\n", gzfilename);
        exit(1);
    }
    while (! feof(source)) {
        rbytes = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            gzclose(gzf);
            (void) fprintf(stderr, "error on input stream\n");
            exit(1); 
        }
        if (gzwrite(gzf, in, rbytes) == 0) {
            gzclose(gzf);
            (void) fprintf(stderr, "error when write to gz file\n");
            exit(1);
        }
    }
    gzclose(gzf);

    fclose(source);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *source = "packages.txt";
    const char *dest = "haiya.gz";
    FILE *fp;
    if ((fp = fopen(source, "r")) == NULL) {
        fprintf(stderr, "failure on open input source: %s\n", source);
        exit(1);
    }
    if (gzsave(fp, dest) == 0)
        ;

   return 0;
}

