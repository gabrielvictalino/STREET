#include "enemy.h"
#include <stdlib.h>

Inimigo *CriarInimigo() {
    Inimigo *novo = malloc(sizeof(Inimigo));
    novo->caixa = (Rectangle){800, 480, 40, 60};  // pode pular depois
    novo->velocidade = 6.0f;
    novo->proximo = NULL;
    return novo;
}

void AtualizarInimigos(Inimigo **lista) {
    Inimigo *atual = *lista, *anterior = NULL;
    while (atual) {
        atual->caixa.x -= atual->velocidade;
        if (atual->caixa.x + atual->caixa.width < 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else *lista = atual->proximo;
            free(atual);
            atual = (anterior) ? anterior->proximo : *lista;
        } else {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    if (rand() % 120 == 0) {
        Inimigo *novo = CriarInimigo();
        novo->proximo = *lista;
        *lista = novo;
    }
}

void DesenharInimigos(Inimigo *lista) {
    while (lista) {
        DrawRectangleRec(lista->caixa, RED);
        lista = lista->proximo;
    }
}

bool VerificarColisaoComInimigos(Inimigo *lista, Rectangle jogador) {
    while (lista) {
        if (CheckCollisionRecs(lista->caixa, jogador)) return true;
        lista = lista->proximo;
    }
    return false;
}

void LiberarInimigos(Inimigo *lista) {
    while (lista) {
        Inimigo *tmp = lista;
        lista = lista->proximo;
        free(tmp);
    }
}
