#include "mapa.h"
#include <stdio.h>

void IniciarMapa(Mapa *m) {
    m->textura = LoadTexture("spritesMapa/mapa.png");

    if (m->textura.id == 0) {
        printf("Erro: Não foi possível carregar a textura do mapa!\n");
    }

    // Cada frame do sprite tem 800x800, mas exibiremos apenas 800x600
    m->frameLargura = 800;
    m->frameAltura = 800;
    m->totalFrames = 5;
    m->frameAtual = 0;
    Rectangle dest = { 0, 0, 1920, 1000 };

    m->frameRec = (Rectangle){ 0, 0, (float)m->frameLargura, (float)m->frameAltura };
    m->posicao = (Vector2){ 0, 0 };
}

void AtualizarMapa(Mapa *m) {
    static int contador = 0;
    contador++;

    if (contador >= 28) {  // troca de quadro a cada 0.5 segundos em 60 FPS
        contador = 0;
        m->frameAtual = (m->frameAtual + 1) % m->totalFrames;

        int coluna = m->frameAtual % 2;
        int linha = m->frameAtual / 2;

        m->frameRec.x = coluna * m->frameLargura;
        m->frameRec.y = linha * m->frameAltura;
    }
}

void DesenharMapa(Mapa m) {
    // Só desenhar os primeiros 600 pixels de altura do frame
    Rectangle frameVisivel = m.frameRec;
    frameVisivel.height = 800;

    Rectangle destino = { m.posicao.x, m.posicao.y, 1920, 1000 };

    DrawTexturePro(m.textura, frameVisivel, destino, (Vector2){0, 0}, 0.0f, WHITE);
}

void LiberarMapa(Mapa *m) {
    UnloadTexture(m->textura);
}
