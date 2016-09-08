#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int displayUsage();

int main(int argc, char* argv[]) {

    int targetFormat;
    char* inputFilename;
    char* outputFilename;
    FILE *filePointer;

    // Validate argument count
    if (argc != 4)
        return displayUsage();

    // Validate target format parameter
    targetFormat = atoi(argv[1]);
    if (targetFormat != 3 && targetFormat != 6) {
        printf("Invalid parameter target_format = '%s', expected 3 or 6.\n", argv[1]);
        return displayUsage();
    }

    inputFilename = argv[2];
    outputFilename = argv[3];

    // Open file
    printf("Processing input file.\n");
    filePointer = fopen(inputFilename, "r");
    if (filePointer == NULL) {
        printf("File '%s' does not exist or cannot be opened. Error number %d.\n", inputFilename, errno);
        return displayUsage();
    }

    fclose(filePointer);
    printf("Input file processed.\n");

    return 0;
}

/**
 * Displays the usage information and returns an error exit code
 * @return exit code 1
 */
int displayUsage() {
    printf("Usage: ppmrw target_format input_filename output_filename\n");
    printf(" - target_format: The PX format that the output file should be converted to. Valid options are 3 or 6.\n");
    printf(" - input_filename: The name of the ppm file that will be converted.\n");
    printf(" - output_filename: The name of the ppm file that will be created in the target format.\n");
    return 1;
}