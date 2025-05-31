#include "obstacle.h"
#include "player.h"
#include "score.h"
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

// Retirado o extern Texture2D spriteObstaculo

int AleatorioEntre(int min, int max) {
    return min + rand() % (max - min + 1);
}

ListaObstaculos* CriarObstaculos() {
    ListaObstaculos *lista = malloc(sizeof(ListaObstaculos));
    lista->inicio = NULL;
    lista->contadorFrames = 0;
    return lista;
}

// Agora recebe Texture2D* para atribuir ao obstáculo
void AdicionarObstaculo(ListaObstaculos *lista, int pontos, Texture2D *sprite) {
    Obstaculo *novo = malloc(sizeof(Obstaculo));

    int alturaMax = 80 + pontos / 100;
    if (alturaMax > 180) alturaMax = 180;

    int altura = AleatorioEntre(40, alturaMax);
    int y = 730 - altura;

    novo->caixa = (Rectangle){1900, y, 40, altura};
    novo->velocidade = 4 + pontos / 150.0f;
    if (novo->velocidade > 10.0f) novo->velocidade = 10.0f;

    novo->frameAtual = AleatorioEntre(0, 1);  // frame 0 ou 1
    
    novo->sprite = sprite;  // Atribui a textura

    novo->proximo = lista->inicio;
    lista->inicio = novo;
}

// Agora recebe Texture2D* para passar ao criar obstáculo
void AtualizarObstaculos(ListaObstaculos *lista, int pontos, Texture2D *sprite) {
    lista->contadorFrames++;
    if (lista->contadorFrames >= 120) {
        AdicionarObstaculo(lista, pontos, sprite);
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
    for (Obstaculo *o = lista->inicio; o != NULL; o = o->proximo) {
        Rectangle frame = { 0, 0, 80, 32 };
        if (o->frameAtual == 1) frame.y = 32;

        Vector2 posicao = { o->caixa.x, o->caixa.y + o->caixa.height - 32 };
        // Usa o sprite individual do obstáculo
        DrawTextureRec(*o->sprite, frame, posicao, WHITE);
    }
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
