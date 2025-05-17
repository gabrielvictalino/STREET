#include "obstacle.h"
#include "player.h"
#include "score.h"
#include <stdlib.h>
#include <time.h>

int AleatorioEntre(int min, int max) {
    return min + rand() % (max - min + 1);
}

ListaObstaculos* CriarObstaculos() {
    ListaObstaculos *lista = malloc(sizeof(ListaObstaculos));
    lista->inicio = NULL;
    lista->contadorFrames = 0;
    return lista;
}

void AdicionarObstaculo(ListaObstaculos *lista, int pontos) {
    Obstaculo *novo = malloc(sizeof(Obstaculo));

    // Aumenta a altura máxima com o tempo
    int alturaMax = 80 + pontos / 100;  // cresce a cada 100 pontos
    if (alturaMax > 180) alturaMax = 180;

    int altura = AleatorioEntre(40, alturaMax);
    int y = 600 - altura;

    novo->caixa = (Rectangle){800, y, 40, altura};

    // Aumenta a velocidade com o tempo
    novo->velocidade = 4 + pontos / 150.0f;  // mais rápido conforme pontua
    if (novo->velocidade > 10.0f) novo->velocidade = 10.0f;

    novo->proximo = lista->inicio;
    lista->inicio = novo;
}



void AtualizarObstaculos(ListaObstaculos *lista, int pontos) {
    lista->contadorFrames++;
    if (lista->contadorFrames >= 120) {
        AdicionarObstaculo(lista, pontos);
        lista->contadorFrames = 0;
    }

    Obstaculo *atual = lista->inicio;
    Obstaculo *anterior = NULL;

    while (atual) {
        atual->caixa.x -= atual->velocidade;

        if (atual->caixa.x < -40) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                lista->inicio = atual->proximo;

            Obstaculo *temp = atual;
            atual = atual->proximo;
            free(temp);
            continue;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}


void DesenharObstaculos(ListaObstaculos *lista) {
    for (Obstaculo *o = lista->inicio; o != NULL; o = o->proximo)
        DrawRectangleRec(o->caixa, ORANGE);
}

bool VerificarColisao(Jogador *j, ListaObstaculos *lista) {
    for (Obstaculo *o = lista->inicio; o != NULL; o = o->proximo)
        if (CheckCollisionRecs(j->caixa, o->caixa)) return true;
    return false;
}

void LiberarObstaculos(ListaObstaculos *lista) {
    Obstaculo *atual = lista->inicio;
    while (atual) {
        Obstaculo *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    free(lista);
}
