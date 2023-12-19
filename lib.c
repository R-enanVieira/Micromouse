#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

#define MAX_ROW 300
#define MAX_COL 300

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

head *criar_lista() {
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
