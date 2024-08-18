#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void apresentar_estatisticas(HashTable* table) {
    int sub_option;
    do {
        printf("Estatísticas:\n");
        printf("1. Quantidade de sorteios de um número\n");
        printf("2. Dez Números Mais Sorteados\n");
        printf("3. Dez Números Menos Sorteados\n");
        printf("4. Quantidade de concursos em um determinado ano\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &sub_option);

        switch (sub_option) {
            case 1:
                // Implementar a função que conta a quantidade de sorteios de um número específico
                quantidade_sorteios_numero(table);
                break;
            case 2:
                // Implementar a função que mostra os dez números mais sorteados
                dez_numeros_mais_sorteados(table);
                break;
            case 3:
                // Implementar a função que mostra os dez números menos sorteados
                dez_numeros_menos_sorteados(table);
                break;
            case 4:
                // Implementar a função que mostra a quantidade de concursos de um ano específico
                quantidade_concursos_ano(table);
                break;
            case 5:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (sub_option != 5);
}
