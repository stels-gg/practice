#include "sppmod.cpp"

int main() {
    sppHeader HEADER;
    FILE* file = openSpp("foo.spp", "rb");
    if (readHeader(file, &HEADER) != 0) {
        closeSpp(file);
        return 1;
    };
    int cntPoints = HEADER.numPoints;
    closeSpp(file);
    point** points = new point*[cntPoints];
    sppRead("foo.spp", points);
    printf("Num of points: %i\n", cntPoints);
    for (int i = 0; i < cntPoints; i++) {
        printf("Point %i: %f %f\n", i+1, points[i]->x, points[i]->y);
    }
    return 0;
}
