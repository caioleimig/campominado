#include "raylib.h"
#include "game.h"
#define LARGURA_TELA 700
#define ALTURA_TELA 700

int main(void) {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Campo Minado");

    int tamanhoGrade = 10;
    int numeroMinas = 10;

    Tabuleiro *tabuleiro = CriarTabuleiro(tamanhoGrade, numeroMinas);
    InicializarJogo(tabuleiro);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        AtualizarJogo(tabuleiro, LARGURA_TELA, ALTURA_TELA);

        if (tabuleiro->fimDeJogo && IsKeyPressed(KEY_R)) {
            InicializarJogo(tabuleiro);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DesenharJogo(tabuleiro, LARGURA_TELA, ALTURA_TELA);

        EndDrawing();
    }

    DestruirTabuleiro(tabuleiro);
    CloseWindow();

    return 0;
}