#include "score.h"
#include "player.h"
#include "obstacle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PONTUACOES 5

char **LerPontuacoes() {
    FILE *arquivo = fopen("pontuacoes.txt", "r");
    if (!arquivo) return NULL;

    char linha[100];
    char **pontuacoes = malloc(MAX_PONTUACOES * sizeof(char *));
    int total = 0;

    // Lê todas as pontuações
    int temp[MAX_PONTUACOES * 10];
    int count = 0;
    while (fgets(linha, sizeof(linha), arquivo) && count < MAX_PONTUACOES * 10) {
        int p = atoi(linha);
        if (p >= 0) temp[count++] = p;
    }
    fclose(arquivo);

    // Ordena em ordem decrescente (simples bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                int aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    // Prepara strings
    for (int i = 0; i < MAX_PONTUACOES && i < count; i++) {
        pontuacoes[i] = malloc(50);
        sprintf(pontuacoes[i], "%dº lugar: %d pontos", i + 1, temp[i]);
        total++;
    }

    // Preenche restante com NULL
    for (int i = total; i < MAX_PONTUACOES; i++)
        pontuacoes[i] = NULL;

    return pontuacoes;
}

void SalvarPontuacao(int pontos) {
    FILE *arquivo = fopen("pontuacoes.txt", "a");
    if (arquivo) {
        fprintf(arquivo, "%d\n", pontos);
        fclose(arquivo);
    }
}
