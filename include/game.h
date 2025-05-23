#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <stdbool.h>

typedef struct {
    bool revelada;
    bool temMina;
    bool marcada;
    int minasAdjacentes;
} Celula;

typedef struct NoMina {
    int x, y;
    struct NoMina *proximo;
} NoMina;

typedef struct {
    NoMina *cabeca;
} ListaMinas;

typedef struct {
    int tamanhoGrade;
    int numeroMinas;
    Celula **celulas;
    ListaMinas minas;
    bool fimDeJogo;
} Tabuleiro;

Tabuleiro* CriarTabuleiro(int tamanhoGrade, int numeroMinas);
void DestruirTabuleiro(Tabuleiro *tabuleiro);
void InicializarJogo(Tabuleiro *tabuleiro);

void AtualizarJogo(Tabuleiro *tabuleiro, int larguraTela, int alturaTela);
void DesenharJogo(Tabuleiro *tabuleiro, int larguraTela, int alturaTela);
void RevelarTodasMinas(Tabuleiro *tabuleiro); 

void AdicionarMina(ListaMinas *lista, int x, int y);
void LiberarListaMinas(ListaMinas *lista);
#endif 