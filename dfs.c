#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 150
#define MAX_COL 150

typedef struct {
  int x;
  int y;
} pair;

typedef struct {
  bool paredes[4];  // paredes[0] - cima | paredes[1] - esquerda | paredes[2] -
                    // baixo | parede[3] - direita
  int dir;

  bool visitado;

  pair pai;

} mapa;

// Declaração de variáveis globais
int mouseLookAt = 0;
mapa grid[MAX_ROW][MAX_COL];
pair directions[] = {
    (pair){-1, 0},  // pra cima
    (pair){0, -1},  // pra esquerda
    (pair){1, 0},   // pra baixo
    (pair){0, 1},   // pra direita
};
pair goal;

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdout);

  int ans;
  scanf("%d", &ans);
  fflush(stdin);

  return ans;
}

pair move(pair originCell, int direcaoRato) {
  int x = originCell.x, y = originCell.y;
  pair destinyCell;

  x += directions[direcaoRato].x;
  y += directions[direcaoRato].y;

  grid[x][y].pai = originCell;
  grid[x][y].visitado = true;
  grid[x][y].dir = direcaoRato;

  destinyCell.x = x;
  destinyCell.y = y;

  return destinyCell;
}

void setWall(pair coord, int direction) {
  int x = coord.x, y = coord.y;

  grid[x][y].paredes[direction] = true;
}

bool isVisited(pair currentCell, int ratoDir) {
  int x = currentCell.x, y = currentCell.y;

  x += directions[ratoDir].x;
  y += directions[ratoDir].y;

  return grid[x][y].visitado;
}

void rotate(int direction) {
  if (mouseLookAt == direction) return;

  int cont = 0;
  for (int i = 0; i < 4; i++) {
    cont++;
    mouseLookAt = (mouseLookAt + 1) % 4;
    if (mouseLookAt == direction) break;
  }

  if (cont == 3)
    doAction('r');
  else {
    for (int i = 0; i < cont; i++) {
      doAction('l');
    }
  }
}

void goBack(pair currentCell) {
  printf("Entrou no GObacl!!!\n");
  int x = currentCell.x, y = currentCell.y;

  int dirCameFrom = grid[x][y].dir;

  dirCameFrom = (dirCameFrom + 2) % 4;

  printf("o tal do dirCameFron %d\n",dirCameFrom );

  rotate(dirCameFrom);

  printf("o tal do dirCameFron depois do rotacoes %d\n",dirCameFrom );

  doAction('w');
}

bool dfs(pair coord) {
  printf("Coordenada que estou: {%d, %d}\n", coord.x, coord.y);
  for (int i = 0; i < 4; i++) {
    printf("mous  eLookAt before rotate: %d\n", mouseLookAt);

    if (isVisited(coord, i)) {
      printf("o no que eu estou olhando ofi visitado\n");
      continue;
    }
    printf("mouseLookAt after rotate: %d\n", mouseLookAt);

    if (mouseLookAt != i) rotate(i);

    int judgeAns = doAction('w');

    if (judgeAns == 1) {
      coord = move(coord, mouseLookAt);

      if (dfs(coord)) {
        if (coord.x != MAX_ROW / 2 || coord.y != MAX_COL / 2) goBack(coord);
        return true;
      }
    } else if (judgeAns == 0) {
      setWall(coord, mouseLookAt);
    } else if (judgeAns == 2) {
      goBack(move(coord,mouseLookAt));
      goBack(coord);
      goal = coord;
      return true;
    }
  }

  goBack(coord);
  return false;
}

int main() {
  pair inital_coord = {MAX_ROW / 2, MAX_COL / 2};
  grid[MAX_ROW / 2][MAX_COL / 2].visitado = true;


  dfs(inital_coord);
  return 0;
}
