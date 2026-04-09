#ifndef TRIBUNAL_H
#define TRIBUNAL_H

// [OBSERVAÇÃO PARA O GRUPO]:
// 1. NÃO ALTERAR OS NOMES DOS CAMPOS NA STRUCT - Eles seguem a ordem exata do PDF
// 2. TAD LISTA: O ponteiro 'proximo' já está criado; usem ele para a lista encadeada
// 3. SEPARADOR: Lembrem-se que o arquivo CSV usa ponto e vírgula (;) como separador

typedef struct DadoTribunal
{
    // Definição da estrutura com base nos 33 campos do PDF
    char sigla_tribunal[10];
    char procedimento[100];
    char ramo_justica[50];
    char sigla_grau[10];
    char uf_oj[5];
    char municipio_oj[100];
    int id_ultimo_oj;
    char nome[200];
    char mesano_cnm1[10];
    char mesano_sent[10];

    // Campos numéricos para cálculos das Metas (11 a 33)
    int casos_novos_2026;
    int julgados_2026;
    int prim_sent2026;
    int suspensos_2026;
    int dessobrestados_2026;
    float cumprimento_meta1;
    int distm2_a;
    int julgm2_a;
    int suspm2_a;
    float cumprimento_meta2a;
    int distm2_ant;
    int julgm2_ant;
    int suspm2_ant;
    int desom2_ant;
    float cumprimento_meta2ant;
    int distm4_a;
    int julgm4_a;
    int suspm4_a;
    float cumprimento_meta4a;
    int distm4_b;
    int julgm4_b;
    int suspm4_b;
    float cumprimento_meta4b;

    struct DadoTribunal *proximo; // Ponteiro para o próximo elemento da lista encadeada
} DadoTribunal;

// Protótipos das funções obrigatórias
void concatenarArquivos();                                         // Item 1
void gerarResumoPorTribunal(DadoTribunal *lista);                  // Item 2
void buscarPorMunicipio(DadoTribunal *lista, char *nomeMunicipio); // Item 3

#endif
