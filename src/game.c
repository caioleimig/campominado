#include "raylib.h"
#include "../include/game.h"
#include <stdlib.h>
#include <time.h>

Board* CreateBoard(int gridSize, int numMines) {
    Board *board = (Board *)malloc(sizeof(Board));
    board->gridSize = gridSize;
    board->numMines = numMines;
    board->gameOver = false;

    board->cells = (Cell **)malloc(gridSize * sizeof(Cell *));
    for (int i = 0; i < gridSize; i++) {
        board->cells[i] = (Cell *)calloc(gridSize, sizeof(Cell));
    }

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

void RevealAllMines(Board *board) {
    for (int y = 0; y < board->gridSize; y++) {
        for (int x = 0; x < board->gridSize; x++) {
            if (board->cells[y][x].hasMine) {
                board->cells[y][x].revealed = true;
            }
        }
    }
}

void UpdateGame(Board *board, int screenWidth, int screenHeight) {
    if (board->gameOver) return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();

        int maxCellSize = 50;
        int cellSize = screenWidth / board->gridSize;
        if (cellSize > maxCellSize) cellSize = maxCellSize;

        int offsetX = (screenWidth - (cellSize * board->gridSize)) / 2;
        int offsetY = (screenHeight - (cellSize * board->gridSize)) / 2;

        int x = (int)(mousePos.x - offsetX) / cellSize;
        int y = (int)(mousePos.y - offsetY) / cellSize;

        if (x >= 0 && x < board->gridSize && y >= 0 && y < board->gridSize) {
            board->cells[y][x].revealed = true;

            if (board->cells[y][x].hasMine) {
                board->gameOver = true;
                RevealAllMines(board);
            }
        }
    }
}

void DrawGame(Board *board, int screenWidth, int screenHeight) {
    DrawText("Campo Minado", 10, 10, 20, DARKGRAY);
    if (board->gameOver) {
        DrawText("Você perdeu! Pressione R para reiniciar", 10, 40, 20, RED);
    }

    int maxCellSize = 50;
    int cellSize = screenWidth / board->gridSize;
    if (cellSize > maxCellSize) cellSize = maxCellSize;

    int offsetX = (screenWidth - (cellSize * board->gridSize)) / 2;
    int offsetY = (screenHeight - (cellSize * board->gridSize)) / 2;

    for (int y = 0; y < board->gridSize; y++) {
        for (int x = 0; x < board->gridSize; x++) {
            Rectangle cellRect = { offsetX + x * cellSize, offsetY + y * cellSize, cellSize - 2, cellSize - 2 };
            Color color = board->cells[y][x].revealed ? LIGHTGRAY : DARKGRAY;
            DrawRectangleRec(cellRect, color);

            if (board->cells[y][x].flagged) {
                DrawText("F", cellRect.x + cellSize / 4, cellRect.y + cellSize / 6, 16, RED);
            } else if (board->cells[y][x].revealed && board->cells[y][x].hasMine) {
                DrawText("*", cellRect.x + cellSize / 4, cellRect.y + cellSize / 6, 16, BLACK);
            } else if (board->cells[y][x].revealed && board->cells[y][x].adjacentMines > 0) {
                DrawText(TextFormat("%d", board->cells[y][x].adjacentMines), cellRect.x + cellSize / 4, cellRect.y + cellSize / 6, 16, BLUE);
            }
        }
    }
}

void AddMine(MineList *list, int x, int y) {
    MineNode *newNode = malloc(sizeof(MineNode));
    newNode->x = x;
    newNode->y = y;
    newNode->next = list->head;
    list->head = newNode;
}

void FreeMineList(MineList *list) {
    MineNode *current = list->head;
    while (current) {
        MineNode *tmp = current;
        current = current->next;
        free(tmp);
    }
    list->head = NULL;
}

void DestroyBoard(Board *board) {
    for (int i = 0; i < board->gridSize; i++) {
        free(board->cells[i]);
    }
    free(board->cells);
    FreeMineList(&board->mines);
    free(board);
}
