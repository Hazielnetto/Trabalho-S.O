#include <stdio.h>
#include <string.h>
#include <time.h>

// Modelo 1 de read-write em C

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[256] = "C:\\Users\\haziel\\Documents\\Trabalhos FURB\\Trabalho-S.O\\files\\video480p.mp4";
    char outputFileName[256] = "C:\\Users\\haziel\\Documents\\Trabalhos FURB\\Trabalho-S.O\\files\\video480p.mp4.txt";
    int TAMANHO_BUFFER = 32768;    

    printf("Caminho input: %s", inputFileName);
    printf("Caminho output: %s", outputFileName);
    

    // Read from input file and write to output file using buffer
    // char buffer[32768];
    char buffer[TAMANHO_BUFFER];
    size_t bytesRead;
    
    while (TAMANHO_BUFFER >= 4){

        inputFile = fopen(inputFileName, "rb");
        // if (inputFile == NULL) {
        //     printf("Error opening input file.\n");
        //     return 1;
        // }
    
        outputFile = fopen(outputFileName, "wb");
        // if (outputFile == NULL) {
        //  printf("Error opening output file.\n");
        //     return 1;
        // }

        clock_t startTime = clock();        

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0){
            fwrite(buffer, 1, bytesRead, outputFile);
            fflush(inputFile);            
        }

        double elapsedTime = ((double)startTime)/CLOCKS_PER_SEC;

        printf("\nNome do arquivo: %s\n", inputFileName);
        printf("Tamanho do arquivo: Bytes\n");
        printf("Tempo de execucao:  %.3f segundos\n", elapsedTime);
        printf("Tamanho do buffer:  %ld Bytes\n\n", TAMANHO_BUFFER);
        TAMANHO_BUFFER *= 0.5; 
    }        

    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}