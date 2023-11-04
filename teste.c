#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *inputFile;
    FILE *outputFile;
    char inputFileName[100];
    char outputFileName[100];
    char fileExtension[10];
    char path[100];
    int TAMANHO_BUFFER = 8192;
    char buffer[TAMANHO_BUFFER];
    int ofs;
    int fs;
    char pfs;
    
    printf("Arquivo de entrada: ");
    scanf("%s", inputFileName);
    
    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    
    strcpy(path, inputFileName);
    char *lastSlash = strrchr(path, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }
    
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Erro ao abrir o diretório.\n");
        return 1;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char fileName[] = entry -> d_name;
        char extension[] = strrchr(fileName, '.');
        if (extension != NULL) {
            strcpy(fileExtension, extension + 1);
            if (strcmp(fileName, inputFileName) == 0) {
                strcpy(inputFileName, fileName);
                break;
            }
        }
    }
    closedir(dir);
    
    printf("Arquivo de saída (txt): ");
    scanf("%s", outputFileName);
    
    if (strstr(outputFileName, ".txt") == NULL) {
        strcat(outputFileName, ".txt");
    }
    
    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    
    outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }
    
    fseek(inputFile, 0, SEEK_END);
    ofs = ftell(inputFile);
    fs = ofs;
    pfs = ' ';
    
    for (TAMANHO_BUFFER += 0; TAMANHO_BUFFER >= 4; TAMANHO_BUFFER *= 0.5) {
        if (fs >= 1000) {
            fs /= 1000;
            pfs = 'K';
            if (fs >= 1000) {
                fs /= 1000;
                pfs = 'M';
                if (fs >= 1000) {
                    fs /= 1000;
                    pfs = 'G';
                }
            }
        }
        
        long startTime = time(NULL);
        while (1) {
            size_t bytesRead = fread(buffer, 1, TAMANHO_BUFFER, inputFile);
            if (bytesRead == 0) {
                break;
            }
            fwrite(buffer, 1, bytesRead, outputFile);
        }
        float elapsedTime = (float)(time(NULL) - startTime);
        printf("\nTipo de arquivo:    %s\n", fileExtension);
        printf("Tamanho do arquivo: %d Bytes (%d %cB)\n", ofs, fs, pfs);
        printf("Tempo de execução:  %.2f segundos\n", elapsedTime);
        printf("Tamanho do buffer:  %d Bytes\n", TAMANHO_BUFFER);
    }
    
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}