#include "raylib.h"
#include "score.h"
#include "player.h"
#include "obstacle.h"
#include "mapa.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

typedef enum {
    MENU_INICIAL,
    JOGANDO,
    GAME_OVER
} EstadoJogo;

int main() {
    InitWindow(800, 600, "STREET - O jogo");
    SetTargetFPS(60);
    srand(time(NULL));

    EstadoJogo estado = MENU_INICIAL;

    Mapa mapa;
    IniciarMapa(&mapa);

    Jogador jogador;
    IniciarJogador(&jogador);

    ListaObstaculos *obstaculos = CriarObstaculos();
    Inimigo *inimigos = NULL;

    int pontos = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        switch (estado) {
            case MENU_INICIAL:
                DrawText("STREET - O JOGO", 220, 180, 40, RAYWHITE);
                DrawText("Pressione ENTER para começar", 200, 260, 20, LIGHTGRAY);
                if (IsKeyPressed(KEY_ENTER)) {
                    IniciarMapa(&mapa);
                    IniciarJogador(&jogador);
                    if (obstaculos) LiberarObstaculos(obstaculos);
                    obstaculos = CriarObstaculos();
                    LiberarInimigos(inimigos);
                    inimigos = NULL;
                    pontos = 0;
                    estado = JOGANDO;
                }
                break;

            case JOGANDO:
                AtualizarMapa(&mapa);
                AtualizarJogador(&jogador);
                AtualizarObstaculos(obstaculos, pontos);
                AtualizarInimigos(&inimigos);

                if (VerificarColisao(&jogador, obstaculos) || VerificarColisaoComInimigos(inimigos, jogador.caixa)) {
                    SalvarPontuacao(pontos);
                    estado = GAME_OVER;
                }

                pontos++;

                DesenharMapa(mapa);
                DesenharJogador(jogador);
                DesenharObstaculos(obstaculos);
                DesenharInimigos(inimigos);
                DrawText(TextFormat("Pontos: %d", pontos), 20, 20, 20, RAYWHITE);
                break;

            case GAME_OVER:
                DrawText("GAME OVER", 270, 180, 40, RED);
                DrawText(TextFormat("Pontuação final: %d", pontos), 270, 240, 20, RAYWHITE);
                DrawText("Pressione R para reiniciar ou ESC para sair", 180, 300, 20, GRAY);

                if (IsKeyPressed(KEY_R)) {
                    estado = MENU_INICIAL;
                }
                break;
        }

        EndDrawing();
    }

    // Liberação de recursos
    LiberarObstaculos(obstaculos);
    UnloadTexture(jogador.sprite);
    LiberarMapa(&mapa);
    LiberarInimigos(inimigos);
    CloseWindow();

    return 0;
}

