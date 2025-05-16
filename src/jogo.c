#include "raylib.h"
#include "score.h"
#include "player.h"
#include "obstacle.h"
#include "mapa.h"

int main() {
    InitWindow(800, 600, "STREET - Jogo Runner");
    SetTargetFPS(60);

    Mapa mapa;
    IniciarMapa(&mapa);

    Jogador jogador;
    IniciarJogador(&jogador);

    ListaObstaculos *obstaculos = CriarObstaculos();
    int pontos = 0;

    while (!WindowShouldClose()) {
        AtualizarMapa(&mapa);
        AtualizarJogador(&jogador);
        AtualizarObstaculos(obstaculos);

        if (VerificarColisao(&jogador, obstaculos)) {
            SalvarPontuacao(pontos);
            break;
        }

        pontos++;

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DesenharMapa(mapa);
        DesenharJogador(jogador);
        DesenharObstaculos(obstaculos);
        DrawText(TextFormat("Pontos: %d", pontos), 20, 20, 20, RAYWHITE);
        EndDrawing();
    }

    LiberarObstaculos(obstaculos);
    UnloadTexture(jogador.sprite);
    LiberarMapa(&mapa);
    CloseWindow();

    return 0;
}
