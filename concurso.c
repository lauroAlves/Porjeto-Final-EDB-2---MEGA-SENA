#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concurso.h"

#define HASH_FUNC(numero) (numero % MAX_CONCURSOS)

void inicializar_tabela(HashTable* hashTable) {
    for (int i = 0; i < MAX_CONCURSOS; i++) {
        hashTable->tabela[i] = NULL;
    }
}

Concurso* criar_concurso(int numero, const char* data, int numeros[]) {
    Concurso* novo = (Concurso*)malloc(sizeof(Concurso));
    novo->numero = numero;
    strncpy(novo->data, data, 11);
    memcpy(novo->numeros, numeros, MAX_NUMEROS * sizeof(int));
    novo->prox = NULL;
    return novo;
}

void inserir_concurso(HashTable* hashTable, Concurso* concurso) {
    int index = HASH_FUNC(concurso->numero);
    Concurso* atual = hashTable->tabela[index];

    while (atual != NULL) {
        if (atual->numero == concurso->numero) {
            // Evita duplicação
            free(concurso);
            return;
        }
        atual = atual->prox;
    }
    
    concurso->prox = hashTable->tabela[index];
    hashTable->tabela[index] = concurso;
}

Concurso* buscar_concurso(HashTable* hashTable, int numero) {
    int index = HASH_FUNC(numero);
    Concurso* atual = hashTable->tabela[index];

    while (atual != NULL) {
        if (atual->numero == numero) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void remover_concurso(HashTable* hashTable, int numero) {
    int index = HASH_FUNC(numero);
    Concurso* atual = hashTable->tabela[index];
    Concurso* anterior = NULL;

    while (atual != NULL) {
        if (atual->numero == numero) {
            if (anterior == NULL) {
                hashTable->tabela[index] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void visualizar_concursos(HashTable* hashTable) {
    for (int i = 0; i < MAX_CONCURSOS; i++) {
        Concurso* atual = hashTable->tabela[i];
        while (atual != NULL) {
            printf("Concurso: %d, Data: %s, Números: ", atual->numero, atual->data);
            for (int j = 0; j < MAX_NUMEROS; j++) {
                printf("%d ", atual->numeros[j]);
            }
            printf("\n");
            atual = atual->prox;
        }
    }
}

void carregar_concursos(HashTable* hashTable, const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), fp)) {
        int numero, numeros[MAX_NUMEROS];
        char data[11];
        sscanf(linha, "%d,%10[^,],%d,%d,%d,%d,%d,%d", &numero, data, &numeros[0], &numeros[1], &numeros[2], &numeros[3], &numeros[4], &numeros[5]);
        inserir_concurso(hashTable, criar_concurso(numero, data, numeros));
    }

    fclose(fp);
}

void apresentar_estatisticas(HashTable* hashTable) {
    int freq[61] = {0};  // Frequência dos números sorteados (Mega-Sena tem números de 1 a 60)

    for (int i = 0; i < MAX_CONCURSOS; i++) {
        Concurso* atual = hashTable->tabela[i];
        while (atual != NULL) {
            for (int j = 0; j < MAX_NUMEROS; j++) {
                freq[atual->numeros[j]]++;
            }
            atual = atual->prox;
        }
    }

    printf("Estatísticas:\n");
    // Exemplo de estatísticas simples: Mostrar a frequência dos números
    for (int i = 1; i <= 60; i++) {
        if (freq[i] > 0) {
            printf("Número %d: %d vezes\n", i, freq[i]);
        }
    }
}
