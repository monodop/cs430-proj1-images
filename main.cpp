#include <stdio.h>
#include <stdlib.h>

int displayUsage();

int main(int argc, char* argv[]) {

    // Validate argument count
    if (argc != 4)
        return displayUsage();

    // Validate target format parameter
    int targetFormat = atoi(argv[1]);
    if (targetFormat != 3 && targetFormat != 6) {
        printf("Invalid parameter target_format = '%s', expected 3 or 6.\n", argv[1]);
        return displayUsage();
    }

    char* inputFilename = argv[2];
    char* outputFilename = argv[3];

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