#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "header.h"
#include "helpers.h"
#include "ppm3.h"
#include "ppm6.h"

/**
 * Displays the usage information and returns an error exit code
 * @return exit code 1
 */
int displayUsage();

int main(int argc, char* argv[]) {

    /* - - - - - - Setup - - - - - - */

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

    /* - - - - - - Read Data - - - - - - */

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

    // Read the data into the grid
    switch (fileHeader.ppmType) {
        case 3:
            if (!ppm3_parse_data(filePointer, &fileHeader, pixelGrid)) {
                fprintf(stderr, "Unable to continue reading the image file.\n");
                return displayUsage();
            }
            break;
        case 6:
            if (!ppm6_parse_data(filePointer, &fileHeader, pixelGrid)) {
                fprintf(stderr, "Unable to continue reading the image file.\n");
                return displayUsage();
            }
            break;
        default:
            fprintf(stderr, "Unsupported ppm type (must be P3 or P6), unable to read the image.\n");
            return displayUsage();
    }

    // Close input file
    fclose(filePointer);
    printf("Input file processed.\n");

    /* - - - - - - Write Data - - - - - - */

    // Open / Clear output file
    printf("Opening output file for writing.\n");
    filePointer = fopen(outputFilename, "w+");
    if (filePointer == NULL) {
        fprintf(stderr, "File '%s' cannot be opened for writing. Error number %d.\n", outputFilename, errno);
        return displayUsage();
    }

    // Write output image file's headers
    fileHeader.ppmType = (char)targetFormat;
    if (!header_write(filePointer, &fileHeader)) {
        fprintf(stderr, "Unable to write to image file. Operation aborted.\n");
        return displayUsage();
    }

    // Write the data in the grid to the file
    switch (targetFormat) {
        case 3:
            if (!ppm3_write_data(filePointer, &fileHeader, pixelGrid)) {
                fprintf(stderr, "Unable to continue writing the image file.\n");
                return displayUsage();
            }
            break;
        default:
            fprintf(stderr, "Unsupported output ppm type (must be P3 or P6), unable to write the image.\n");
            return displayUsage();
    }

    // Deallocate the pixel grid
    free(pixelGrid);

    // Close output file
    fclose(filePointer);
    printf("Output file processed.\n");

    return 0;
}

int displayUsage() {
    fprintf(stderr, "Usage: ppmrw target_format input_filename output_filename\n");
    fprintf(stderr, " - target_format: The PX format that the output file should be converted to. Valid options are 3 or 6.\n");
    fprintf(stderr, " - input_filename: The name of the ppm file that will be converted.\n");
    fprintf(stderr, " - output_filename: The name of the ppm file that will be created in the target format.\n");
    return 1;
}