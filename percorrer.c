#include <stdbool.h>

#include "stack.c"

#define COL 350
#define LIN 350

int dLinha[] = {0, 1, 0, -1};
int dColuna[] = {-1, 0, 1, 0};

pair directions[] = {
    (pair){-1, 0},  // pra cima
    (pair){0, 1},   // pra baixo
    (pair){1, 0},   // pra esquerda
    (pair){0, -1},  // pra direita
};

bool is_valid(bool vis[][COL], int x, int y) {
  if (x < 0 || y < 0 || x > LIN || y >= COL) return false;

  if (vis[x][y]) return false;

  return true;
}

void dfs2D(int x, int y, int malha[][COL], bool vis[][COL]) {
  head *s = criar_stack();

  empilha(s, (pair){x, y});

  while (!vazia(s)) {
    pair atual = desempilha(s);

    int linha = atual.p;
    int coluna = atual.s;

    if (is_valid(vis, x, y)) continue;

    vis[linha][coluna] = true;

    printf("%d ", malha[linha][coluna]);

    for (int i = 0; i < COL; i++) {
      int adjx = linha + dLinha[i];
      int adjy = coluna + dColuna[i];
      empilha(s, (pair){adjx, adjy});
    }
  }
}
