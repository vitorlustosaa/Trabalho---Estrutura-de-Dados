
// [OBSERVAÇÃO PARA O GRUPO]:
// 1. MENU: (vitor) já estruturei o switch/case para chamar as funções obrigatórias
// 2. ENTRADA: (vitor) usei 'gets' para capturar nomes de municípios com espaços (ex: MACAPA)

#include <stdio.h>
#include <stdlib.h>
#include "tribunal.h"

int main()
{

    int opcao = 0;
    char municipio[100];
    DadoTribunal *minhaLista = NULL; // Inicializa a lista do TAD como vazia

    do
    {
        printf("\n----------------------------------------------\n");
        printf("   SISTEMA DE MANIPULACAO DE DADOS - UCB\n");
        printf("----------------------------------------------\n");
        printf("1 - Concatenar arquivos (.csv)\n");
        printf("2 - Gerar resumo por tribunal\n");
        printf("3 - Buscar por municipio\n");
        printf("0 - Sair\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\nIniciando concatenacao de arquivos...\n");
            concatenarArquivos(); // Chamada da função 
            break;

        case 2:
            printf("\nGerando resumo das metas por tribunal...\n");
            gerarResumoPorTribunal(minhaLista); // Chamada da função 
            break;

        case 3:
            printf("\nDigite o nome do municipio (ex: MACAPA): ");
            gets(municipio);                           // Lê o nome do municipio com espaços 
            buscarPorMunicipio(minhaLista, municipio); // Chamada da função 
            break;

        case 0:
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
