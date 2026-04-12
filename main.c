#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tribunal.h"

int main() {
    int opcao = 0;
    char municipio[100];
    DadoTribunal *minhaLista = NULL;

    do {
        printf("\n----------------------------------------------\n");
        printf("   SISTEMA DE MANIPULACAO DE DADOS - UCB\n");
        printf("----------------------------------------------\n");
        printf("1 - Concatenar e Carregar Dados\n");
        printf("2 - Gerar resumo por tribunal\n");
        printf("3 - Buscar por municipio\n");
        printf("0 - Sair\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar(); // Limpa o buffer para o gets() funcionar

        switch (opcao) {
            case 1:
                concatenarArquivos();
                carregarDados(&minhaLista);
                break;
            case 2:
                if (minhaLista == NULL) printf("\nErro: Carregue os dados primeiro (Opcao 1).\n");
                else gerarResumoPorTribunal(minhaLista);
                break;
         case 3:
                if (minhaLista == NULL) printf("\nErro: Carregue os dados primeiro.\n");
                else {
                    printf("\nDigite o nome do municipio (ex: MACAPA): ");
                    // O gets() le ate o final da linha. Se nao encontrar nada, tente limpar o buffer:
                    // fflush(stdin); // No Windows pode ajudar
                    gets(municipio);
                    buscarPorMunicipio(minhaLista, municipio);
                }
                break;
            case 0:
                printf("Encerrando...\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
