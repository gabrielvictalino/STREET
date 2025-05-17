#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "raylib.h"
#include "player.h"

typedef struct Obstaculo {
    Rectangle caixa;
    float velocidade;
    struct Obstaculo *proximo;
} Obstaculo;

typedef struct {
    Obstaculo *inicio;
    int contadorFrames;
} ListaObstaculos;

ListaObstaculos* CriarObstaculos();
void AdicionarObstaculo(ListaObstaculos *lista, int pontos);
void AtualizarObstaculos(ListaObstaculos *lista, int pontos);
void DesenharObstaculos(ListaObstaculos *lista);
bool VerificarColisao(Jogador *j, ListaObstaculos *lista);
void LiberarObstaculos(ListaObstaculos *lista);

#endif
