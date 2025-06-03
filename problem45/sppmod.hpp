// sppmod.h
#ifndef SPPMOD_H
#define SPPMOD_H
#include <cstdio>
// const
const int MAX_VER_CHARS = 10;
const int SPP_MAGIC_DEFINE = 4;

// Point pair: (x, y)
struct point {
    double x, y;
};

// Header for .spp format
struct sppHeader {
    char def[SPP_MAGIC_DEFINE]; // magic "SPP\0"
    char version[MAX_VER_CHARS]; // version: "x.x.x\0"
    int numPoints;
};

// IO Functions for .spp
int sppRead(const char* fname, point** points);
int sppWrite(const char* fname, point* points, int numPoints);

// Help functions for IO
FILE* openSpp(const char* fname, const char* mode);
int readHeader(FILE* fname, sppHeader* header);
int checkFormatFile(sppHeader* header);
int readPoints(FILE* fname, sppHeader* header, point** points);
int closeSpp(FILE* file);
#endif

