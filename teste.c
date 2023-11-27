#include <stdio.h>
#include <string.h>

// Modelo 1 de read-write em C

int main() {
    FILE *inputFile, *outputFile;
    char nomeArquivo[32], inputFileName[256], outputFileName[256];
    char caminho[1024] = "E:\\Documentos\\Trabalhos FURB\\Trabalho-S.O\\";
    int TAMANHO_BUFFER = 0;

    // Get input file name from user
    printf("Enter the name of the input file: ");
    scanf("%s", nomeArquivo);     
    strcat(caminho, nomeArquivo);
    strcpy(inputFileName, caminho);

    memset(caminho, 0, sizeof(caminho));
    strcpy(caminho, "E:\\Documentos\\Trabalhos FURB\\Trabalho-S.O\\");

    // Get output file name from user
    printf("\nEnter the name of the output file: ");
    scanf("%s", nomeArquivo);
    strcat(caminho, nomeArquivo);
    strcpy(outputFileName, caminho);

    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
    
    outputFile = fopen(caminho, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Read from input file and write to output file using buffer
    char buffer[32768];
    size_t bytesRead;

    fseek(inputFile, 0, SEEK_END);
    long ofilesize = ftell(inputFile);
    fclose(inputFile);

    //while (TAMANHO_BUFFER >= 4){
        long startTime = time(NULL);

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
                fwrite(buffer, 1, bytesRead, outputFile);
            }

        float elapsedTime = (float)(time(NULL) - startTime);

        printf("\nNome do arquivo: %s\n", inputFileName);
        printf("Tamanho do arquivo: %ld Bytes\n", ofilesize);
        printf("Tempo de execucao:  %.2f segundos\n", elapsedTime);
        printf("Tamanho do buffer:  %d Bytes\n\n", TAMANHO_BUFFER);
        TAMANHO_BUFFER *= 0.5; 
    //}
        // while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
        // fwrite(buffer, 1, bytesRead, outputFile);
        // }

    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}