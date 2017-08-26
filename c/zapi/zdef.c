#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <zlib.h>

static const int CHUNK = 4096;

int zdef(FILE *source, FILE *dest, int level)
{
    int ret;
    int flush;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];
    unsigned consumed;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    ret = deflateInit(&strm, level);
    if (ret != Z_OK) {
        fprintf(stderr, "deflate init failed!\n");
        return ret;
    }
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            deflateEnd(&strm);
            return Z_ERRNO;
        }
        strm.next_in = in;
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        (void) fprintf(stderr, "compress in %lu bytes\n", strm.total_in);

        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;

            ret = deflate(&strm, flush);
            assert(ret != Z_STREAM_ERROR);

            // need not check ret when compress
            consumed = CHUNK - strm.avail_out;
            if (fwrite(out, 1, consumed, dest) != consumed ||
                ferror(dest)) {
                deflateEnd(&strm);
                return Z_ERRNO;
            }
            (void) fprintf(stderr, "compress out %lu bytes\n", strm.total_out);
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);
    } while (flush != Z_FINISH);

    assert(ret == Z_STREAM_END);
    deflateEnd(&strm);
    return Z_OK;
}

int main(int argc, char *argv[])
{
    int ret;
    FILE *fp;
    FILE *wfp;
    const char *filename;
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }
    filename = argv[1];
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "fail to open file %s\n", filename);
        exit(1);
    }
    wfp = fopen("hahaz", "wb");
    ret = zdef(fp, wfp, Z_DEFAULT_COMPRESSION);

    if (ret != Z_OK)
        return 1;
    return 0;
}
