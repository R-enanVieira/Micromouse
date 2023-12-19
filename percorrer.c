#include <stdbool.h>

#include "stack.c"

#define COL 350
#define LIN 350

int dLinha[] = {0, 1, 0, -1};
int dColuna[] = {-1, 0, 1, 0};

bool is_valid(mapa grid[][COL], int x, int y) {
  if (x < 0 || y < 0 || x > LIN || y >= COL) return false;

  if (grid[x][y].visitado) return false;

  return true;
}

void dfs2D(int x, int y, mapa grid[][COL]) {
  head *s = criar_stack();

  empilha(s, (pair){x, y});  // start at MAX_ROW/2 and MAX_COL/2

  while (!vazia(s)) {
    pair atual = desempilha(s);

    int x = atual.p;
    int y = atual.s;

    if (!is_valid(grid, x, y)) continue;

    grid[x][y].visitado = true;

    for (int i = 0; i < 4; i++) {
      int adjx = x + dLinha[i];
      int adjy = y + dColuna[i];
      empilha(s, (pair){adjx, adjy});
    }
  }
}
