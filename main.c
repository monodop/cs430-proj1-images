#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "header.h"
#include "helpers.h"

/**
 * Displays the usage information and returns an error exit code
 * @return exit code 1
 */
int displayUsage();

int main(int argc, char* argv[]) {

    int targetFormat;
    char* inputFilename;
    char* outputFilename;
    FILE *filePointer;
    PpmHeader fileHeader;
    ColorRef pixelGrid;

    // Validate argument count
    if (argc != 4)
        return displayUsage();

    // Validate target format parameter
    targetFormat = atoi(argv[1]);
    if (targetFormat != 3 && targetFormat != 6) {
        fprintf(stderr, "Invalid parameter target_format = '%s', expected 3 or 6.\n", argv[1]);
        return displayUsage();
    }

    inputFilename = argv[2];
    outputFilename = argv[3];

    // Open input file
    printf("Processing input file.\n");
    filePointer = fopen(inputFilename, "r");
    if (filePointer == NULL) {
        fprintf(stderr, "File '%s' does not exist or cannot be opened. Error number %d.\n", inputFilename, errno);
        return displayUsage();
    }

    // Read input image file's headers
    if (!header_read(filePointer, &fileHeader)) {
        fprintf(stderr, "Unable to continue processing image file.\n");
        return displayUsage();
    }
    printf("Detected file with dimensions %u x %u of type P%d, maxval=%hu.\n",
           fileHeader.imageWidth,
           fileHeader.imageHeight,
           fileHeader.ppmType,
           fileHeader.maxVal);

    // Create the pixel grid in memory
    pixelGrid = malloc(sizeof(Color) * fileHeader.imageWidth * fileHeader.imageHeight);

    // Close input file
    fclose(filePointer);
    printf("Input file processed.\n");

    // Deallocate the pixel grid
    free(pixelGrid);

    return 0;
}

int displayUsage() {
    fprintf(stderr, "Usage: ppmrw target_format input_filename output_filename\n");
    fprintf(stderr, " - target_format: The PX format that the output file should be converted to. Valid options are 3 or 6.\n");
    fprintf(stderr, " - input_filename: The name of the ppm file that will be converted.\n");
    fprintf(stderr, " - output_filename: The name of the ppm file that will be created in the target format.\n");
    return 1;
}