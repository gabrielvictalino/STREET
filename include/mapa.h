#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"

typedef struct {
    Texture2D textura;
    Rectangle frameRec;
    int frameAtual;
    int totalFrames;
    int frameLargura;
    int frameAltura;
    Vector2 posicao;
} Mapa;

void IniciarMapa(Mapa *m);
void AtualizarMapa(Mapa *m);
void DesenharMapa(Mapa m);
void LiberarMapa(Mapa *m);

#endif
