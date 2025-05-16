#include "raylib.h"

int main ()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Create the window and OpenGL context
    InitWindow(1280, 800, "Hello Raylib");

    // Carrega a textura usando caminho relativo direto
    Texture wabbit = LoadTexture("resources/wabbit_alpha.png");
    
    // game loop
    while (!WindowShouldClose()) // run the loop until user presses ESCAPE or closes window
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Hello Raylib", 200, 200, 20, WHITE);

        DrawTexture(wabbit, 400, 200, WHITE);
        
        EndDrawing();
    }

    UnloadTexture(wabbit);

    CloseWindow();
    return 0;
}
