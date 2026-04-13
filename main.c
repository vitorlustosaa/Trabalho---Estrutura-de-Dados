#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tribunal.h"

int main()
{
    int opcao = 0;
    char municipio[100];
    DadoTribunal *minhaLista = NULL;

    do
    {
        printf("\n----------------------------------------------\n");
        printf("    SISTEMA DE MANIPULACAO DE DADOS - UCB\n");
        printf("----------------------------------------------\n");
        printf("1 - Concatenar e Carregar Dados\n");
        printf("2 - Gerar resumo por tribunal \n");
        printf("3 - Buscar por municipio \n");
        printf("0 - Sair\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }
        getchar();

        switch (opcao)
        {
        case 1:
            concatenarArquivos();

            carregarDados(&minhaLista);
            if (minhaLista != NULL)
            {
                printf("\nDados carregados com sucesso!\n");
            }
            else
            {
                printf("\nErro: A lista continua vazia. Verifique o arquivo base_unificada.csv\n");
            }
            break;

        case 2:
            if (minhaLista == NULL)
            {
                printf("\nErro: Carregue os dados primeiro (Opcao 1).\n");
            }
            else
            {
                gerarResumoPorTribunal(minhaLista);
            }
            break;

        case 3:
            if (minhaLista == NULL)
            {
                printf("\nErro: Carregue os dados primeiro.\n");
            }
            else
            {
                printf("\nDigite o nome do municipio (ex: MACAPA): ");

                fgets(municipio, sizeof(municipio), stdin);

                municipio[strcspn(municipio, "\n")] = 0;

                buscarPorMunicipio(minhaLista, municipio);
            }
            break;

        case 0:
            printf("Encerrando o sistema...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
