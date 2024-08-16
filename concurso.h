#ifndef CONCURSO_H
#define CONCURSO_H

#define MAX_CONCURSOS 1000
#define MAX_NUMEROS 6

typedef struct Concurso {
    int numero;
    char data[11];
    int numeros[MAX_NUMEROS];
    struct Concurso* prox;  // Para tratamento de colisões
} Concurso;

typedef struct HashTable {
    Concurso* tabela[MAX_CONCURSOS];
} HashTable;

void inicializar_tabela(HashTable* hashTable);
Concurso* criar_concurso(int numero, const char* data, int numeros[]);
void inserir_concurso(HashTable* hashTable, Concurso* concurso);
Concurso* buscar_concurso(HashTable* hashTable, int numero);
void remover_concurso(HashTable* hashTable, int numero);
void visualizar_concursos(HashTable* hashTable);
void carregar_concursos(HashTable* hashTable, const char* arquivo);
void apresentar_estatisticas(HashTable* hashTable);

#endif
