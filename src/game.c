#include "game.h"
#include <stdlib.h>

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

void InitGame(Board *board) {
    // Aqui você pode inicializar minas e preparar o jogo
    // Exemplo simples: limpar células e resetar flags
    for (int i = 0; i < board->gridSize; i++) {
        for (int j = 0; j < board->gridSize; j++) {
            board->cells[i][j].revealed = false;
            board->cells[i][j].hasMine = false;
            board->cells[i][j].flagged = false;
            board->cells[i][j].adjacentMines = 0;
        }
    }
    board->gameOver = false;

    // TODO: adicionar minas e calcular adjacentes
}

void UpdateGame(Board *board) {
    // Atualize o estado do jogo (input, lógica)
    // Exemplo: verificar se jogo acabou etc.
}

void DrawGame(Board *board) {
    DrawText("Campo Minado", 10, 10, 20, DARKGRAY);

    // Exemplo simples: desenhar células como quadrados
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

bool IsGameOver(Board *board) {
    return board->gameOver;
}

void DestroyBoard(Board *board) {
    for (int i = 0; i < board->gridSize; i++) {
        free(board->cells[i]);
    }
    free(board->cells);

    // Liberar lista de minas
    FreeMineList(&board->mines);

    free(board);
}

// Funções para manipular MineList
void AddMine(MineList *list, int x, int y) {
    MineNode *newNode = (MineNode *)malloc(sizeof(MineNode));
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

// Aqui você pode implementar SaveBoard e LoadBoard se quiser
