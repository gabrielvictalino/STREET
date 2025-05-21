#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

typedef struct {
    Vector2 posicao;
    float velocidade;
    Rectangle caixa;

    // Animação
    Texture2D sprite;
    Rectangle frameRec;
    int frameAtual;
    int frameContador;
    int frameVelocidade;
    int totalFrames;
    int pulos;
} Jogador;

void IniciarJogador(Jogador *j);
void AtualizarJogador(Jogador *j);
void DesenharJogador(Jogador j);

#endif
