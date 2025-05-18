#include "raylib.h"
#include "game.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Campo Minado");

    int gridSize = 10;
    int numMines = 10;

    Board *board = CreateBoard(gridSize, numMines);
    InitGame(board);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame(board, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (board->gameOver && IsKeyPressed(KEY_R)) {
            InitGame(board);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawGame(board, SCREEN_WIDTH, SCREEN_HEIGHT);

        EndDrawing();
    }

    DestroyBoard(board);
    CloseWindow();

    return 0;
}
