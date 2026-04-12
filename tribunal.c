#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tribunal.h"

void inicializar(DadoTribunal **l) {
    *l = NULL;
}

void inserir(DadoTribunal **l, DadoTribunal r) {
    DadoTribunal *novo = (DadoTribunal*) malloc(sizeof(DadoTribunal));
    if (novo == NULL) return;
    *novo = r;
    novo->proximo = *l;
    *l = novo;
}

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
    int total = 27;
    FILE *saida = fopen("base_unificada.csv", "w");
    if (!saida) return;

    char linha[4096];
    for (int i = 0; i < total; i++) {
        FILE *f = fopen(arquivos[i], "r");
        if (!f) continue;
        int primeira = 1;
        while (fgets(linha, sizeof(linha), f)) {
            if (i > 0 && primeira) { primeira = 0; continue; }
            fprintf(saida, "%s", linha);
            primeira = 0;
        }
        fclose(f);
    }
    fclose(saida);
    printf("Item 1: Arquivos unificados!\n");
}

void carregarDados(DadoTribunal **lista) {
    FILE *f = fopen("base_unificada.csv", "r");
    if (!f) return;

    char linha[4096];
    DadoTribunal r;
    int contador = 0;
    
    fgets(linha, sizeof(linha), f); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), f)) {
        // Esta máscara lê as 33 colunas. O %*[^,] pula as colunas de 'cumprimento' que já existem no arquivo.
        int lidos = sscanf(linha, 
            "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%d,\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%d,%d,%d,%d,%d,%*[^,],%d,%d,%d,%*[^,],%d,%d,%d,%d,%*[^,],%d,%d,%d,%*[^,],%d,%d,%d,%*[^,]",
            r.sigla_tribunal, r.procedimento, r.ramo_justica, r.sigla_grau, r.uf_oj, r.municipio_oj, 
            &r.id_ultimo_oj, r.nome, r.mesano_cnm1, r.mesano_sent, 
            &r.casos_novos_2026, &r.julgados_2026, &r.prim_sent2026, &r.suspensos_2026, &r.dessobrestados_2026,
            &r.distm2_a, &r.julgm2_a, &r.suspm2_a, 
            &r.distm2_ant, &r.julgm2_ant, &r.suspm2_ant, &r.desom2_ant,
            &r.distm4_a, &r.julgm4_a, &r.suspm4_a,
            &r.distm4_b, &r.julgm4_b, &r.suspm4_b);

        if (lidos >= 10) { 
            inserir(lista, r);
            contador++;
        }
    }
    fclose(f);
    printf("Item 1.1: %d registros carregados!\n", contador);
}

void gerarResumoPorTribunal(DadoTribunal *lista) {
    FILE *f = fopen("resumo_metas.csv", "w");
    if (!f) return;

    fprintf(f, "Tribunal,Meta1,Meta2A,Meta2Ant,Meta4A,Meta4B\n");
    DadoTribunal *p = lista;

    while (p) {
        float m1=0, m2a=0, m2ant=0, m4a=0, m4b=0;

        // Meta 1
        float den1 = (float)(p->casos_novos_2026 + p->suspensos_2026 + p->dessobrestados_2026);
        if (den1 != 0) m1 = ((float)p->julgados_2026 / den1) * 100;

        // Meta 2A
        float den2a = (float)(p->distm2_a + p->suspm2_a);
        if (den2a != 0) m2a = ((float)p->julgm2_a / den2a) * (1000.0 / 7.0);

        // Meta 2Ant
        float den2ant = (float)(p->distm2_ant + p->suspm2_ant + p->desom2_ant);
        if (den2ant != 0) m2ant = ((float)p->julgm2_ant / den2ant) * 100;

        // Meta 4A
        float den4a = (float)(p->distm4_a - p->suspm4_a);
        if (den4a != 0) m4a = ((float)p->julgm4_a / den4a) * 100;

        // Meta 4B
        float den4b = (float)(p->distm4_b - p->suspm4_b);
        if (den4b != 0) m4b = ((float)p->julgm4_b / den4b) * 100;

        fprintf(f, "%s,%.2f%%,%.2f%%,%.2f%%,%.2f%%,%.2f%%\n", 
                p->sigla_tribunal, m1, m2a, m2ant, m4a, m4b);
        p = p->proximo;
    }
    fclose(f);
    printf("Item 2: Relatorio gerado! Verifique o arquivo resumo_metas.csv\n");
}

void buscarPorMunicipio(DadoTribunal *lista, char *municipio) {
    char nomeArq[150];
    sprintf(nomeArq, "%s.csv", municipio);
    FILE *f = fopen(nomeArq, "w");
    if (!f) return;

    DadoTribunal *p = lista;
    int n = 0;
    while (p) {
        if (strcasecmp(p->municipio_oj, municipio) == 0) {
            fprintf(f, "\"%s\",\"%s\",%d,%d\n", 
                p->sigla_tribunal, p->municipio_oj, p->julgados_2026, p->casos_novos_2026);
            n++;
        }
        p = p->proximo;
    }
    fclose(f);
    printf("Item 3: %d registros salvos em %s\n", n, nomeArq);
}
