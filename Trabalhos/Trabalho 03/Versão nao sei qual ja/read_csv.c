#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256
#define MAX_ENTRIES 100

typedef struct {
    char* substancia;
    char* ean3;
    float pf_sem_impostos;
} Medicamento;

Medicamento* ler_csv(char* filename, int* num_entries) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    char line[MAX_LEN];
    char* token;
    char* substr;
    Medicamento* medicamentos = (Medicamento*) malloc(MAX_ENTRIES * sizeof(Medicamento));
    int i = 0;

    while (fgets(line, MAX_LEN, file) != NULL && i < MAX_ENTRIES) {
        Medicamento med;

        // Lê a substância
        token = strtok(line, ",");
        substr = token + 1;
        med.substancia = (char*) malloc(strlen(substr) + 1);
        strcpy(med.substancia, substr);

        // Lê o EAN 3
        token = strtok(NULL, ",");
        substr = token + 1;
        med.ean3 = (char*) malloc(strlen(substr) + 1);
        strcpy(med.ean3, substr);

        // Lê o preço sem impostos
        token = strtok(NULL, ",");
        substr = token + 1;
        sscanf(substr, "%f", &med.pf_sem_impostos);
    }

    fclose(file);

    *num_entries = i;
    return medicamentos;
}

