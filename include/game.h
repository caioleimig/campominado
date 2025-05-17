#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <stdbool.h>

typedef struct {
    bool revealed;
    bool hasMine;
    bool flagged;
    int adjacentMines;
} Cell;

typedef struct MineNode {
    int x, y;
    struct MineNode *next;
} MineNode;

typedef struct {
    MineNode *head;
} MineList;

typedef struct {
    int gridSize;
    int numMines;
    Cell **cells;
    MineList mines;
    bool gameOver;
} Board;

// Board management
Board* CreateBoard(int gridSize, int numMines);
void DestroyBoard(Board *board);
void InitGame(Board *board);

// Game logic
void UpdateGame(Board *board);
void DrawGame(Board *board);
bool IsGameOver(Board *board);

// MineList management
void AddMine(MineList *list, int x, int y);
void FreeMineList(MineList *list);

// Saving and loading
void SaveBoard(Board *board, const char *filename);
Board* LoadBoard(const char *filename);

#endif
