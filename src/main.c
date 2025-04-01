#include "header.h"

int main(int argc, char** argv) {

    FILE* fIn = fopen("data/image.bmp", "r");
    FILE* fOut = fopen("data/image_gray.bmp", "w+");

    int i, y;
    unsigned char byte[54];

    if(fIn == NULL) {
        printf("File does not exist\n");
    }

    for(i=0; i<54; i++) {
        byte[i] = getc(fIn);
    }

    fwrite(byte, sizeof(unsigned char), 54, fOut);

    int height = *(int*)&byte[18];
    int width = *(int*)&byte[22];
    int bitDepth = *(int*)&byte[28];
    int size = height * width;

    printf("width: %d\n", width);
    printf("height: %d\n", height);

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

    fclose(fIn);
    fclose(fOut);

    return 0;
}