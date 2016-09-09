//
// Created by Harrison on 9/8/2016.
//

#include "ppm3.h"

#define INVALID_FILE_ERROR_MESSAGE "Unable to read PPM3 data. Unexpected EOF."

/**
 * Reads a set of 3 values from the input filestream and stores it in the provided ColorRef
 * @param filePointer - the file pointer to read from
 * @param maxValue - the maximum value a number in the file could be (taken from the header)
 * @param color - the color reference to store the values into
 * @return 1 if success, 0 if failure
 */
int ppm3_read_triple(FILE* filePointer, unsigned short maxValue, ColorRef color) {
    int count;
    unsigned short nextValue;

    // Red
    skip_ignored_characters(filePointer);
    count = fscanf(filePointer, "%hu", &nextValue);
    if (count == 0 || count == EOF) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }
    color->r = (double)nextValue / maxValue;

    // Green
    skip_ignored_characters(filePointer);
    count = fscanf(filePointer, "%hu", &nextValue);
    if (count == 0 || count == EOF) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }
    color->g = (double)nextValue / maxValue;

    // Blue
    skip_ignored_characters(filePointer);
    count = fscanf(filePointer, "%hu", &nextValue);
    if (count == 0 || count == EOF) {
        fprintf(stderr, INVALID_FILE_ERROR_MESSAGE);
        return 0;
    }
    color->b = (double)nextValue / maxValue;

    return 1;
}

int ppm3_parse_data(FILE* filePointer, PpmHeaderRef header, ColorRef colorGrid) {
    int i, arrLength = header->imageHeight * header->imageWidth;
    unsigned short nextValue;

    // Loop through each position, parse the triple to it
    for (i = 0; i < arrLength; i++) {
        if (!ppm3_read_triple(filePointer, header->maxVal, colorGrid + i)) {
            return 0;
        }
    }
}