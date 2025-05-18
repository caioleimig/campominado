#include "raylib.h"
#include "game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Campo Minado");

    int gridSize = 10;
    int numMines = 10;

    Board *board = CreateBoard(gridSize, numMines);
    InitGame(board);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame(board);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawGame(board);

        EndDrawing();
    }

    DestroyBoard(board);
    CloseWindow();

    return 0;
}
