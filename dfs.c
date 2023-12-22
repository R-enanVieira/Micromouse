#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 150
#define MAX_COL 150

typedef struct registro node;

struct registro {
  char info;
  node *prox;
};

typedef struct cabeca head;

struct cabeca {
  int num_itens;
  node *prox;
  node *ultimo;
};

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
head *stack;

node *criar_no(char x) {
  node *no = malloc(sizeof(node));
  no->prox = NULL;
  no->info = x;
  return no;
}

head *criar_stack() {
  head *le = malloc(sizeof(head));
  le->num_itens = 0;
  le->prox = NULL;
  le->ultimo = NULL;
  return le;
}

bool stackVazia(head *p) { return (p->prox == NULL); }

void empilha(head *lista, char x) {
  node *novo = criar_no(x);
  if (novo) {
    if (stackVazia(lista)) lista->ultimo = novo;

    novo->prox = lista->prox;
    lista->prox = novo;

    lista->num_itens++;
  }
}

char desempilha(head *lista) {
  node *topo = lista->prox;
  lista->prox = topo->prox;

  if (topo == lista->ultimo) lista->ultimo = NULL;
  lista->num_itens--;

  char x = topo->info;
  free(topo);
  return x;
}

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdout);

  int ans;
  scanf("%d", &ans);

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

void rotate(int direction, int flag) {
  if (mouseLookAt == direction) return;

  int cont = 0;
  for (int i = 0; i < 4; i++) {
    cont++;
    mouseLookAt = (mouseLookAt + 1) % 4;
    if (mouseLookAt == direction) break;
  }

  if (cont == 3) {
    doAction('r');
    if (flag) empilha(stack, 'r');
  } else {
    for (int i = 0; i < cont; i++) {
      doAction('l');
      if (flag) empilha(stack, 'l');
    }
  }
}

void goBack(pair currentCell, bool flag) {
  // printf("Entrou no Goback!!!\n");
  int x = currentCell.x, y = currentCell.y;

  int dirCameFrom = grid[x][y].dir;

  dirCameFrom = (dirCameFrom + 2) % 4;

  // printf("o tal do dirCameFron %d\n",dirCameFrom );

  rotate(dirCameFrom, flag);

  // printf("o tal do dirCameFron depois do rotacoes %d\n",dirCameFrom );

  doAction('w');
  if (flag) empilha(stack, 'w');
}

bool dfs(pair coord) {
  // printf("Coordenada que estou: {%d, %d}\n", coord.x, coord.y);
  for (int i = 0; i < 4; i++) {
    if (mouseLookAt != i) rotate(i, false);
    // printf("mouseLookAt: %d\n", mouseLookAt);

    if (isVisited(coord, i) || grid[coord.x][coord.y].paredes[i]) {
      // fprintf(stderr, "o no que eu estou olhando foi visitado\n");
      // printf(
      //   "-----------------------------------------------------------------"
      //   "\n");
      continue;
    }

    int judgeAns = doAction('w');

    if (judgeAns == 1) {
      if (dfs(move(coord, mouseLookAt))) {
        if (coord.x != MAX_ROW / 2 || coord.y != MAX_COL / 2)
          goBack(coord, true);

        return true;
      }
      // printf("SAIMOS DA RECURSÃO!\n");
      // printf("O rato tá olhando pra la: %d", mouseLookAt);
    } else if (judgeAns == 0) {
      setWall(coord, mouseLookAt);
    } else if (judgeAns == 2) {
      goBack(move(coord, mouseLookAt), true);
      goBack(coord, true);
      goal = coord;
      return true;
    }
    // printf(
    //   "-----------------------------------------------------------------\n");
  }

  goBack(coord, false);
  return false;
}

void finishMaze() {
  int judgeAns;

  while (!stackVazia(stack)) {
    char action = desempilha(stack);
    if (action == 'l')
      judgeAns = doAction('r');
    else if (action == 'r')
      judgeAns = doAction('l');
    else
      judgeAns = doAction('w');
  }
}

int main() {
  stack = criar_stack();

  pair inital_coord = {MAX_ROW / 2, MAX_COL / 2};
  grid[MAX_ROW / 2][MAX_COL / 2].visitado = true;

  for (int i = 0; i < MAX_ROW; i++) {
    for (int j = 0; j < MAX_COL; j++) {
      for (int k = 0; k < 4; k++) grid[i][j].paredes[k] = false;
      grid[i][j].visitado = false;
    }
  }

  dfs(inital_coord);
  doAction('l');
  doAction('l');
  finishMaze();

  return 0;
}
