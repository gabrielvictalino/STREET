#include "player.h"
#include "obstacle.h"
#include "score.h"

void IniciarJogador(Jogador *j) {
    j->posicao = (Vector2){100, 500};
    j->velocidade = 0;
    j->caixa = (Rectangle){100, 500, 40, 40};
}

void AtualizarJogador(Jogador *j) {
    if (IsKeyDown(KEY_SPACE) && j->posicao.y >= 500)
        j->velocidade = -12;

    j->velocidade += 0.5f;
    j->posicao.y += j->velocidade;

    if (j->posicao.y > 500) {
        j->posicao.y = 500;
        j->velocidade = 0;
    }

    j->caixa.y = j->posicao.y;
}

void DesenharJogador(Jogador j) {
    DrawRectangleRec(j.caixa, RED);
}
