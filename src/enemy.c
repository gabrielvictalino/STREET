#include "enemy.h"
#include <stdlib.h>

static Texture2D texturaInimigo = { 0 };  // Inicializa com zeros

Inimigo *CriarInimigo() {
    Inimigo *novo = (Inimigo *)malloc(sizeof(Inimigo));
    if (novo) {
        novo->caixa.x = GetScreenWidth();
        novo->caixa.y = 380;
        novo->caixa.width = 80;
        novo->caixa.height = 80;
        novo->velocidade = 4.0f;
        novo->frameAtual = 0;
        novo->contadorFrames = 0;
        novo->proximo = NULL;
    }
    return novo;
}

void AtualizarInimigos(Inimigo **lista) {
    Inimigo *atual = *lista;
    Inimigo *anterior = NULL;

    while (atual) {
        atual->caixa.x -= atual->velocidade;

        // Animação simples: alterna a cada 15 frames
        atual->contadorFrames++;
        if (atual->contadorFrames >= 15) {
            atual->frameAtual = 1 - atual->frameAtual;  // Alterna entre 0 e 1
            atual->contadorFrames = 0;
        }

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
        Rectangle frame = {
            0,
            atual->frameAtual * 80,  // y = 0 ou y = 80
            80,
            80
        };
        DrawTextureRec(
            texturaInimigo,
            frame,
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
