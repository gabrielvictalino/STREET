#include "obstacle.h"
#include "player.h"
#include "score.h"
#include <stdlib.h>

ListaObstaculos* CriarObstaculos() {
    ListaObstaculos *lista = malloc(sizeof(ListaObstaculos));
    lista->inicio = NULL;
    lista->contadorFrames = 0;
    return lista;
}

void AdicionarObstaculo(ListaObstaculos *lista) {
    Obstaculo *novo = malloc(sizeof(Obstaculo));
    novo->caixa = (Rectangle){800, 540, 40, 60};
    novo->proximo = lista->inicio;
    lista->inicio = novo;
}

void AtualizarObstaculos(ListaObstaculos *lista) {
    lista->contadorFrames++;
    if (lista->contadorFrames >= 120) {
        AdicionarObstaculo(lista);
        lista->contadorFrames = 0;
    }

    Obstaculo *atual = lista->inicio;
    Obstaculo *anterior = NULL;

    while (atual) {
        atual->caixa.x -= 4;

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
