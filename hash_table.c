#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    // Check for duplicates
    Concurso* current = table->table[index];
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
