#include <stdio.h>
#include <assert.h>

#include <zlib.h>

static const int CHUNK = 4096;

int inf(FILE *source, FILE *dest)
{
    z_stream strm;
    int ret;
    unsigned consumed_out;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            inflateEnd(&strm);
            return Z_ERRNO;
        }
        strm.next_in = in;

        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);
            switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&strm);
                    return ret;
            }

            consumed_out = CHUNK - strm.avail_out;
            if (fwrite(out, 1, consumed_out, dest) != consumed_out ||
                ferror(dest)) {
                inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int ret;
    fp = fopen("ListOfPkgs", "rb");
    ret = inf(fp, stdout);
    if (ret != Z_OK)
        fprintf(stderr, "stream error or other error!\n");
    return 0;
}
