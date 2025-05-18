#include "raylib.h"
#include "../include/game.h"
#include <stdlib.h>
#include <time.h>

Board* CreateBoard(int gridSize, int numMines) {
    Board *board = (Board *)malloc(sizeof(Board));
    board->gridSize = gridSize;
    board->numMines = numMines;
    board->gameOver = false;

    // Aloca matriz de células
    board->cells = (Cell **)malloc(gridSize * sizeof(Cell *));
    for (int i = 0; i < gridSize; i++) {
        board->cells[i] = (Cell *)calloc(gridSize, sizeof(Cell));
    }

    // Inicializa lista de minas vazia
    board->mines.head = NULL;

    return board;
}

void PlaceMines(Board *board) {
    srand(time(NULL));
    int placedMines = 0;
    while (placedMines < board->numMines) {
        int x = rand() % board->gridSize;
        int y = rand() % board->gridSize;

        if (!board->cells[y][x].hasMine) {
            board->cells[y][x].hasMine = true;
            AddMine(&board->mines, x, y);
            placedMines++;
        }
    }
}

void CalculateAdjacentMines(Board *board) {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int y = 0; y < board->gridSize; y++) {
        for (int x = 0; x < board->gridSize; x++) {
            if (board->cells[y][x].hasMine) continue;

            int count = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < board->gridSize && ny >= 0 && ny < board->gridSize && board->cells[ny][nx].hasMine) {
                    count++;
                }
            }
            board->cells[y][x].adjacentMines = count;
        }
    }
}

void InitGame(Board *board) {
    for (int i = 0; i < board->gridSize; i++) {
        for (int j = 0; j < board->gridSize; j++) {
            board->cells[i][j].revealed = false;
            board->cells[i][j].hasMine = false;
            board->cells[i][j].flagged = false;
            board->cells[i][j].adjacentMines = 0;
        }
    }
    board->gameOver = false;

    PlaceMines(board);
    CalculateAdjacentMines(board);
}

void UpdateGame(Board *board) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int cellSize = 20;
        int x = (int)(mousePos.x - 10) / cellSize;
        int y = (int)(mousePos.y - 40) / cellSize;

        if (x >= 0 && x < board->gridSize && y >= 0 && y < board->gridSize) {
            board->cells[y][x].revealed = true;

            if (board->cells[y][x].hasMine) {
                board->gameOver = true;
            }
        }
    }
}

void DrawGame(Board *board) {
    DrawText("Campo Minado", 10, 10, 20, DARKGRAY);

    int cellSize = 20;
    for (int y = 0; y < board->gridSize; y++) {
        for (int x = 0; x < board->gridSize; x++) {
            Rectangle cellRect = { x * cellSize + 10, y * cellSize + 40, cellSize - 2, cellSize - 2 };
            Color color = board->cells[y][x].revealed ? LIGHTGRAY : DARKGRAY;
            DrawRectangleRec(cellRect, color);

            if (board->cells[y][x].flagged) {
                DrawText("F", cellRect.x + 5, cellRect.y + 2, 16, RED);
            } else if (board->cells[y][x].revealed && board->cells[y][x].hasMine) {
                DrawText("*", cellRect.x + 5, cellRect.y + 2, 16, BLACK);
            } else if (board->cells[y][x].revealed && board->cells[y][x].adjacentMines > 0) {
                DrawText(TextFormat("%d", board->cells[y][x].adjacentMines), cellRect.x + 5, cellRect.y + 2, 16, BLUE);
            }
        }
    }
}

// Função para adicionar uma mina na lista encadeada
void AddMine(MineList *list, int x, int y) {
    MineNode *newNode = malloc(sizeof(MineNode));
    newNode->x = x;
    newNode->y = y;
    newNode->next = list->head;
    list->head = newNode;
}

// Função para liberar a lista de minas
void FreeMineList(MineList *list) {
    MineNode *current = list->head;
    while (current) {
        MineNode *tmp = current;
        current = current->next;
        free(tmp);
    }
    list->head = NULL;
}

// Função para destruir o tabuleiro e liberar memória
void DestroyBoard(Board *board) {
    for (int i = 0; i < board->gridSize; i++) {
        free(board->cells[i]);
    }
    free(board->cells);
    FreeMineList(&board->mines);
    free(board);
}


