#include "raylib.h"
#include "score.h"
#include "player.h"
#include "obstacle.h"

int main() {
    InitWindow(800, 600, "STREET - Jogo Runner");
    SetTargetFPS(60);

    Jogador jogador;
    IniciarJogador(&jogador);

    ListaObstaculos *obstaculos = CriarObstaculos();
    int pontos = 0;

    while (!WindowShouldClose()) {
        AtualizarJogador(&jogador);
        AtualizarObstaculos(obstaculos);

        if (VerificarColisao(&jogador, obstaculos)) {
            SalvarPontuacao(pontos);
            break;
        }

        pontos++;

        BeginDrawing();
        ClearBackground(DARKBLUE);

        DesenharJogador(jogador);
        DesenharObstaculos(obstaculos);
        DrawText(TextFormat("Pontos: %d", pontos), 20, 20, 20, RAYWHITE);

        EndDrawing();
    }

    LiberarObstaculos(obstaculos);
    CloseWindow();

    return 0;
}
