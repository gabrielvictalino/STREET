#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"

typedef struct Inimigo {
    Rectangle caixa;
    float velocidade;
    struct Inimigo *proximo;
} Inimigo;

Inimigo *CriarInimigo();
void AtualizarInimigos(Inimigo **lista);
void DesenharInimigos(Inimigo *lista);
void LiberarInimigos(Inimigo *lista);
bool VerificarColisaoComInimigos(Inimigo *lista, Rectangle jogador);

#endif
