//
// Created by harrison on 9/8/2016.
//

#include "ppm6.h"
#include <ctype.h>

#define INVALID_FILE_ERROR_MESSAGE "Unable to read PPM6 data. Unexpected EOF.\n"

/**
 * Reads a set of 3 values from the input filestream and stores it in the provided ColorRef
 * @param filePointer - the file pointer to read from
 * @param maxValue - the maximum value a number in the file could be (taken from the header)
 * @param color - the color reference to store the values into
 * @return 1 if success, 0 if failure
 */
int ppm6_read_triple(FILE* filePointer, int maxValue, ColorRef color) {
    int c1, c2;

    // Red
    c1 = getc(filePointer);
    if (c1 == EOF) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }
    if (maxValue > 255) {
        c2 = getc(filePointer);
        if (c2 == EOF) {
            fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
            return 0;
        }
        c1 = (c1 << 8) + c2;
    }
    color->r = (double)c1 / maxValue;

    // Green
    c1 = getc(filePointer);
    if (c1 == EOF) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }
    if (maxValue > 255) {
        c2 = getc(filePointer);
        if (c2 == EOF) {
            fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
            return 0;
        }
        c1 = (c1 << 8) + c2;
    }
    color->g = (double)c1 / maxValue;

    // Blue
    c1 = getc(filePointer);
    if (c1 == EOF) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }
    if (maxValue > 255) {
        c2 = getc(filePointer);
        if (c2 == EOF) {
            fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
            return 0;
        }
        c1 = (c1 << 8) + c2;
    }
    color->b = (double)c1 / maxValue;

    return 1;
}

int ppm6_parse_data(FILE* filePointer, PpmHeaderRef header, ColorRef colorGrid) {
    int i, arrLength = header->imageHeight * header->imageWidth;
    int c;

    // Skip one whitespace character
    c = getc(filePointer);
    if (!isspace(c)) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }

    // Loop through each position, parse the triple to it
    for (i = 0; i < arrLength; i++) {
        if (!ppm6_read_triple(filePointer, header->maxVal, colorGrid + i)) {
            return 0;
        }
    }

    return 1;
}