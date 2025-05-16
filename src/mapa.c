#include "mapa.h"
#include <stdio.h>

void IniciarMapa(Mapa *m) {
    m->textura = LoadTexture("spritesMapa/mapa.png");

    if (m->textura.id == 0) {
        printf("Erro: Não foi possível carregar a textura do mapa!\n");
    }

    m->frameLargura = 800;
    m->frameAltura = 600;
    m->totalFrames = 4;
    m->frameAtual = 0;

    m->frameRec = (Rectangle){ 0, 0, (float)m->frameLargura, (float)m->frameAltura };
    m->posicao = (Vector2){ 0, 0 };
}

void AtualizarMapa(Mapa *m) {
    static int contador = 0;
    contador++;

    if (contador >= 30) {  // troca de quadro a cada 2 segundos (60 FPS)
        contador = 0;
        m->frameAtual = (m->frameAtual + 1) % m->totalFrames;

        int coluna = m->frameAtual % 2;
        int linha = m->frameAtual / 2;

        m->frameRec.x = coluna * m->frameLargura;
        m->frameRec.y = linha * m->frameAltura;
    }
}

void DesenharMapa(Mapa m) {
    DrawTextureRec(m.textura, m.frameRec, m.posicao, WHITE);
}

void LiberarMapa(Mapa *m) {
    UnloadTexture(m->textura);
}
