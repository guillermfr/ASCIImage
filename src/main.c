#include "header.h"

int main(int argc, char** argv) {

    FILE* inputImage = fopen("data/test.jpg", "rb");
    FILE* asciiImage = fopen("data/image.txt", "w+");

    if(inputImage == NULL) {
        printf("File does not exist\n");
    }
    
    imgToAscii2(inputImage, asciiImage);

    fclose(inputImage);
    fclose(asciiImage);

    return 0;
}