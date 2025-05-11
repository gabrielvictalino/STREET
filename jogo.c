#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "Teste Raylib");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Street\n the game", 250, 280, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
