
// [OBSERVAÇÃO PARA O GRUPO - TAREFAS QUE AINDA TÊM QUE SER FEITAS]:
// 2. ITEM 2 (RESUMO): Criar a lógica para calcular as Metas 1, 2A, 2Ant, 4A e 4B usando as fórmulas do PDF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tribunal.h" 


void inicializar(DadoTribunal **l) {
    *l = NULL;
}

void inserir(DadoTribunal **l, DadoTribunal r) {
    DadoTribunal *novo = (DadoTribunal*) malloc(sizeof(DadoTribunal));
    *novo = r;
    novo->proximo = *l; 
    *l = novo;
}


void concatenarArquivos() {
    char arquivos[][100] = {"dados1.csv", "dados2.csv", "dados3.csv"}; 
    FILE *saida = fopen("base_unificada.csv", "w");
    char linha[2000];

    for (int i = 0; i < 3; i++) {
        FILE *f = fopen(arquivos[i], "r");
        if (!f) continue;

        int primeiraLinha = 1;
        while (fgets(linha, sizeof(linha), f)) {
        
            if (i > 0 && primeiraLinha) {
                primeiraLinha = 0;
                continue;
            }
            fprintf(saida, "%s", linha);
            primeiraLinha = 0;
        }
        fclose(f);
    }
    fclose(saida);
    printf("Item 1 Concluido: Arquivos unificados em base_unificada.csv\n");
}


void buscarPorMunicipio(DadoTribunal *lista, char *municipio) {
    FILE *f = fopen("resultado_busca.csv", "w");
    DadoTribunal *p = lista;

    while (p) {
      
        if (strcmp(p->municipio, municipio) == 0) {
         
            fprintf(f, "%s;%s;%d;%d\n", 
                p->sigla_tribunal, 
                p->municipio, 
                p->julgados_2026, 
                p->casos_novos_2026);
        }
        p = p->proximo;
    }
    fclose(f);
    printf("Item 3 Concluido: Arquivo de busca gerado!\n");
}


void gerarResumoPorTribunal(DadoTribunal *lista) {
    FILE *f = fopen("resumo_metas.csv", "w");
    DadoTribunal *p = lista;

  
    fprintf(f, "Tribunal;Meta1;Meta2A;Meta2Ant;Meta4A;Meta4B\n");

    while (p) {
     
        float meta1 = ((float)p->julgados_2026 / (p->casos_novos_2026 + p->suspensos_2026 + p->dessobrestados_2026)) * 100;

       
        fprintf(f, "%s;%.2f%%;0.00;0.00;0.00;0.00\n", p->sigla_tribunal, meta1);
        p = p->proximo;
    }
    fclose(f);
    printf("Item 2 Parcial: Meta 1 gerada. Grupo deve completar as outras 4 fórmulas.\n");
}
