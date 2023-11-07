#ifndef biblio
#define biblio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct header {
    char magicNumber[2];
    unsigned int width, height, maxColor;
}header_t;

typedef struct pixel {
    unsigned int R, G, B;
}pixel_t;

typedef struct image {
    header_t header;
    pixel_t* pixels;
}image_t;


FILE* CreateFile();
FILE* OpenFile();

header_t ReadHeader(FILE* image_file);
image_t* ReadImage(FILE* image_file);
image_t* ReadP6(FILE* image_file, header_t header);

void WriteHeader(FILE* out_file, header_t header);
void WriteP6(FILE* out_file, image_t* image);

#endif