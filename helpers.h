//
// Created by Harrison on 9/8/2016.
//

#ifndef CS430_PROJ1_IMAGES_HELPERS_H
#define CS430_PROJ1_IMAGES_HELPERS_H

#include <stdio.h>

typedef struct {
    double r, g, b;
} Color;

typedef Color* ColorRef;

/**
 * Peeks the next character in the provided stream
 * @param fp - The file stream to peek into
 * @return - The character that was read
 */
int peek(FILE* fp);

/**
 * Scans over whitespace and comments in the provided file stream
 * @param fp - The file being read
 * @return the total number of characters skipped
 */
int skip_ignored_characters(FILE* fp);

#endif //CS430_PROJ1_IMAGES_HELPERS_H
