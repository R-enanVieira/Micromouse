#include <stdlib.h>
#include <stdio.h>
#include "mapa.c"

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

int vazia(head *);
int tamanho(head *);

node *primeiro(head *);
node *ultimo(head *);

pair espia(head *);

void empilha(head *, pair);  // insere_inicio
pair desempilha(head *);     // remove_inicio

head *criar_stack() {
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

int stack_vazia(head *p) { return (p->prox == NULL); }

int tamanho_stack(head *lista) { return lista->num_itens; }

node *topo(head *lista) { return lista->prox; }

node *ultimo(head *lista) { return lista->ultimo; }

pair espia(head *p) { return (p->prox->info); }

void empilha(head *lista, pair x) {
  node *novo = criar_no(x);
  if (novo) {
    if (vazia(lista)) lista->ultimo = novo;

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
