#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "hash_table.h"

int main() {
    HashTable table;
    init_hash_table(&table); // Inicializa a tabela de dispersão

    menu(&table); // Chama a função do menu para interação com o usuário

    clear_table(&table); // Libera recursos e memória alocados

    return 0;
}
