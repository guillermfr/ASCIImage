#ifndef IMGTOASCII_H
#define IMGTOASCII_H

#include "includes.h"

// Déclaration du prototype des fonctions
char pxlToAscii(int value);
void imgToAscii(FILE* fIn, FILE* fOut);

#endif