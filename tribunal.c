
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tribunal.h"

// Função auxiliar para tratar campos "NA" ou vazios
int converterCampo(char *campo)
{
    if (campo == NULL || strcmp(campo, "NA") == 0 || strcmp(campo, "\"NA\"") == 0 || strlen(campo) == 0)
    {
        return 0;
    }
    // Remove aspas se sobrarem no campo
    if (campo[0] == '\"')
    {
        char limpo[20];
        sscanf(campo, "\"%[^\"]\"", limpo);
        return atoi(limpo);
    }
    return atoi(campo);
}

void inserir(DadoTribunal **l, DadoTribunal r)
{
    DadoTribunal *novo = (DadoTribunal *)malloc(sizeof(DadoTribunal));
    if (novo == NULL)
        return;
    *novo = r;
    novo->proximo = *l;
    *l = novo;
}

void concatenarArquivos()
{
    char *ufs[] = {"AC", "AL", "AM", "AP", "BA", "CE", "DF", "ES", "GO", "MA", "MG", "MS", "MT", "PA", "PB", "PE", "PI", "PR", "RJ", "RN", "RO", "RR", "RS", "SC", "SE", "SP", "TO"};
    FILE *saida = fopen("base_unificada.csv", "w");
    if (!saida)
        return;

    char linha[4096], nomeArq[50];

    for (int i = 0; i < 27; i++)
    {
        sprintf(nomeArq, "teste_TRE-%s.csv", ufs[i]);
        FILE *f = fopen(nomeArq, "r");
        if (!f)
            continue;

        int primeiraLinha = 1;
        while (fgets(linha, sizeof(linha), f))
        {
            if (i > 0 && primeiraLinha)
            {
                primeiraLinha = 0;
                continue;
            }
            fprintf(saida, "%s", linha);
            primeiraLinha = 0;
        }
        fclose(f);
    }
    fclose(saida);
}

void carregarDados(DadoTribunal **lista)
{
    FILE *f = fopen("base_unificada.csv", "r");
    if (!f)
        return;

    char linha[4096];
    char t[20][50];
    DadoTribunal r;

    fgets(linha, sizeof(linha), f); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), f))
    {
        // Leitura tratando as aspas e vírgulas para evitar erro no "NA"
        int lidos = sscanf(linha,
                           "\"%[^\"]\",\"%*[^\"]\",\"%*[^\"]\",\"%*[^\"]\",\"%*[^\"]\",\"%[^\"]\",%*[^,],\"%*[^\"]\",\"%*[^\"]\",\"%*[^\"]\",%[^,],%[^,],%[^,],%[^,],%[^,],%*[^,],%[^,],%[^,],%[^,],%*[^,],%[^,],%[^,],%[^,],%[^,],%*[^,],%[^,],%[^,],%[^,],%*[^,],%[^,],%[^,],%[^,]",
                           r.sigla_tribunal, r.municipio_oj,
                           t[0], t[1], t[2], t[3], t[4],
                           t[5], t[6], t[7],
                           t[8], t[9], t[10], t[11],
                           t[12], t[13], t[14],
                           t[15], t[16], t[17]);

        if (lidos >= 5)
        {
            r.casos_novos = converterCampo(t[0]);
            r.julgados = converterCampo(t[1]);
            r.prim_sent = converterCampo(t[2]);
            r.suspensos = converterCampo(t[3]);
            r.dessobrestados = converterCampo(t[4]);
            r.distm2_a = converterCampo(t[5]);
            r.julgm2_a = converterCampo(t[6]);
            r.suspm2_a = converterCampo(t[7]);
            r.distm2_ant = converterCampo(t[8]);
            r.julgm2_ant = converterCampo(t[9]);
            r.suspm2_ant = converterCampo(t[10]);
            r.desom2_ant = converterCampo(t[11]);
            r.distm4_a = converterCampo(t[12]);
            r.julgm4_a = converterCampo(t[13]);
            r.suspm4_a = converterCampo(t[14]);
            r.distm4_b = converterCampo(t[15]);
            r.julgm4_b = converterCampo(t[16]);
            r.suspm4_b = converterCampo(t[17]);

            inserir(lista, r);
        }
    }
    fclose(f);
}

void gerarResumoPorTribunal(DadoTribunal *lista)
{
    FILE *f = fopen("resumo_metas.csv", "w");
    char *tribunais[] = {"TRE-AC", "TRE-AL", "TRE-AM", "TRE-AP", "TRE-BA", "TRE-CE", "TRE-DF", "TRE-ES", "TRE-GO", "TRE-MA", "TRE-MG", "TRE-MS", "TRE-MT", "TRE-PA", "TRE-PB", "TRE-PE", "TRE-PI", "TRE-PR", "TRE-RJ", "TRE-RN", "TRE-RO", "TRE-RR", "TRE-RS", "TRE-SC", "TRE-SE", "TRE-SP", "TRE-TO"};

    fprintf(f, "Tribunal;Meta1;Meta2A;Meta2Ant;Meta4A;Meta4B\n");

    for (int i = 0; i < 27; i++)
    {
        long cn = 0, ju = 0, su = 0, de = 0, d2a = 0, j2a = 0, s2a = 0, d2ant = 0, j2ant = 0, s2ant = 0, de2ant = 0, d4a = 0, j4a = 0, s4a = 0, d4b = 0, j4b = 0, s4b = 0;
        DadoTribunal *p = lista;
        while (p)
        {
            if (strcmp(p->sigla_tribunal, tribunais[i]) == 0)
            {
                cn += p->casos_novos;
                ju += p->julgados;
                su += p->suspensos;
                de += p->dessobrestados;
                d2a += p->distm2_a;
                j2a += p->julgm2_a;
                s2a += p->suspm2_a;
                d2ant += p->distm2_ant;
                j2ant += p->julgm2_ant;
                s2ant += p->suspm2_ant;
                de2ant += p->desom2_ant;
                d4a += p->distm4_a;
                j4a += p->julgm4_a;
                s4a += p->suspm4_a;
                d4b += p->distm4_b;
                j4b += p->julgm4_b;
                s4b += p->suspm4_b;
            }
            p = p->proximo;
        }

        float m1 = 0, m2a = 0, m2ant = 0, m4a = 0, m4b = 0;
        if ((cn + su + de) != 0)
            m1 = ((float)ju / (cn + su + de)) * 100;
        if ((d2a + s2a) != 0)
            m2a = ((float)j2a / (d2a + s2a)) * 100;
        if ((d2ant + s2ant + de2ant) != 0)
            m2ant = ((float)j2ant / (d2ant + s2ant + de2ant)) * 100;
        if ((d4a - s4a) != 0)
            m4a = ((float)j4a / (d4a - s4a)) * 100;
        if ((d4b - s4b) != 0)
            m4b = ((float)j4b / (d4b - s4b)) * 100;

        fprintf(f, "%s;%.2f%%;%.2f%%;%.2f%%;%.2f%%;%.2f%%\n", tribunais[i], m1, m2a, m2ant, m4a, m4b);
    }
    fclose(f);
}

void buscarPorMunicipio(DadoTribunal *lista, char *municipio)
{
    char nomeArq[150];
  sprintf(nomeArq, "%s.csv", municipio);
    FILE *f = fopen(nomeArq, "w");
    DadoTribunal *p = lista;
    while (p)
    {
        if (strcasecmp(p->municipio_oj, municipio) == 0)
        {
            fprintf(f, "%s;%s;%d;%d\n", p->sigla_tribunal, p->municipio_oj, p->julgados, p->casos_novos);
        }
        p = p->proximo;
    }
    fclose(f);
}
