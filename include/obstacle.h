#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"
#include "player.h"
#include <stdbool.h>

typedef struct Obstaculo {
    Rectangle caixa;
    float velocidade;
    int frameAtual;
    Texture2D *sprite;      // Ponteiro para textura usada no obstáculo
    struct Obstaculo *proximo;
} Obstaculo;

typedef struct {
    Obstaculo *inicio;
    int contadorFrames;
} ListaObstaculos;

// Cria a lista de obstáculos
ListaObstaculos* CriarObstaculos();

// Adiciona obstáculo à lista, recebe textura para o sprite
void AdicionarObstaculo(ListaObstaculos *lista, int pontos, Texture2D *sprite);

// Atualiza obstáculos, recebe textura para criar novos obstáculos
void AtualizarObstaculos(ListaObstaculos *lista, int pontos, Texture2D *sprite);

// Desenha todos os obstáculos da lista
void DesenharObstaculos(ListaObstaculos *lista);

// Verifica colisão entre jogador e obstáculos
bool VerificarColisao(Jogador *j, ListaObstaculos *lista);

// Libera a memória da lista de obstáculos
void LiberarObstaculos(ListaObstaculos *lista);

#endif // OBSTACLE_H