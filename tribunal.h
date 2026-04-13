#ifndef TRIBUNAL_H
#define TRIBUNAL_H

typedef struct DadoTribunal
{
    char sigla_tribunal[20];
    char municipio_oj[150];
    int casos_novos, julgados, prim_sent, suspensos, dessobrestados;
    int distm2_a, julgm2_a, suspm2_a;
    int distm2_ant, julgm2_ant, suspm2_ant, desom2_ant;
    int distm4_a, julgm4_a, suspm4_a;
    int distm4_b, julgm4_b, suspm4_b;
    struct DadoTribunal *proximo;
} DadoTribunal;

void concatenarArquivos();
void carregarDados(DadoTribunal **lista);
void gerarResumoPorTribunal(DadoTribunal *lista);
void buscarPorMunicipio(DadoTribunal *lista, char *nomeMunicipio);
void inserir(DadoTribunal **l, DadoTribunal r);

#endif
