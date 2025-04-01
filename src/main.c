#include "header.h"

char imgToAscii(int value) {
    char ascii[] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
    return ascii[value/25];
}

int main(int argc, char** argv) {

    FILE* fIn = fopen("data/sample1.bmp", "r");
    FILE* fOut = fopen("data/image_gray.bmp", "w+");
    FILE* txt = fopen("data/image.txt", "w+");
    FILE* small = fopen("data/small.bmp", "w+");

    int i, y;
    char c;
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

        c = imgToAscii(y);
        putc(c, txt);

        if((i+1) % width == 0) {
            putc('\n', txt);
        }
    }

    int scaleFactor = 4;
    int newWidth = width / scaleFactor;
    int newHeight = height / scaleFactor;

    *(int*)&byte[18] = newWidth;
    *(int*)&byte[22] = newHeight;

    fwrite(byte, sizeof(unsigned char), 54, small);

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

        fwrite(newRow, sizeof(unsigned char), newRowSize, small);
    }

    free(row);
    free(newRow);

    fclose(fIn);
    fclose(fOut);
    fclose(txt);
    fclose(small);

    return 0;
}