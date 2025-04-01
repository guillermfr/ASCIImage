#include "resize.h"

void resize(FILE* fIn, FILE* fOut, int scaleFactor) {

    int i;
    unsigned char byte[54];

    for(i=0; i<54; i++) {
        byte[i] = getc(fIn);
    }

    int width = *(int*)&byte[18];
    int height = *(int*)&byte[22];

    int newWidth = width / scaleFactor;
    int newHeight = height / scaleFactor;

    *(int*)&byte[18] = newWidth;
    *(int*)&byte[22] = newHeight;

    fwrite(byte, sizeof(unsigned char), 54, fOut);

    int rowSize = (3 * width + 3) & (~3);
    int newRowSize = (3 * newWidth + 3) & (~3);

    unsigned char* row = (unsigned char*)malloc(rowSize);
    unsigned char* newRow = (unsigned char*)malloc(newRowSize);

    for(int y=0; y<newHeight; y++) {
        for(int x=0; x<newWidth; x++) {
            int r = 0, g = 0, b = 0;

            for(int j=0; j<scaleFactor; j++) {
                fseek(fIn, 54 + (y * scaleFactor + j) * rowSize + (x * scaleFactor) * 3, SEEK_SET);
                fread(row, sizeof(unsigned char), 3, fIn);
                b += row[0];
                g += row[1];
                r += row[2];
            }

            b /= (scaleFactor * scaleFactor);
            g /= (scaleFactor * scaleFactor);
            r /= (scaleFactor * scaleFactor);

            newRow[x * 3] = b;
            newRow[x * 3 + 1] = g;
            newRow[x * 3 + 2] = r;
        }

        fwrite(newRow, sizeof(unsigned char), newRowSize, fOut);
    }

    free(row);
    free(newRow);

}