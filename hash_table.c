#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Para usar INT_MAX
#include "hash_table.h"

static int hash_function(int numero) {
    return numero % TABLE_SIZE;
}

void init_hash_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }
}

void clear_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* current = table->table[i];
        while (current != NULL) {
            Concurso* temp = current;
            current = current->next;
            free(temp);
        }
        table->table[i] = NULL;
    }
}

void insert(HashTable* table, Concurso concurso) {
    int index = hash_function(concurso.numero);
    Concurso* current = table->table[index];
    
    // Check for duplicates
    while (current != NULL) {
        if (current->numero == concurso.numero) {
            printf("Concurso com o número %d já existe.\n", concurso.numero);
            return;
        }
        current = current->next;
    }
    
    // Insert new concurso
    Concurso* new_concurso = (Concurso*)malloc(sizeof(Concurso));
    *new_concurso = concurso;
    new_concurso->next = table->table[index];
    table->table[index] = new_concurso;
}

Concurso* search(HashTable* table, int numero) {
    int index = hash_function(numero);
    Concurso* current = table->table[index];
    while (current != NULL) {
        if (current->numero == numero) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void remove_concurso(HashTable* table, int numero) {
    int index = hash_function(numero);
    Concurso* current = table->table[index];
    Concurso* prev = NULL;
    
    while (current != NULL) {
        if (current->numero == numero) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                table->table[index] = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Concurso com o número %d não encontrado.\n", numero);
}

void print_all(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* current = table->table[i];
        while (current != NULL) {
            printf("Número do Concurso: %d\n", current->numero);
            printf("Data: %s\n", current->data);
            printf("Números Sorteados: ");
            for (int j = 0; j < 6; j++) {
                printf("%d ", current->bolas[j]);
            }
            printf("\n");
            current = current->next;
        }
    }
}

void load_from_file(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip header line

    while (fgets(line, sizeof(line), file)) {
        Concurso concurso;
        sscanf(line, "%d,%10[^,],%d,%d,%d,%d,%d,%d",
               &concurso.numero,
               concurso.data,
               &concurso.bolas[0],
               &concurso.bolas[1],
               &concurso.bolas[2],
               &concurso.bolas[3],
               &concurso.bolas[4],
               &concurso.bolas[5]);
        concurso.next = NULL; // Initialize next pointer
        insert(table, concurso);
    }

    fclose(file);
}

void quantidade_sorteios_numero(HashTable* table) {
    int numero, count = 0;
    printf("Digite o número a ser consultado: ");
    scanf("%d", &numero);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* current = table->table[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                if (current->bolas[j] == numero) {
                    count++;
                }
            }
            current = current->next;
        }
    }
    printf("O número %d foi sorteado %d vezes.\n", numero, count);
}

void dez_numeros_mais_sorteados(HashTable* table) {
    int freq[61] = {0}; // Frequência de 1 a 60

    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* current = table->table[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                freq[current->bolas[j]]++;
            }
            current = current->next;
        }
    }

    printf("Dez números mais sorteados:\n");
    for (int i = 0; i < 10; i++) {
        int max = 0, numero = 0;
        for (int j = 1; j <= 60; j++) {
            if (freq[j] > max) {
                max = freq[j];
                numero = j;
            }
        }
        printf("Número %d: %d vezes\n", numero, max);
        freq[numero] = 0; // Reseta o valor para encontrar o próximo maior
    }
}

void dez_numeros_menos_sorteados(HashTable* table) {
    int freq[61] = {0}; // Frequência de 1 a 60

    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* current = table->table[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                freq[current->bolas[j]]++;
            }
            current = current->next;
        }
    }

    printf("Dez números menos sorteados:\n");
    for (int i = 0; i < 10; i++) {
        int min = INT_MAX, numero = 0;
        for (int j = 1; j <= 60; j++) {
            if (freq[j] < min && freq[j] > 0) {
                min = freq[j];
                numero = j;
            }
        }
        printf("Número %d: %d vezes\n", numero, min);
        freq[numero] = INT_MAX; // Seta para o valor máximo para não contar novamente
    }
}

void quantidade_concursos_ano(HashTable* table) {
    int ano, count = 0;
    printf("Digite o ano a ser consultado (yyyy): ");
    scanf("%d", &ano);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* current = table->table[i];
        while (current != NULL) {
            int ano_concurso;
            sscanf(current->data + 6, "%d", &ano_concurso); // Extrai o ano da data
            if (ano_concurso == ano) {
                printf("Número do Concurso: %d, Data: %s\n", current->numero, current->data);
                count++;
            }
            current = current->next;
        }
    }
    printf("Total de concursos no ano %d: %d\n", ano, count);
}
