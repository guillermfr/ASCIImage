#include "header.h"

int main(int argc, char** argv) {

    // Verify the number of arguments
    if(argc != 3) {
        printf("The number of arguments is incorrect. There should be exactly 2 arguments\n");
        printf("Usage: bin/main inputFile.jpg outputFile.txt\n");
        return 1;
    }

    // Open the input and output files
    FILE* inputImage = fopen(argv[1], "rb");
    FILE* asciiImage = fopen(argv[2], "w+");

    // Check if the files were opened successfully
    if(inputImage == NULL || asciiImage == NULL) {
        printf("File does not exist\n");
    }
    
    // Convert the image to ASCII
    imgToAscii(inputImage, asciiImage);

    // Close the files
    fclose(inputImage);
    fclose(asciiImage);

    return 0;
}