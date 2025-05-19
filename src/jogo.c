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
    GAME_OVER,
    PONTUACOES
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

    int opcaoSelecionada = 0; // 0: Iniciar, 1: Pontuação, 2: Sair
    const char *opcoesMenu[] = { "Iniciar Jogo", "Pontuacoes", "Sair" };
    const int totalOpcoes = 3;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        switch (estado) {
            case MENU_INICIAL:
                DrawText("STREET - O JOGO", 240, 100, 40, RAYWHITE);

                for (int i = 0; i < totalOpcoes; i++) {
                    Color cor = (i == opcaoSelecionada) ? YELLOW : LIGHTGRAY;
                    DrawText(opcoesMenu[i], 320, 200 + i * 40, 30, cor);
                }

                if (IsKeyPressed(KEY_DOWN)) {
                    opcaoSelecionada = (opcaoSelecionada + 1) % totalOpcoes;
                } else if (IsKeyPressed(KEY_UP)) {
                    opcaoSelecionada = (opcaoSelecionada - 1 + totalOpcoes) % totalOpcoes;
                } else if (IsKeyPressed(KEY_ENTER)) {
                    if (opcaoSelecionada == 0) {
                        IniciarMapa(&mapa);
                        IniciarJogador(&jogador);
                        if (obstaculos) LiberarObstaculos(obstaculos);
                        obstaculos = CriarObstaculos();
                        LiberarInimigos(inimigos);
                        inimigos = NULL;
                        pontos = 0;
                        estado = JOGANDO;
                    } else if (opcaoSelecionada == 1) {
                        estado = PONTUACOES;
                    } else if (opcaoSelecionada == 2) {
                        CloseWindow();
                        return 0;
                    }
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
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    CloseWindow();
                    return 0;
                }
                break;

            case PONTUACOES:
                DrawText("RANKING DE PONTOS", 230, 120, 30, RAYWHITE);

                char **pontuacoes = LerPontuacoes();
                for (int i = 0; i < 5 && pontuacoes && pontuacoes[i]; i++) {
                    DrawText(pontuacoes[i], 280, 180 + i * 30, 20, LIGHTGRAY);
                    free(pontuacoes[i]);
                }
                free(pontuacoes);

                DrawText("Pressione ESC para voltar ao menu", 180, 400, 20, GRAY);

                if (IsKeyPressed(KEY_ESCAPE)) {
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
