#include "imgToAscii.h"

char imgToAscii(int value) {
    char ascii[] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
    return ascii[value/25];
}