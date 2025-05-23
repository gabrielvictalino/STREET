#include "raylib.h"
#include "score.h"
#include "player.h"
#include "obstacle.h"
#include "mapa.h"
#include "enemy.h"
#include "predio.h"
#include <stdlib.h>
#include <time.h>

typedef enum {
    MENU_INICIAL,
    JOGANDO,
    GAME_OVER,
    PONTUACOES
} EstadoJogo;

typedef struct {
    Rectangle frame;
} MenuFrame;

// Duas texturas para obstáculos
Texture2D spriteCarro;
Texture2D spriteCaminhao;

// Função para adicionar inimigo na lista encadeada
void AdicionarInimigo(Inimigo **lista, Inimigo *novo) {
    if (novo) {
        novo->proximo = *lista;
        *lista = novo;
    }
}

int main() {
    InitWindow(800, 800, "STREET - O jogo");
    SetTargetFPS(60);
    srand(time(NULL));

    // Carregando sprites
    spriteCarro = LoadTexture("spritesCarro/carro.png");
    spriteCaminhao = LoadTexture("spritesCarro/caminhao.png");
    CarregarTexturaInimigo("spritesCrocodilo/crocodilo.png"); // SPRITE INIMIGO

    EstadoJogo estado = MENU_INICIAL;

    Mapa mapa;
    IniciarMapa(&mapa);

    Jogador jogador;
    IniciarJogador(&jogador);

    ListaObstaculos *obstaculos = CriarObstaculos();
    Inimigo *inimigos = NULL;

    int pontos = 0;

    int opcaoSelecionada = 0;
    const int totalOpcoes = 3;

    // Alternador para sprite do obstáculo (0 = carro, 1 = caminhão)
    int alternadorSprite = 0;

    // Variável para controle de spawn de inimigos
    int spawnTimer = 0;
    const int spawnInterval = 120; // Spawn a cada 120 frames (2 segundos a 60 FPS)

    // MENU
    Texture2D menuTexture = LoadTexture("spritesMenu/menu.png");

    MenuFrame menuFrames[3] = {
        { .frame = (Rectangle){ 0, 0, 800, 800 } },
        { .frame = (Rectangle){ 800, 0, 800, 800 } },
        { .frame = (Rectangle){ 0, 800, 800, 800 } }
    };

    // PRÉDIOS
    Texture2D texturaPredio = LoadTexture("spritesPredio/predio.png");
    Predio predios[3];
    for (int i = 0; i < 3; i++) predios[i].ativo = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        switch (estado) {
            case MENU_INICIAL: {
                Rectangle dest = { 0, 0, 800, 800 };
                Rectangle src = menuFrames[opcaoSelecionada].frame;
                Vector2 origin = { 0, 0 };
                DrawTexturePro(menuTexture, src, dest, origin, 0, WHITE);

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
                        spawnTimer = 0;
                        for (int i = 0; i < 3; i++) predios[i].ativo = false;
                        estado = JOGANDO;
                    } else if (opcaoSelecionada == 1) {
                        estado = PONTUACOES;
                    } else if (opcaoSelecionada == 2) {
                        UnloadTexture(menuTexture);
                        UnloadTexture(texturaPredio);
                        UnloadTexture(spriteCarro);
                        UnloadTexture(spriteCaminhao);
                        DescarregarTexturaInimigo();
                        CloseWindow();
                        return 0;
                    }
                }
                break;
            }

            case JOGANDO: {
                AtualizarMapa(&mapa);
                AtualizarJogador(&jogador);

                // Atualiza obstáculos
                Texture2D *spriteAtual = (alternadorSprite == 0) ? &spriteCarro : &spriteCaminhao;
                AtualizarObstaculos(obstaculos, pontos, spriteAtual);

                // Alterna sprite a cada 500 pontos
                if (pontos % 500 == 0) {
                    alternadorSprite = 1 - alternadorSprite;
                }

                // Spawn de inimigos periodicamente
                spawnTimer++;
                if (spawnTimer >= spawnInterval) {
                    spawnTimer = 0;
                    Inimigo *novo = CriarInimigo();
                    if (novo) AdicionarInimigo(&inimigos, novo);
                }

                AtualizarInimigos(&inimigos);

                // Atualiza prédios
                for (int i = 0; i < 3; i++) {
                    if (!predios[i].ativo && GetRandomValue(0, 1000) < 5) {
                        IniciarPredio(&predios[i], texturaPredio);
                    }
                    if (predios[i].ativo) {
                        AtualizarPredio(&predios[i]);
                    }
                }

                // Colisão do jogador com topo do prédio
                for (int i = 0; i < 3; i++) {
                    if (predios[i].ativo && ColisaoComTopo(predios[i], jogador.caixa)) {
                        if (jogador.velocidade > 0) {
                            jogador.velocidade = 0;
                            jogador.posicao.y = predios[i].hitboxTopo.y - jogador.caixa.height;
                            jogador.caixa.y = jogador.posicao.y;
                            jogador.pulos = 0;
                        }
                    }
                }

                // Verifica colisões com obstáculos e inimigos
                if (VerificarColisao(&jogador, obstaculos) || VerificarColisaoComInimigos(inimigos, jogador.caixa)) {
                    SalvarPontuacao(pontos);
                    estado = GAME_OVER;
                }

                pontos++;

                // Desenha o cenário
                DesenharMapa(mapa);

                for (int i = 0; i < 3; i++) {
                    if (predios[i].ativo) DesenharPredio(predios[i]);
                }

                DesenharJogador(jogador);
                DesenharObstaculos(obstaculos);
                DesenharInimigos(inimigos);

                DrawText(TextFormat("Pontos: %d", pontos), 20, 20, 20, RAYWHITE);
                break;
            }

            case GAME_OVER:
                DrawText("GAME OVER", 270, 180, 40, RED);
                DrawText(TextFormat("Pontuação final: %d", pontos), 270, 240, 20, RAYWHITE);
                DrawText("Pressione R para reiniciar ou ESC para sair", 180, 300, 20, GRAY);

                if (IsKeyPressed(KEY_R)) {
                    estado = MENU_INICIAL;
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    UnloadTexture(menuTexture);
                    UnloadTexture(texturaPredio);
                    UnloadTexture(spriteCarro);
                    UnloadTexture(spriteCaminhao);
                    DescarregarTexturaInimigo();
                    CloseWindow();
                    return 0;
                }
                break;

            case PONTUACOES: {
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
        }

        EndDrawing();
    }

    // Liberação final
    LiberarObstaculos(obstaculos);
    UnloadTexture(jogador.sprite);
    LiberarMapa(&mapa);
    LiberarInimigos(inimigos);
    DescarregarTexturaInimigo();
    UnloadTexture(menuTexture);
    UnloadTexture(texturaPredio);
    UnloadTexture(spriteCarro);
    UnloadTexture(spriteCaminhao);
    CloseWindow();

    return 0;
}
