
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tribunal.h"

// Inicializa a lista como vazia
void inicializar(DadoTribunal **l) {
    *l = NULL;
}

// Insere um novo registro no início da lista encadeada
void inserir(DadoTribunal **l, DadoTribunal r) {
    DadoTribunal *novo = (DadoTribunal*) malloc(sizeof(DadoTribunal));
    if (novo == NULL) return;
    *novo = r;
    novo->proximo = *l;
    *l = novo;
}

// Une os arquivos CSV do disco em um arquivo único
void concatenarArquivos() {
    char arquivos[][100] = {
        "teste_TRE-AC.csv", "teste_TRE-AL.csv", "teste_TRE-AM.csv",
        "teste_TRE-AP.csv", "teste_TRE-BA.csv", "teste_TRE-CE.csv",
        "teste_TRE-DF.csv", "teste_TRE-ES.csv", "teste_TRE-GO.csv",
        "teste_TRE-MA.csv", "teste_TRE-MG.csv", "teste_TRE-MS.csv",
        "teste_TRE-MT.csv", "teste_TRE-PA.csv", "teste_TRE-PB.csv",
        "teste_TRE-PE.csv", "teste_TRE-PI.csv", "teste_TRE-PR.csv",
        "teste_TRE-RJ.csv", "teste_TRE-RN.csv", "teste_TRE-RO.csv",
        "teste_TRE-RR.csv", "teste_TRE-RS.csv", "teste_TRE-SC.csv",
        "teste_TRE-SE.csv", "teste_TRE-SP.csv", "teste_TRE-TO.csv"
    };
    int totalArquivos = 27;

    FILE *saida = fopen("base_unificada.csv", "w");
    if (!saida) return;

    char linha[2000];
    for (int i = 0; i < totalArquivos; i++) {
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
    printf("Item 1: Arquivos unificados com sucesso!\n");
}


void carregarDados(DadoTribunal **lista) {
    FILE *f = fopen("base_unificada.csv", "r");
    if (!f) return;

    char linha[2048];
    DadoTribunal r;
    int contador = 0;

    fgets(linha, sizeof(linha), f); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), f)) {
        // O formato \"%[^\"]\" serve para ler o texto dentro das aspas do CSV
        if (sscanf(linha, "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%d,\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%d,%d,%d,%d,%d",
               r.sigla_tribunal, r.procedimento, r.ramo_justica,
               r.sigla_grau, r.uf_oj, r.municipio_oj,
               &r.id_ultimo_oj, r.nome, r.mesano_cnm1,
               r.mesano_sent, &r.casos_novos_2026, &r.julgados_2026,
               &r.prim_sent2026, &r.suspensos_2026, &r.dessobrestados_2026) >= 10) {
            
            inserir(lista, r);
            contador++;
        }
    }
    fclose(f);
    printf("Item 1.1: %d registros carregados na memoria!\n", contador);
}

// Gera o relatório de metas (Exemplo Meta 1)
void gerarResumoPorTribunal(DadoTribunal *lista) {
    FILE *f = fopen("resumo_metas.csv", "w");
    if (!f) return;

    fprintf(f, "Tribunal;Meta1;Meta2A;Meta2Ant;Meta4A;Meta4B\n");
    DadoTribunal *p = lista;

    while (p) {
        float m1 = 0;
        float den1 = (p->casos_novos_2026 + p->suspensos_2026 + p->dessobrestados_2026);
        if (den1 != 0) m1 = ((float)p->julgados_2026 / den1) * 100;

        fprintf(f, "%s;%.2f%%;0.00;0.00;0.00;0.00\n", p->sigla_tribunal, m1);
        p = p->proximo;
    }
    fclose(f);
    printf("Item 2: Relatorio 'resumo_metas.csv' gerado!\n");
}

// Busca por município ignorando maiúsculas/minúsculas
void buscarPorMunicipio(DadoTribunal *lista, char *municipio) {
    FILE *f = fopen("resultado_busca.csv", "w");
    if (!f) return;

    DadoTribunal *p = lista;
    int encontradas = 0;

    while (p) {
        // strcasecmp resolve o problema de digitar minusculo
        if (strcasecmp(p->municipio_oj, municipio) == 0) {
            fprintf(f, "\"%s\",\"%s\",%d,%d\n", 
                p->sigla_tribunal, p->municipio_oj, p->julgados_2026, p->casos_novos_2026);
            encontradas++;
        }
        p = p->proximo;
    }
    fclose(f);
    printf("Item 3: %d ocorrencias encontradas para '%s' e salvas no ficheiro!\n", encontradas, municipio);
}
