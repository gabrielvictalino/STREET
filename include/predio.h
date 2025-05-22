#ifndef PREDIO_H
#define PREDIO_H

#include "raylib.h"

typedef struct Predio {
    Vector2 posicao;
    Rectangle hitboxTopo;
    Texture2D sprite;
    bool ativo;
} Predio;

void IniciarPredio(Predio *predio, Texture2D sprite);
void AtualizarPredio(Predio *predio);
void DesenharPredio(Predio predio);
bool ColisaoComTopo(Predio predio, Rectangle jogador);

#endif
