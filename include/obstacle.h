#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "raylib.h"
#include "player.h"

typedef struct Obstaculo {
    Rectangle caixa;
    struct Obstaculo *proximo;
} Obstaculo;

typedef struct {
    Obstaculo *inicio;
    int contadorFrames;
} ListaObstaculos;

ListaObstaculos* CriarObstaculos();
void AtualizarObstaculos(ListaObstaculos *lista);
void DesenharObstaculos(ListaObstaculos *lista);
bool VerificarColisao(Jogador *j, ListaObstaculos *lista);
void LiberarObstaculos(ListaObstaculos *lista);

#endif
