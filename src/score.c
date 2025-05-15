#include "score.h"
#include "player.h"
#include "obstacle.h"
#include <stdio.h>

void SalvarPontuacao(int pontos) {
    FILE *arquivo = fopen("pontuacoes.txt", "a");
    if (arquivo) {
        fprintf(arquivo, "%d\n", pontos);
        fclose(arquivo);
    }
}
