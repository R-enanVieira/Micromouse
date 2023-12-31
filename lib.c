#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define esquerdinha \
  'l'  // → rotacionar 90º para a esquerda (sentido anti-horário).
#define direitinha 'r'  // r → rotacionar 90º para a direita (sentido horário).
#define frentinha 'w'   // → caminhar para frente. (anda uma casa)
#define corridinha 'j'  // → corridinha para frente. (anda duas casas)
#define correr 'R'      // → correr para frente. (anda três casas)
#define corridona 's'  // → correr ao máximo para frente. (anda quatro casas)
#define sensor 'c'     // → ativar sensor de paredes próximas.
#define distancia_euclides 'd'  // → ativar sensor de proximidade do objetivo.

int doAction(char c) {
  printf("%c\n", c);

  int ans;
  scanf("%d", &ans);
  fflush(stdout);

  return ans;
}

typedef struct {
  int p;
  int s;
} pair;

typedef pair Item;

typedef struct {
  bool paredes[4];  // paredes[0] - cima | paredes[1] - esquerda | paredes[2] -
                    // baixo | parede[3] - direita
  int dir;

  bool visitado;

  pair pai;

} mapa;

#define MAX_ROW 150
#define MAX_COL 150

pair directions[] = {
    (pair){-1, 0},  // pra cima
    (pair){0, -1},  // pra esquerda
    (pair){1, 0},   // pra baixo
    (pair){0, 1},   // pra direita
};

pair locomover(mapa grid[][MAX_COL], pair originCell, int direcaoRato) {
  int x = originCell.p, y = originCell.s;
  pair destinyCell;

  destinyCell.p = x + directions[direcaoRato].p;
  destinyCell.s = y + directions[direcaoRato].s;

  grid[destinyCell.p][destinyCell.s].pai = originCell;
  grid[destinyCell.p][destinyCell.s].visitado = true;
  grid[destinyCell.p][destinyCell.s].dir = direcaoRato;

  return destinyCell;
}

void setWall(mapa grid[][MAX_COL], pair coord, int direction, int sensorData) {
  int frente = (sensorData >> 0) & 1;
  int direita = (sensorData >> 1) & 1;
  int tras = (sensorData >> 2) & 1;
  int esquerda = (sensorData >> 3) & 1;

  int x = coord.p, y = coord.s;
  // if(dir)
  grid[x][y].paredes[direction] = true;
}

bool isVisited(mapa grid[][MAX_COL], pair currentCell, int ratoDir) {
  int x = currentCell.p, y = currentCell.s;
  printf(
      "Verificando se o caralho dessas coordenadas {%d, %d} já foi visitada\n",
      x + directions[ratoDir].p, y + directions[ratoDir].s);
  return grid[x + directions[ratoDir].p][y + directions[ratoDir].s].visitado;
}

//////////////////////////////////////////////////////// Queue
////////////////////////////////////////////////////////////////////////////////////////////

typedef struct registro node;

struct registro {
  pair info;
  node *prox;
};

// tipo head
typedef struct cabeca head;

struct cabeca {
  int num_itens;
  node *prox;
  node *ultimo;
};

head *criar_lista();
node *criar_no(pair);

int queueVazia(head *);
int queueTamanho(head *);

node *queuePrimeiro(head *);
node *queueUltimo(head *);

void enfileira(head *, pair);  // insere_fim
pair desenfileira(head *);     // remove_inicio .. busca_inicio .. remove_no

head *criar_queue() {
  head *le = malloc(sizeof(head));
  le->num_itens = 0;
  le->prox = NULL;
  le->ultimo = NULL;
  return le;
}

node *criar_no(pair x) {
  node *no = malloc(sizeof(node));
  no->prox = NULL;
  no->info = x;
  return no;
}

int queueVazia(head *p) { return (p->prox == NULL); }

int queueTamanho(head *lista) { return lista->num_itens; }

node *queuePrimeiro(head *lista) { return lista->prox; }

node *queueUltimo(head *lista) { return lista->ultimo; }

void enfileira(head *lista, pair x) {
  node *novo = criar_no(x);
  if (novo) {
    novo->prox = NULL;

    // cabeca != node
    if (!queueVazia(lista))
      lista->ultimo->prox = novo;
    else
      lista->prox = novo;

    lista->ultimo = novo;
    lista->num_itens++;
  }
}

pair desenfileira(head *lista) {
  node *lixo = queuePrimeiro(lista);
  lista->prox = lista->prox->prox;

  // cabeca != node
  if (lixo == lista->ultimo) lista->ultimo = NULL;
  lista->num_itens--;

  pair x = lixo->info;
  free(lixo);
  return x;
}

//////////////////////////////////////////////////////// Stack
////////////////////////////////////////////////////////////////////////////////////////////

int stackVazia(head *);
int stackTamanho(head *);

node *stackPrimeiro(head *);
node *stackUltimo(head *);

pair stackEspia(head *);

void empilha(head *, pair);  // insere_inicio
pair desempilha(head *);     // remove_inicio

