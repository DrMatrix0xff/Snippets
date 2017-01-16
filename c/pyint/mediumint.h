#ifndef MEDIUM_INT_H
#define MEDIUM_INT_H

#define MAXSEG 10240
#define DECBUFSZ 102400

#define SHIFTB 30
#define BINBASE ((1 << SHIFTB))
#define DECBASE 1000000000
#define MASK30 ((BINBASE) - 1)

#define UISIGNBIT ((1U)<<31)
#define ULSIGNBIT ((1UL)<<63)

#define ABS(x) ((x) < 0?(-(x)):(x))

typedef struct medium_int MediumInt;

struct medium_int {
    int size;
    int *digits;
};

MediumInt *AllocMediumInt(int size);

MediumInt *MediumIntFromInt(int i); 
MediumInt *MediumIntFromUnsignedInt(unsigned int ui); 

MediumInt *MediumIntFromLong(long l); 
MediumInt *MediumIntFromUnsignedLong(unsigned long ul); 

char *MediumIntToString(MediumInt *mi);

#endif

