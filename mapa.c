#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int p;
  int s;
} pair;

typedef pair Item;

typedef struct {
  pair coord;

  char dir;

  bool visitado;

  pair pai;

} mapa;

pair locomover(pair no_atual, int direcao) {
  pair directions[] = {
      (pair){-1, 0},  // pra cima
      (pair){0, 1},   // pra baixo
      (pair){1, 0},   // pra esquerda
      (pair){0, -1},  // pra direita
  };

  no_atual.p -= directions[direcao].p;
  no_atual.s -= directions[direcao].s;

  return no_atual;
}
