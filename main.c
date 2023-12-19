#include "lib.c"

#define esquerdinha 'l'  // → rotacionar 90º para a esquerda (sentido anti-horário).
#define direitinha 'r'  // r → rotacionar 90º para a direita (sentido horário).
#define frentinha 'w'   // → caminhar para frente. (anda uma casa)
#define corridinha 'j'  // → corridinha para frente. (anda duas casas)
#define correr 'R'      // → correr para frente. (anda três casas)
#define corridona 's'  // → correr ao máximo para frente. (anda quatro casas)
#define sensor 'c'     // → ativar sensor de paredes próximas.
#define distancia_euclides 'd'  // → ativar sensor de proximidade do objetivo.

//iniciando a matrix
mapa grid[MAX_ROW][MAX_COL];

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdin);

  int ans;
  scanf("%d", &ans);
  fflush(stdout);

  return ans;
}

bool explore(pair coord, char dir) {
  int judgeAns = doAction(dir);

  if(!grid[coord.p][coord.s].visitado)
      return false;

  //callBack //desempilha ate o topo da pilha = topo da lista

  int frente = (judgeAns >> 0) & 1;    // 1 (livre)
  int direita = (judgeAns >> 1) & 1;   // 0 (parede)
  int tras = (judgeAns >> 2) & 1;      // 1 (livre)
  int esquerda = (judgeAns >> 3) & 1;  // 1 (livre)
}

int main() {


  pair coord_inicial = {MAX_ROW / 2, MAX_COL / 2};
  explore(coord_inicial, frentinha);
}


