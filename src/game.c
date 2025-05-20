#include "raylib.h"
#include "../include/game.h"
#include <stdlib.h>
#include <time.h>

Tabuleiro* CriarTabuleiro(int tamanhoGrade, int numeroMinas) {
    Tabuleiro *tabuleiro = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    tabuleiro->tamanhoGrade = tamanhoGrade;
    tabuleiro->numeroMinas = numeroMinas;
    tabuleiro->fimDeJogo = false;

    tabuleiro->celulas = (Celula **)malloc(tamanhoGrade * sizeof(Celula *));
    for (int i = 0; i < tamanhoGrade; i++) {
        tabuleiro->celulas[i] = (Celula *)calloc(tamanhoGrade, sizeof(Celula));
    }

    tabuleiro->minas.cabeca = NULL;
    return tabuleiro;
}

void PosicionarMinas(Tabuleiro *tabuleiro) {
    srand(time(NULL));
    int minasColocadas = 0;
    while (minasColocadas < tabuleiro->numeroMinas) {
        int x = rand() % tabuleiro->tamanhoGrade;
        int y = rand() % tabuleiro->tamanhoGrade;

        if (tabuleiro->celulas[y][x].temMina == false) {
            tabuleiro->celulas[y][x].temMina = true;
            AdicionarMina(&tabuleiro->minas, x, y);
            minasColocadas++;
        }
    }
}

void Adjacentes(Tabuleiro *tabuleiro) {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int y = 0; y < tabuleiro->tamanhoGrade; y++) {
        for (int x = 0; x < tabuleiro->tamanhoGrade; x++) {
            if (tabuleiro->celulas[y][x].temMina){
                continue;
            }
            int contagem = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < tabuleiro->tamanhoGrade &&
                    ny >= 0 && ny < tabuleiro->tamanhoGrade && 
                    tabuleiro->celulas[ny][nx].temMina) {
                    contagem++;
                }
            }
            tabuleiro->celulas[y][x].minasAdjacentes = contagem;
        }
    }
}

void InicializarJogo(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->tamanhoGrade; i++) {
        for (int j = 0; j < tabuleiro->tamanhoGrade; j++) {
            tabuleiro->celulas[i][j].revelada = false;
            tabuleiro->celulas[i][j].temMina = false;
            tabuleiro->celulas[i][j].marcada = false;
            tabuleiro->celulas[i][j].minasAdjacentes = 0;
        }
    }
    tabuleiro->fimDeJogo = false;

    PosicionarMinas(tabuleiro);
    Adjacentes(tabuleiro);
}

void RevelarTodasMinas(Tabuleiro *tabuleiro) {
    for (int y = 0; y < tabuleiro->tamanhoGrade; y++) {
        for (int x = 0; x < tabuleiro->tamanhoGrade; x++){
            if (tabuleiro->celulas[y][x].temMina) {
                tabuleiro->celulas[y][x].revelada = true;
            }
        }
    }
}

void AtualizarJogo(Tabuleiro *tabuleiro, int larguraTela, int alturaTela) {
    if (tabuleiro->fimDeJogo) {
    return;
}
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 posMouse = GetMousePosition();

        int tamanhoMaxCelula = 50;
        int tamanhoCelula = larguraTela / tabuleiro->tamanhoGrade;
        if (tamanhoCelula > tamanhoMaxCelula) {
        tamanhoCelula = tamanhoMaxCelula;
        }       

        int deslocX = (larguraTela - (tamanhoCelula * tabuleiro->tamanhoGrade)) / 2;
        int deslocY = (alturaTela - (tamanhoCelula * tabuleiro->tamanhoGrade)) / 2;

        int x = (int)(posMouse.x - deslocX) / tamanhoCelula;
        int y = (int)(posMouse.y - deslocY) / tamanhoCelula;

        if (x >= 0 && x < tabuleiro->tamanhoGrade && y >= 0 && y < tabuleiro->tamanhoGrade) {
            tabuleiro->celulas[y][x].revelada = true;

            if (tabuleiro->celulas[y][x].temMina) {
                tabuleiro->fimDeJogo = true;
                RevelarTodasMinas(tabuleiro);
            }
        }
    }
}

void DesenharJogo(Tabuleiro *tabuleiro, int largura, int altura) {
    DrawText("Campo Minado", 10, 10, 20, DARKGRAY);

    if (tabuleiro->fimDeJogo) {
        DrawText("GAME OVER!!! (Pressione R para reiniciar)", 10, 40, 20, RED);
    }

    int tamanho = largura / tabuleiro->tamanhoGrade;
    if (tamanho > 50) tamanho = 50;

    for (int y = 0; y < tabuleiro->tamanhoGrade; y++) {
    for (int x = 0; x < tabuleiro->tamanhoGrade; x++) {
        int posX = x * tamanho + (largura - (tamanho * tabuleiro->tamanhoGrade)) / 2;
        int posY = y * tamanho + (altura - (tamanho * tabuleiro->tamanhoGrade)) / 2;

        Color cor;
        if (tabuleiro->celulas[y][x].revelada) {
            cor = LIGHTGRAY;
        } else {
            cor = DARKGRAY;
        }
        DrawRectangle(posX, posY, tamanho - 2, tamanho - 2, cor);

        if (tabuleiro->celulas[y][x].marcada) {
            DrawText("F", posX + 5, posY + 5, 16, RED);
        } 
        else if (tabuleiro->celulas[y][x].revelada) {
            if (tabuleiro->celulas[y][x].temMina) {
                DrawText("*", posX + 5, posY + 5, 16, BLACK);
            } 
            else if (tabuleiro->celulas[y][x].minasAdjacentes > 0) {
                DrawText(TextFormat("%d", tabuleiro->celulas[y][x].minasAdjacentes), posX + 5, posY + 5, 16, BLUE);
            }
        }
    }
}    
}

void AdicionarMina(ListaMinas *lista, int x, int y) {
    NoMina *novo = malloc(sizeof(NoMina));
    novo->x = x;
    novo->y = y;
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
}

void LiberarListaMinas(ListaMinas *lista) {
    NoMina *atual = lista->cabeca;
    while (atual) {
        NoMina *novo = atual;
        atual = atual->proximo;
        free(novo);
    }
    lista->cabeca = NULL;
}

void DestruirTabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->tamanhoGrade; i++) {
        free(tabuleiro->celulas[i]);
    }
    free(tabuleiro->celulas);
    LiberarListaMinas(&tabuleiro->minas);
    free(tabuleiro);
}