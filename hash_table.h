#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 100

typedef struct Concurso {
    int numero;
    char data[11]; // dd-mm-yyyy + null terminator
    int bolas[6];
    struct Concurso* next; // Membro para encadeamento
} Concurso;

typedef struct HashTable {
    Concurso* table[TABLE_SIZE];
} HashTable;

void init_hash_table(HashTable* table);
void insert(HashTable* table, Concurso concurso);
Concurso* search(HashTable* table, int numero);
void remove_concurso(HashTable* table, int numero);
void print_all(HashTable* table);
void load_from_file(HashTable* table, const char* filename);
void clear_table(HashTable* table);

#endif // HASH_TABLE_H
