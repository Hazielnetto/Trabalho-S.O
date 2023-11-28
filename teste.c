#include <stdio.h>
#include <string.h>

// Modelo 1 de read-write em C

int main() {
    FILE *inputFile, *outputFile;
    char nomeArquivo[32], inputFileName[256] = "E:\\Downloads\\GTIP Full-68-v0-30.zip", outputFileName[256] = "E:\\Documentos\\Trabalhos FURB\\Trabalho-S.O\\video2.txt";
    char caminho[1024] = "E:\\Documentos\\Trabalhos FURB\\Trabalho-S.O\\";
    int TAMANHO_BUFFER = 32768;    

    printf("Caminho input: %s", inputFileName);
    printf("Caminho output: %s", outputFileName);

    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
    
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Read from input file and write to output file using buffer
    // char buffer[32768];
    char buffer[TAMANHO_BUFFER];
    size_t bytesRead;
    long l = 0;
    
    while (TAMANHO_BUFFER >= 4)
    {
        long startTime = time(NULL);        

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) 

        {                
            fwrite(buffer, 1, bytesRead, outputFile);
        }

        float elapsedTime = (float)(time(NULL) - startTime);

        printf("\nNome do arquivo: %s\n", inputFileName);
        printf("Tamanho do arquivo: Bytes\n");
        printf("Tempo de execucao:  %.2f segundos\n", elapsedTime);
        printf("Tamanho do buffer:  %ld Bytes\n\n", TAMANHO_BUFFER);
        TAMANHO_BUFFER *= 0.5; 
    }        

    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}