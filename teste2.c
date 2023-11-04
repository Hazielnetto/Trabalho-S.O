#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[32], outputFileName[32];
    int bufferSize = 8192;

    // Get input file name from user
    printf("Enter the name of the input file: ");
    scanf("%s", inputFileName);

    // Get output file name from user
    printf("Enter the name of the output file: ");
    scanf("%s", outputFileName);

    // Open input file in read mode
    inputFile = open(inputFileName, "rb");
    printf("%s", inputFileName);

    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open output file in write mode
    outputFile = open(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Read from input file and write to output file using buffer
    int *buffer = bufferSize;
    size_t bytesRead;
    // while ((bytesRead = fread(buffer, 1, bufferSize, inputFile)) >= 0) {
        while ((bytesRead = fread(buffer, sizeof(int), bufferSize, inputFile)) >= 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}