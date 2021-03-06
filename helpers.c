//
// Created by Harrison on 9/8/2016.
//

#include <ctype.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Peeks the next character in the provided stream
 * @param fp - The file stream to peek into
 * @return - The character that was read
 */
int peek(FILE* fp) {
    int c;
    c = getc(fp);
    ungetc(c, fp);
    return c;
}

/**
 * Scans over whitespace and comments in the provided file stream
 * @param fp - The file being read
 * @return the total number of characters skipped
 */
int skip_ignored_characters(FILE* fp) {
    int c, count = 0;
    while (1) {
        c = peek(fp);
        if (isspace(c)) {
            // Whitespace mode
            getc(fp);
            count++;
        } else if (c == '#') {
            // Comment mode
            do {
                getc(fp);
                count++;
                c = peek(fp);
            }
            while (c != '\n' && c != '\r');
        } else {
            break;
        }
    }
    return count;
}

int wxy_to_index(int width, int x, int y) {
    return x + y*width;
}

void index_to_xwy(int index, int width, int* x, int* y) {
    *x = index % width;
    *y = index / width;
}