head *criar_stack() {
  head *le = malloc(sizeof(head));
  le->num_itens = 0;
  le->prox = NULL;
  le->ultimo = NULL;
  return le;
}

int stackVazia(head *p) { return (p->prox == NULL); }

int stackTamanho(head *lista) { return lista->num_itens; }

node *stackTopo(head *lista) { return lista->prox; }

node *stackUltimo(head *lista) { return lista->ultimo; }

pair stackEspia(head *p) { return (p->prox->info); }

void empilha(head *lista, pair x) {
  node *novo = criar_no(x);
  if (novo) {
    if (stackVazia(lista)) lista->ultimo = novo;

    novo->prox = lista->prox;
    lista->prox = novo;

    lista->num_itens++;
  }
}

pair desempilha(head *lista) {
  node *topo = lista->prox;
  lista->prox = topo->prox;

  if (topo == lista->ultimo) lista->ultimo = NULL;
  lista->num_itens--;

  pair x = topo->info;
  free(topo);
  return x;
}

#define igualPair(A, B) \
  { A.p == B.p &&A.s == B.s }

int noPath(mapa grid[][MAX_COL], pair destinCell, head *stack, int ratoDir) {
  printf("Entrou no NoPath\n");
  doAction(esquerdinha);
  printf("\ndireção que a porra do rato ta olhando: %d\n", ratoDir);
  ratoDir = (ratoDir + 1) % 4;
  printf("\ndireção que a porra do rato ta olhando: %d\n", ratoDir);
  doAction(esquerdinha);
  ratoDir = (ratoDir + 1) % 4;
  printf("\ndireção que a porra do rato ta olhando: %d\n", ratoDir);
  doAction(frentinha);

  pair currentCell = desempilha(stack);
  printf("pair de origem [NoPath]: {%d, %d}\n", currentCell.p, currentCell.s);
  printf("pair de destino [NoPath]: {%d, %d}\n", destinCell.p, destinCell.s);

  while (currentCell.p != destinCell.p || currentCell.s != destinCell.s) {
    pair ancestorCell = desempilha(stack);
    printf("pair de origem [NoPath]: {%d, %d}\n", currentCell.p, currentCell.s);

    int nextDir;

    int i = ancestorCell.p - currentCell.p;
    int j = ancestorCell.s - currentCell.s;

    printf("i: %d     j: %d\n", i, j);
    if (i == -1 && j == 0)
      nextDir = 0;
    else if (i == 0 && j == -1)
      nextDir = 1;
    else if (i == 1 && j == 0)
      nextDir = 2;
    else if (i == 0 && j == 1)
      nextDir = 3;

    // 0 -> 1 rotateLeft
    // 0 -> 3 rotateRight

    // 1 -> 0 rotateRight
    // 1 -> 2 rotateLeft

    // 2 -> 1 rotateRight
    // 2 -> 3 rotateLeft

    // 3 -> 2 rotateRight
    // 3 -> 1 rotateLeft

    if (ratoDir == nextDir)
      doAction(frentinha);
    else if (ratoDir == 0 && nextDir == 1 || ratoDir == 1 && nextDir == 2 ||
             ratoDir == 2 && nextDir == 3 || ratoDir == 3 && nextDir == 1)
      doAction(esquerdinha), ratoDir = (ratoDir + 1) % 4, doAction(frentinha);
    else if (ratoDir == 0 && nextDir == 3 || ratoDir == 1 && nextDir == 0 ||
             ratoDir == 2 && nextDir == 1 || ratoDir == 3 && nextDir == 2)
      doAction(direitinha), ratoDir = (ratoDir + 3) % 4, doAction(frentinha);

    currentCell = ancestorCell;

    printf("direção que a porra do rato ta olhando: %d\n", ratoDir);
    printf("a direção que a porra do rato devia tá olhando: %d\n", ratoDir);
  }

  printf("Saiu do Nopath\n");
  return ratoDir;
}

//////////////////////////////////////////////////////////////////////Percorrer
/////////////////////////////////////////////////////

int dLinha[] = {0, 1, 0, -1};
int dColuna[] = {-1, 0, 1, 0};

bool isValid(mapa grid[][MAX_COL], int x, int y) {
  if (x < 0 || y < 0 || x > MAX_ROW || y >= MAX_COL) return false;

  if (grid[x][y].visitado) return false;

  return true;
}

void dfs2D(int x, int y, mapa grid[][MAX_COL]) {
  head *s = criar_stack();

  empilha(s, (pair){x, y});  // start at MAX_ROW/2 and MAX_COL/2

  while (!stackVazia(s)) {
    pair atual = desempilha(s);

    int x = atual.p;
    int y = atual.s;

    if (!isValid(grid, x, y)) continue;

    grid[x][y].visitado = true;

    for (int i = 0; i < 4; i++) {
      int adjx = x + dLinha[i];
      int adjy = y + dColuna[i];
      empilha(s, (pair){adjx, adjy});
    }
  }
}
