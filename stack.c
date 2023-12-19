#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int p;
  int s;
} pair;

typedef pair Item;

typedef struct registro node;
struct registro {
  Item info;
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
node *criar_no(Item);

int vazia(head *);
int tamanho(head *);

node *primeiro(head *);
node *ultimo(head *);

Item espia(head *);

void empilha(head *, Item);  // insere_inicio
Item desempilha(head *);     // remove_inicio

head *criar_stack() {
  head *le = malloc(sizeof(head));
  le->num_itens = 0;
  le->prox = NULL;
  le->ultimo = NULL;
  return le;
}

node *criar_no(Item x) {
  node *no = malloc(sizeof(node));
  no->prox = NULL;
  no->info = x;
  return no;
}

int stack_vazia(head *p) { return (p->prox == NULL); }

int tamanho_stack(head *lista) { return lista->num_itens; }

node *topo(head *lista) { return lista->prox; }

node *ultimo(head *lista) { return lista->ultimo; }

Item espia(head *p) { return (p->prox->info); }

void empilha(head *lista, Item x) {
  node *novo = criar_no(x);
  if (novo) {
    if (vazia(lista)) lista->ultimo = novo;

    novo->prox = lista->prox;
    lista->prox = novo;

    lista->num_itens++;
  }
}

Item desempilha(head *lista) {
  node *topo = lista->prox;
  lista->prox = topo->prox;

  if (topo == lista->ultimo) lista->ultimo = NULL;
  lista->num_itens--;

  Item x = topo->info;
  free(topo);
  return x;
}
