#include "imgToAscii.h"

char pxlToAscii(int value) {
    char ascii[] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
    int numChars = sizeof(ascii) - 1;

    if (value < 0) value = 0;
    if (value > 255) value = 255;

    int index = value * numChars / 255;

    return ascii[index];
}

void imgToAscii(FILE* fIn, FILE* fOut) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fIn);

    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int numChannels = cinfo.output_components;

    unsigned char* row = (unsigned char*)malloc(width * numChannels);

    for(int y = 0; y < height; y++) {
        unsigned char* rowPtr = row;
        jpeg_read_scanlines(&cinfo, &rowPtr, 1);
        for(int x = 0; x < width; x++) {
            int pixelIndex = (x * numChannels);
            unsigned char pixel[3];
            pixel[0] = row[pixelIndex + 0];
            pixel[1] = row[pixelIndex + 1];
            pixel[2] = row[pixelIndex + 2];

            int pixelValue = (int)(pixel[0] * 0.3 + pixel[1] * 0.58 + pixel[2] * 0.11);
            char asciiChar = pxlToAscii(pixelValue);
            fprintf(fOut, "%c", asciiChar);
        }
        fprintf(fOut, "\n");
    }
}