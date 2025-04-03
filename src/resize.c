#include "resize.h"

// BUG
// With rectangle images, there's a weird offset

void resize(FILE* fIn, FILE* fOut, int scaleFactor) {

    rewind(fIn);
    rewind(fOut);

    int i;
    unsigned char byte[54];

    for(i=0; i<54; i++) {
        byte[i] = getc(fIn);
    }

    int width = *(int*)&byte[18];
    int height = *(int*)&byte[22];

    int newWidth = width / scaleFactor;
    int newHeight = height / scaleFactor;

    int rowSize = (3 * width + 3) & (~3);
    int newRowSize = (3 * newWidth + 3) & (~3);

    int imageSize = newRowSize * newHeight;
    int fileSize = imageSize + 54;

    *(int*)&byte[18] = newWidth;
    *(int*)&byte[22] = newHeight;
    *(int*)&byte[34] = imageSize;
    *(int*)&byte[2] = fileSize;

    fwrite(byte, sizeof(unsigned char), 54, fOut);

    unsigned char* row = (unsigned char*)malloc(rowSize);
    unsigned char* newRow = (unsigned char*)malloc(newRowSize);

    for(int y=0; y<height; y+=scaleFactor) {

        fseek(fIn, 54 + (y * rowSize), SEEK_SET);
        fread(row, sizeof(unsigned char), rowSize, fIn);

        for(int x=0; x<width; x+=scaleFactor) {
            int r = 0, g = 0, b = 0;

            for (int j = 0; j < scaleFactor; j++) {
                for (int i = 0; i < scaleFactor; i++) {
                    int pixelIndex = ((x + i) * 3);
                    b += row[pixelIndex + 0];
                    g += row[pixelIndex + 1];
                    r += row[pixelIndex + 2];
                }
        }

            b /= (scaleFactor * scaleFactor);
            g /= (scaleFactor * scaleFactor);
            r /= (scaleFactor * scaleFactor);

            int newIndex = (x / scaleFactor) * 3;
            newRow[newIndex + 0] = b;
            newRow[newIndex + 1] = g;
            newRow[newIndex + 2] = r;
        }

        fwrite(newRow, sizeof(unsigned char), newRowSize, fOut);
    }

    free(row);
    free(newRow);

    rewind(fIn);

}