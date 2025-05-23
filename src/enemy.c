#include "enemy.h"
#include <stdlib.h>

static Texture2D texturaInimigo = { 0 };  // Inicializa com zeros

Inimigo *CriarInimigo() {
    Inimigo *novo = (Inimigo *)malloc(sizeof(Inimigo));
    if (novo) {
        novo->caixa.x = GetScreenWidth();
        novo->caixa.y = 380;  // Ajuste conforme necessário
        novo->caixa.width = 80;
        novo->caixa.height = 80;
        novo->velocidade = 4.0f;
        novo->proximo = NULL;
    }
    return novo;
}

void AtualizarInimigos(Inimigo **lista) {
    Inimigo *atual = *lista;
    Inimigo *anterior = NULL;

    while (atual) {
        atual->caixa.x -= atual->velocidade;

        if (atual->caixa.x + atual->caixa.width < 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                *lista = atual->proximo;
            }
            Inimigo *remover = atual;
            atual = atual->proximo;
            free(remover);
        } else {
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

void DesenharInimigos(Inimigo *lista) {
    Inimigo *atual = lista;
    while (atual) {
        DrawTextureRec(
            texturaInimigo,
            (Rectangle){ 0, 0, 80, 80 },
            (Vector2){ atual->caixa.x, atual->caixa.y },
            WHITE
        );
        atual = atual->proximo;
    }
}

void LiberarInimigos(Inimigo *lista) {
    while (lista) {
        Inimigo *temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

bool VerificarColisaoComInimigos(Inimigo *lista, Rectangle jogador) {
    Inimigo *atual = lista;
    while (atual) {
        if (CheckCollisionRecs(jogador, atual->caixa)) {
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

void CarregarTexturaInimigo(const char *caminho) {
    // Se textura já estiver carregada, descarrega para evitar vazamento
    if (texturaInimigo.id != 0) {
        UnloadTexture(texturaInimigo);
    }
    texturaInimigo = LoadTexture(caminho);
}

void DescarregarTexturaInimigo() {
    if (texturaInimigo.id != 0) {
        UnloadTexture(texturaInimigo);
        texturaInimigo.id = 0;
    }
}
