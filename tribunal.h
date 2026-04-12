#ifndef TRIBUNAL_H
#define TRIBUNAL_H

typedef struct DadoTribunal {
    char sigla_tribunal[20];
    char procedimento[150];
    char ramo_justica[100];
    char sigla_grau[20];
    char uf_oj[10];
    char municipio_oj[150];
    int id_ultimo_oj;
    char nome[250];
    char mesano_cnm1[20];
    char mesano_sent[20];
    int casos_novos_2026, julgados_2026, prim_sent2026, suspensos_2026, dessobrestados_2026;
    float cumprimento_meta1; // Coluna 16
    
    // Campos para Metas 2 e 4 (Colunas 17 a 33)
    int distm2_a, julgm2_a, suspm2_a;
    float cumprimento_meta2a;
    int distm2_ant, julgm2_ant, suspm2_ant, desom2_ant;
    float cumprimento_meta2ant;
    int distm4_a, julgm4_a, suspm4_a;
    float cumprimento_meta4a;
    int distm4_b, julgm4_b, suspm4_b;
    float cumprimento_meta4b;

    struct DadoTribunal *proximo;
} DadoTribunal;

void concatenarArquivos();
void carregarDados(DadoTribunal **lista);
void gerarResumoPorTribunal(DadoTribunal *lista);
void buscarPorMunicipio(DadoTribunal *lista, char *nomeMunicipio);
void inserir(DadoTribunal **l, DadoTribunal r);

#endif
