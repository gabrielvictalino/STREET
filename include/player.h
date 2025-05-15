#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

typedef struct {
    Vector2 posicao;
    float velocidade;
    Rectangle caixa;
} Jogador;

void IniciarJogador(Jogador *j);
void AtualizarJogador(Jogador *j);
void DesenharJogador(Jogador j);

#endif
