
// [OBSERVAÇÃO PARA O GRUPO - TAREFAS QUE AINDA TÊM QUE SER FEITAS]:
// 1. ITEM 1 (CONCATENAR): Implementar leitura de arquivos e gerar o arquivo unificado "csv"
// 2. ITEM 2 (RESUMO): Criar a lógica para calcular as Metas 1, 2A, 2Ant, 4A e 4B usando as fórmulas do PDF
// 3. ITEM 3 (BUSCA): Implementar a busca na lista pelo município informado e salvar em um novo arquivo .csv

// 5. BIBLIOTECA: Usem 'string.h' para comparar os nomes dos tribunais e municípios

#include <stdio.h>
#include <stdlib.h>
#include "tribunal.h" 

void inicializar(DadoTribunal **l)
{
    *l = NULL;
}


void inserir(DadoTribunal **l, DadoTribunal r)
{
    DadoTribunal *novo = (DadoTribunal *)malloc(sizeof(DadoTribunal));
    *novo = r;
    novo->proximo = *l; 
    *l = novo;
}
