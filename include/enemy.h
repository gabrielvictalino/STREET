#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

// Estrutura que representa um inimigo na lista encadeada
typedef struct Inimigo {
    Rectangle caixa;
    float velocidade;
    struct Inimigo *proximo;
} Inimigo;

// Cria um inimigo novo, posicionando na borda direita da tela
Inimigo *CriarInimigo();

// Atualiza a posição dos inimigos e remove os que saíram da tela
void AtualizarInimigos(Inimigo **lista);

// Desenha todos os inimigos usando a textura carregada
void DesenharInimigos(Inimigo *lista);

// Libera a lista de inimigos da memória
void LiberarInimigos(Inimigo *lista);

// Verifica colisão entre o jogador e qualquer inimigo da lista
bool VerificarColisaoComInimigos(Inimigo *lista, Rectangle jogador);

// Carrega a textura do inimigo (deve ser chamada antes de usar os inimigos)
void CarregarTexturaInimigo(const char *caminho);

// Descarrega a textura do inimigo (deve ser chamada ao finalizar o jogo)
void DescarregarTexturaInimigo();

#endif // ENEMY_H
