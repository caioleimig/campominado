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
void UpdateGame(Board *board, int screenWidth, int screenHeight);
void DrawGame(Board *board, int screenWidth, int screenHeight);
void RevealAllMines(Board *board); // <- nova função

// MineList management
void AddMine(MineList *list, int x, int y);
void FreeMineList(MineList *list);

#endif // GAME_H
