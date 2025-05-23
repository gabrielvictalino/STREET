#include "player.h"
#include "obstacle.h"
#include "score.h"
#include <stdio.h>

void IniciarJogador(Jogador *j) {
    j->posicao = (Vector2){100, 520};  // Ajustado para 80x80
    j->velocidade = 0; 
    j->pulos = 0;// inicia o contador de pulos

    // Carrega o sprite do personagem
    j->sprite = LoadTexture("spritesBoneco/boneco.png");

    // Define a caixa de colisão com o tamanho do frame (65x65)
    j->caixa = (Rectangle){j->posicao.x, j->posicao.y, 65, 65};

    // Inicializa a animação
    j->frameAtual = 0;
    j->frameContador = 0;
    j->frameVelocidade = 8; // FPS da animação
    j->totalFrames = 2;

    // Frame inicial: 80x80, frames na vertical
    j->frameRec = (Rectangle){0.0f, 0.0f, 80.0f, 80.0f};
}

void AtualizarJogador(Jogador *j) {
    // Pulo com limite de 2
    if (IsKeyPressed(KEY_SPACE) && j->pulos < 3) {
        j->velocidade = -12;
        j->pulos++;
    }
    if (IsKeyPressed(KEY_UP) && j->pulos < 3) {
        j->velocidade = -12;
        j->pulos++;
    }
    j->velocidade += 0.5f;
    j->posicao.y += j->velocidade;

    // Se o jogador tocar o chão
    if (j->posicao.y > 520) {
        j->posicao.y = 520;
        j->velocidade = 0;
        j->pulos = 0; // reseta o número de pulos
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

        j->frameRec.y = j->frameAtual * 80.0f; // frames na vertical
    }
}


void DesenharJogador(Jogador j) {
    // Desenha o frame atual
    DrawTextureRec(j.sprite, j.frameRec, j.posicao, WHITE);

    // Borda de debug (opcional)
    // DrawRectangleLines(j.posicao.x, j.posicao.y, 80, 80, GREEN);
}
