#include "imgToGrayscale.h"

void convertToGrayscale(FILE* fIn, FILE* fOut) {

    int i, y;
    unsigned char byte[54];

    if(fIn == NULL) {
        printf("File does not exist\n");
    }

    for(i=0; i<54; i++) {
        byte[i] = getc(fIn);
    }

    fwrite(byte, sizeof(unsigned char), 54, fOut);

    int width = *(int*)&byte[18];
    int height = *(int*)&byte[22];
    int size = height * width;

    unsigned char buffer[size][3];

    for(i=0; i<size; i++) {

        y = 0;
        buffer[i][0] = getc(fIn);
        buffer[i][1] = getc(fIn);
        buffer[i][2] = getc(fIn);

        y = (buffer[i][0] * 0.3) + (buffer[i][1] * 0.59) + (buffer[i][2] * 0.11);

        putc(y, fOut);
        putc(y, fOut);
        putc(y, fOut);
    }

}