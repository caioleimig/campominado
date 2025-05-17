#include "../include/game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void addMine(MineList *list, int x, int y) {
    MineNode *node = malloc(sizeof(MineNode));
    node->x = x;
    node->y = y;
    node->next = list->head;
    list->head = node;
}

void freeMines(MineList *list) {
    MineNode *curr = list->head;
    while (curr) {
        MineNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->head = NULL;
}

Board *createBoard(int size, int mines) {
    Board *board = malloc(sizeof(Board));
    board->gridSize = size;
    board->numMines = mines;
    board->gameOver = false;
    board->mines.head = NULL;

    board->cells = malloc(size * sizeof(Cell *));
    for (int i = 0; i < size; i++) {
        board->cells[i] = malloc(size * sizeof(Cell));
    }

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            board->cells[y][x].hasMine = false;
            board->cells[y][x].revealed = false;
            board->cells[y][x].flagged = false;
            board->cells[y][x].adjacentMines = 0;
        }

    return board;
}

void destroyBoard(Board *board) {
    for (int i = 0; i < board->gridSize; i++) {
        free(board->cells[i]);
    }
    free(board->cells);
    freeMines(&board->mines);
    free(board);
}

void countAdjacentMines(Board *board) {
    int size = board->gridSize;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (board->cells[y][x].hasMine) {
                board->cells[y][x].adjacentMines = -1;
                continue;
            }

            int count = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || ny < 0 || nx >= size || ny >= size)
                        continue;

                    if (board->cells[ny][nx].hasMine)
                        count++;
                }
            }
            board->cells[y][x].adjacentMines = count;
        }
    }
}

void initGame(Board *board) {
    srand(time(NULL));
    board->gameOver = false;
    freeMines(&board->mines);

    int size = board->gridSize;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            board->cells[y][x].hasMine = false;
            board->cells[y][x].revealed = false;
            board->cells[y][x].flagged = false;
            board->cells[y][x].adjacentMines = 0;
        }

    int placed = 0;
    while (placed < board->numMines) {
        int x = GetRandomValue(0, size - 1);
        int y = GetRandomValue(0, size - 1);

        if (!board->cells[y][x].hasMine) {
            board->cells[y][x].hasMine = true;
            addMine(&board->mines, x, y);
            placed++;
        }
    }

    countAdjacentMines(board);
}

void revealCell(Board *board, int x, int y) {
    int size = board->gridSize;

    if (x < 0 || y < 0 || x >= size || y >= size)
        return;

    Cell *cell = &board->cells[y][x];

    if (cell->revealed || cell->flagged)
        return;

    cell->revealed = true;

    if (cell->hasMine) {
        board->gameOver = true;

        for (MineNode *curr = board->mines.head; curr != NULL; curr = curr->next) {
            board->cells[curr->y][curr->x].revealed = true;
        }
        return;
    }

    if (cell->adjacentMines == 0) {
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++)
                if (dx != 0 || dy != 0)
                    revealCell(board, x + dx, y + dy);
    }
}

void updateGame(Board *board) {
    if (board->gameOver)
        return;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        int x = mouse.x / 40;
        int y = mouse.y / 40;
        revealCell(board, x, y);
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        int x = mouse.x / 40;
        int y = mouse.y / 40;

        if (x >= 0 && y >= 0 && x < board->gridSize && y < board->gridSize) {
            Cell *cell = &board->cells[y][x];
            if (!cell->revealed)
                cell->flagged = !cell->flagged;
        }
    }
}

void drawGame(Board *board) {
    int size = board->gridSize;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int px = x * 40;
            int py = y * 40;
            Cell *cell = &board->cells[y][x];

            DrawRectangleLines(px, py, 40, 40, GRAY);

            if (cell->revealed) {
                if (cell->hasMine)
                    DrawCircle(px + 20, py + 20, 10, RED);
                else if (cell->adjacentMines > 0)
                    DrawText(TextFormat("%d", cell->adjacentMines), px + 12, py + 8, 20, DARKGRAY);
            }
            else if (cell->flagged)
                DrawText("F", px + 12, py + 8, 20, BLUE);
        }
    }

    if (board->gameOver)
        DrawText("Game Over!", 150, size * 40 + 10, 30, RED);
}

bool isGameOver(Board *board) {
    return board->gameOver;
}

void saveBoard(Board *board, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return;

    fwrite(&board->gridSize, sizeof(int), 1, file);
    fwrite(&board->numMines, sizeof(int), 1, file);

    for (int y = 0; y < board->gridSize; y++)
        fwrite(board->cells[y], sizeof(Cell), board->gridSize, file);

    fclose(file);
}

Board *loadBoard(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    int size, mines;
    fread(&size, sizeof(int), 1, file);
    fread(&mines, sizeof(int), 1, file);

    Board *board = createBoard(size, mines);

    for (int y = 0; y < size; y++)
        fread(board->cells[y], sizeof(Cell), size, file);

    freeMines(&board->mines);

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
            if (board->cells[y][x].hasMine)
                addMine(&board->mines, x, y);

    countAdjacentMines(board);
    board->gameOver = false;

    fclose(file);
    return board;
}