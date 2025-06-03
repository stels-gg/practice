// sppmod.cpp - module for .spp files
#include "sppmod.hpp"
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

// version
const string SPP_VERSION = "2.0.1";


int sppRead(const char* fname, point** points) {
    sppHeader header;
    FILE* file = openSpp(fname, "rb");
    if (!file) return -1;

    if (readHeader(file, &header) != 0) {
        closeSpp(file);
        return -1;
    }

    if (checkFormatFile(&header) != 0) {
        closeSpp(file);
        return -1;
    }

    if (readPoints(file, &header, points) != 0) {
        closeSpp(file);
        return -1;
    }

    closeSpp(file);
    return header.numPoints;
}

int sppWrite(const char* fname, point* points, int numPoints) {
    sppHeader header;
    strcpy(header.def, "SPP");
    strncpy(header.version, SPP_VERSION.c_str(), sizeof(header.version) - 1);
    header.version[sizeof(header.version) - 1] = '\0';
    header.numPoints = numPoints;

    FILE* file = openSpp(fname, "wb");
    if (!file) return -1;

    if (fwrite(&header, sizeof(header), 1, file) != 1) {
        printf("Error: can't write header to file\n");
        closeSpp(file);
        return -1;
    }

    if (fwrite(points, sizeof(point), numPoints, file) != (size_t)numPoints) {
        printf("Error: can't write points to file\n");
        closeSpp(file);
        return -1;
    }

    closeSpp(file);
    return numPoints;
}

FILE* openSpp(const char* fname, const char* mode) {
    FILE* file = fopen(fname, mode);
    if (!file) {
        printf("Error: can't open file %s in mode %s\n", fname, mode);
    }
    return file;
}

int readHeader(FILE* fname, sppHeader* header) {
    if (fread(header, sizeof(*header), 1, fname) != 1) {
        printf("Error: can't read header from file\n");
        return -1;
    }
    return 0;
}

int checkFormatFile(sppHeader* header) {
    if (strncmp(header->def, "SPP", 3) != 0) {
        printf("Error: file is not a valid SPP file\n");
        return -1;
    }
    return 0;
}

int readPoints(FILE* fname, sppHeader* header, point** points) {
    *points = new point[header->numPoints];
    if (!*points) {
        printf("Error: memory allocation failed for %d points\n",
                header->numPoints);
        return -1;
    }

    if (fread(*points,
                sizeof(point),
                header->numPoints,
                fname) != (size_t)header->numPoints) {
        printf("Error: can't read points from file\n");
        delete [] *points;
        *points = NULL;
        return -1;
    }
    return 0;
}

int closeSpp(FILE* file) {
    if (!file) return -1;
    fclose(file);
    return 0;
}

