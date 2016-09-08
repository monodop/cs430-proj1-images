//
// Created by harrison on 9/8/2016.
//

#include <stdlib.h>
#include "header.h"

#define INVALID_FILE_ERROR_MESSAGE "Unable to read PPM headers. The provided file is either not a PPM P3/P6 file or has been corrupted.\n"
#define INVALID_WIDTH_ERROR_MESSAGE "PPM file contained an invalid width.\n"
#define INVALID_HEIGHT_ERROR_MESSAGE "PPM file contained an invalid height.\n"

int header_read(FILE* filePointer, PpmHeaderRef headerData) {
    int nextChar, count;
    unsigned int nextNumber;

    // Check first part of magic number
    nextChar = getc(filePointer);
    if (nextChar != 'P') {
        printf(INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }

    // Check second part of magic number
    nextChar = getc(filePointer);
    if (nextChar != '3' && nextChar != '6') {
        printf(INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }

    // Determine which magic number was used
    if (nextChar == '3')
        headerData->ppmType = 3;
    else
        headerData->ppmType = 6;

    // Get the image width
    count = fscanf(filePointer, " %u ", &nextNumber);
    if (count == 0 || count == EOF) {
        printf(INVALID_FILE_ERROR_MESSAGE);
        printf(INVALID_WIDTH_ERROR_MESSAGE);
        return 0;
    }
    headerData->imageWidth = nextNumber;

    // Get the image height
    count = fscanf(filePointer, " %u ", &nextNumber);
    if (count == 0 || count == EOF) {
        printf(INVALID_FILE_ERROR_MESSAGE);
        printf(INVALID_HEIGHT_ERROR_MESSAGE);
        return 0;
    }
    headerData->imageHeight = nextNumber;
    return 1;
}