#include <stdio.h>
#include <stdlib.h>
#include "mapa.c"

typedef struct registro node;

struct registro {
    Item info;
    node *prox;
};

//tipo head
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

void enfileira(head *, Item); //insere_fim
Item desenfileira(head *);  //remove_inicio .. busca_inicio .. remove_no

head * criar_lista()
{
    head *le = malloc(sizeof(head));
    le->num_itens = 0;
    le->prox = NULL;
    le->ultimo = NULL;
    return le;
}

node *criar_no(Item x)
{
    node *no = malloc(sizeof(node));
    no->prox = NULL;
    no->info = x;
    return no;
}

int vazia(head *p)
{
    return (p->prox==NULL);
}

int tamanho(head *lista)
{
    return lista->num_itens;
}

node *primeiro(head *lista)
{
    return lista->prox;
}

node *ultimo(head *lista)
{
    return lista->ultimo;
}

void enfileira(head *lista, Item x)
{
    node *novo = criar_no(x);
    if(novo){

        novo->prox = NULL;

        //cabeca != node
        if(!vazia(lista)) lista->ultimo->prox = novo;
        else lista->prox = novo;

        lista->ultimo = novo;
        lista->num_itens++;
    }
}

Item desenfileira(head *lista)
{
    node *lixo = primeiro(lista);
    lista->prox = lista->prox->prox;

    //cabeca != node
    if(lixo == lista->ultimo) lista->ultimo = NULL;
    lista->num_itens--;

    Item x = lixo->info;
    free(lixo);
    return x;
}

