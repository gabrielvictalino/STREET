#include "predio.h"
#include "raylib.h"

void IniciarPredio(Predio *predio, Texture2D sprite) {
    predio->sprite = sprite;
    predio->posicao = (Vector2){
        800,        // começa fora da tela, à direita
        320        // altura fixa (pode ajustar aqui o valor desejado)
    };
    predio->hitboxTopo = (Rectangle){
        predio->posicao.x,
        predio->posicao.y,
        110, 30  //largura do prédio, altura da área "pisável"
    };
    predio->ativo = true;// deixa ele pisável
}

void AtualizarPredio(Predio *predio) {
    predio->posicao.x -= 2;

    predio->hitboxTopo.x = predio->posicao.x;
    predio->hitboxTopo.y = predio->posicao.y;

    if (predio->posicao.x + 140 < 0) {
        predio->ativo = false;
    }
}

void DesenharPredio(Predio predio) {
    if (predio.ativo) {
        DrawTexture(predio.sprite, predio.posicao.x, predio.posicao.y, WHITE);// texturiza

    }
}

bool ColisaoComTopo(Predio predio, Rectangle jogador) {
    return predio.ativo && CheckCollisionRecs(predio.hitboxTopo, jogador);//calcula a colisão
}
