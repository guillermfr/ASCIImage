#include "header.h"

int main(int argc, char** argv) {

    FILE* inputImage = fopen("data/sample1.bmp", "r");
    FILE* grayscaleImage = fopen("data/image_gray.bmp", "w+");
    FILE* asciiImage = fopen("data/image.txt", "w+");
    FILE* resizedImage = fopen("data/small.bmp", "w+");

    if(inputImage == NULL) {
        printf("File does not exist\n");
    }

    fclose(inputImage);
    fclose(grayscaleImage);
    fclose(asciiImage);
    fclose(resizedImage);

    return 0;
}