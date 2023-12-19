#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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



