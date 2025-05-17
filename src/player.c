#include "player.h"
#include "obstacle.h"
#include "score.h"
#include <stdio.h>

void IniciarJogador(Jogador *j) {
    j->posicao = (Vector2){100, 568};
    j->velocidade = 0;

    // Carrega o sprite do personagem
    j->sprite = LoadTexture("spritesBoneco/New Piskel.png");

    // Define a caixa de colisão com o tamanho do frame
    j->caixa = (Rectangle){j->posicao.x, j->posicao.y, 32, 32};

    // Inicializa a animação
    j->frameAtual = 0;
    j->frameContador = 0;
    j->frameVelocidade = 8; // FPS da animação
    j->totalFrames = 2;

    // Frame inicial: 32x32, frames na vertical
    j->frameRec = (Rectangle){0.0f, 0.0f, 32.0f, 32.0f};
}

void AtualizarJogador(Jogador *j) {
    // Física do pulo
    if (IsKeyDown(KEY_SPACE) && j->posicao.y >= 300)
        j->velocidade = -12;

    j->velocidade += 0.5f;
    j->posicao.y += j->velocidade;

    if (j->posicao.y > 568) {
        j->posicao.y = 568;
        j->velocidade = 0;
    }

    // Atualiza a caixa de colisão
    j->caixa.x = j->posicao.x;
    j->caixa.y = j->posicao.y;

    // Animação do sprite
    j->frameContador++;
    if (j->frameContador >= (60 / j->frameVelocidade)) {
        j->frameContador = 0;
        j->frameAtual++;
        if (j->frameAtual >= j->totalFrames)
            j->frameAtual = 0;

        j->frameRec.y = j->frameAtual * 32.0f; // frames na vertical
    }
}

void DesenharJogador(Jogador j) {
    // Desenha o frame atual
    DrawTextureRec(j.sprite, j.frameRec, j.posicao, WHITE);

    // Borda de debug (opcional)
    // DrawRectangleLines(j.posicao.x, j.posicao.y, 32, 32, GREEN);
}
