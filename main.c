#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdin);

  int ans;
  scanf("%d", &ans);
  fflush(stdout);

  return ans;
}

void dfs(char dir, char turn) {
  int judgeAns;
  if (turn == 'n')
    judgeAns = doAction(dir);
  else
    doAction(turn), judgeAns = doAction('w');

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
