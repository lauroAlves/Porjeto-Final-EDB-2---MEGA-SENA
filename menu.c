#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Inclua este cabeçalho

#include "menu.h"
#include "hash_table.h"

void print_concurso(Concurso* concurso) {
    if (concurso) {
        printf("Número do Concurso: %d\n", concurso->numero);
        printf("Data: %s\n", concurso->data);
        printf("Números sorteados: ");
        for (int i = 0; i < 6; i++) {
            printf("%d ", concurso->bolas[i]);
        }
        printf("\n");
    } else {
        printf("Concurso não encontrado.\n");
    }
}

void apresentar_estatisticas(HashTable* table) {
    int freq[61] = {0};  // Frequência dos números sorteados (Mega-Sena tem números de 1 a 60)

    for (int i = 0; i < TABLE_SIZE; i++) {
        Concurso* atual = table->table[i];
        while (atual != NULL) {
            for (int j = 0; j < 6; j++) {
                freq[atual->bolas[j]]++;
            }
            atual = atual->next;
        }
    }

    printf("Estatísticas:\n");

    // Dez números mais sorteados
    printf("Dez Números Mais Sorteados:\n");
    for (int i = 1; i <= 60; i++) {
        if (freq[i] > 0) {
            printf("Número %d: %d vezes\n", i, freq[i]);
        }
    }

    // Dez números menos sorteados
    printf("Dez Números Menos Sorteados:\n");
    for (int i = 1; i <= 60; i++) {
        if (freq[i] > 0) {
            printf("Número %d: %d vezes\n", i, freq[i]);
        }
    }
}

void menu(HashTable* table) {
    int option;
    do {
        printf("Menu:\n");
        printf("1. Inserir Concurso\n");
        printf("2. Buscar Concurso\n");
        printf("3. Remover Concurso\n");
        printf("4. Visualizar Todos os Concursos\n");
        printf("5. Carregar Concursos de um Arquivo\n");
        printf("6. Apresentar Estatísticas\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        int numero_concurso;
        Concurso concurso;

        switch (option) {
            case 1:
                printf("Número do Concurso: ");
                scanf("%d", &concurso.numero);
                printf("Data (dd-mm-yyyy): ");
                scanf("%s", concurso.data);
                printf("Digite os 6 números sorteados: ");
                for (int i = 0; i < 6; i++) {
                    scanf("%d", &concurso.bolas[i]);
                }
                insert(table, concurso);
                break;
            case 2:
                printf("Número do Concurso: ");
                scanf("%d", &numero_concurso);
                Concurso* encontrado = search(table, numero_concurso);
                print_concurso(encontrado);
                break;
            case 3:
                printf("Número do Concurso: ");
                scanf("%d", &numero_concurso);
                remove_concurso(table, numero_concurso);
                break;
            case 4:
                print_all(table);
                break;
            case 5:
                printf("Nome do arquivo: ");
                char filename[100];
                scanf("%s", filename);
                filename[strcspn(filename, "\n")] = 0; // Remove o newline no final da string
                load_from_file(table, filename);
                break;
            case 6:
                apresentar_estatisticas(table);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 7);

    printf("Menu encerrado.\n");
}
