#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Modelo 2 de read-write em C

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
        printf("\nTipo de arquivo: %s\n", fileExtension);
        printf("Tamanho do arquivo: %d Bytes (%d %cB)\n", ofs, fs, pfs);
        printf("Tempo de execução: %.2f segundos\n", elapsedTime);
        printf("Tamanho do buffer: %d Bytes\n", TAMANHO_BUFFER);
    }
    
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}


#include <stdio.h>
#include <string.h>

// Modelo 1 de read-write em C

int main() {
    FILE *inputFile, *outputFile;
    char nomeArquivo[32], inputFileName[256], outputFileName[256];
    int buffersize = 32768;

    char caminho[1024] = "E:\\Documentos\\Trabalhos FURB\\Trabalho-S.O\\";

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
    char buffer[buffersize];  
    size_t bytesRead;

    fseek(inputFile, 0, SEEK_END);
    long ofilesize = ftell(inputFile);
    fclose(inputFile);

    for (buffersize += 0; buffersize >= 4; buffersize /= 2) {
        char buffer[buffersize];
        long startTime = time(NULL);

        char buffer[32000];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

        fseek(inputFile, 0, SEEK_SET);
        fseek(outputFile, 0, SEEK_SET);

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
            fwrite(buffer, 1, bytesRead, outputFile);
        }

        float elapsedTime = (float)(time(NULL) - startTime);

        printf("Nome do arquivo: %s\n", inputFileName);
        printf("Tamanho do arquivo: %ld Bytes\n", ofilesize);
        printf("Tempo de execução: %f segundos\n", elapsedTime);
        printf("Tamanho do buffer: %d Bytes (%.2f KB)\n", buffersize, (float)buffersize / 1024.0);
}

    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}