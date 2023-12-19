#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.c"
//#include "stack.c"

#define esquerdinha 'l' //→ rotacionar 90º para a esquerda (sentido anti-horário).
#define direitinha 'r' //r → rotacionar 90º para a direita (sentido horário).
#define frentinha 'w' //→ caminhar para frente. (anda uma casa)
#define corridinha 'j' //→ corridinha para frente. (anda duas casas)
#define correr  'R' //→ correr para frente. (anda três casas)
#define corridona 's' //→ correr ao máximo para frente. (anda quatro casas)
#define sensor 'c'// → ativar sensor de paredes próximas.
#define distancia_euclides 'd' //→ ativar sensor de proximidade do objetivo.

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdin);

  int ans;
  scanf("%d", &ans);
  fflush(stdout);

  return ans;
}

void dfs(char dir) {
  int judgeAns;
     judgeAns = doAction('w');

  if (judgeAns == 2) return;

  if (judgeAns == 1) {
    judgeAns = doAction('c');

    int frente = (judgeAns >> 0) & 1;    // 1 (livre)
    int direita = (judgeAns >> 1) & 1;   // 0 (parede)
    int tras = (judgeAns >> 2) & 1;      // 1 (livre)
    int esquerda = (judgeAns >> 3) & 1;  // 1 (livre)

    if (direita) doAction('r'), dfs('w');
    if (esquerda) doAction('l'), dfs('w');

    dfs('w');
  }

  if (judgeAns == 0) {
    judgeAns = doAction('c');
    int frente = (judgeAns >> 0) & 1;    // 1 (livre)
    int direita = (judgeAns >> 1) & 1;   // 0 (parede)
    int tras = (judgeAns >> 2) & 1;      // 1 (livre)
    int esquerda = (judgeAns >> 3) & 1;  // 1 (livre)
    if (direita)
      doAction('r'), dfs('w');
    else if (esquerda)
      doAction('l'), dfs('w');
    else
      doAction('l'), doAction('l'), dfs('w');
  }
}

int main() { dfs('w'); }