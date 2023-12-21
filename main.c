#include "lib.c"

// iniciando a matrix
mapa grid[MAX_ROW][MAX_COL];

// variavel que diz a direção que o rato está olhando
int lookAt = 3;  // fala que ele nasce olhando pra esquerda

// inicaliza nossa fila e stack
head *queue;
head *stack;

void explore(pair coord) {
  int judgeAns = doAction(frentinha);

  // esvazia a fila para debbug
  printf("Elementos da pilha: \n");
  node *qElemen = stack->prox;
  while (qElemen != NULL) {
    printf("{%d, %d}\n", qElemen->info.p, qElemen->info.s);
    qElemen = qElemen->prox;
  }
  printf("JudgeAns Value in explorar() scope: %d\n", judgeAns);
  printf("\ndireção que a porra do rato ta olhando: %d\n", lookAt);

  if (judgeAns == 0) {
    printf("Detectou uma parede\n");
    setWall(grid, coord, lookAt);

    judgeAns = doAction(sensor);  // usa o sensor

    // respostas do sensor (1 -> livre e 0 -> parede)
    int frente = (judgeAns >> 0) & 1;
    int direita = (judgeAns >> 1) & 1;
    int tras = (judgeAns >> 2) & 1;
    int esquerda = (judgeAns >> 3) & 1;

    if (esquerda)
      doAction(esquerdinha), lookAt = (lookAt + 1) % 4, explore(coord);
    else if (direita)
      doAction(direitinha), lookAt = (lookAt + 3) % 4, explore(coord);
    else {
      pair desiredCell;
      node *queueElement = queuePrimeiro(queue);
      if (queueElement != NULL) desiredCell = queueElement->info;

      lookAt = noPath(grid, desiredCell, stack, lookAt);

      int flag = 0;

      if (frente && !isVisited(grid, desiredCell, lookAt)) flag++;
      if (esquerda && !isVisited(grid, desiredCell, ((lookAt + 1) % 4))) flag++;
      if (direita && !isVisited(grid, desiredCell, ((lookAt + 3) % 4))) flag++;

      pair discardCell;
      if (!(flag - 1)) discardCell = desenfileira(queue);

      if (frente && !isVisited(grid, desiredCell, lookAt))
        explore(desiredCell);
      else if (esquerda && !isVisited(grid, desiredCell, ((lookAt + 1) % 4)))
        doAction(esquerdinha), lookAt = (lookAt + 1) % 4, explore(desiredCell);
      else if (direita && !isVisited(grid, desiredCell, ((lookAt + 3) % 4)))
        doAction(direitinha), lookAt = (lookAt + 3) % 4, explore(desiredCell);
    }

  } else if (judgeAns == 1) {
    printf("Andou pra frente!!!\n");

    if (grid[coord.p + directions[lookAt].p][coord.s + directions[lookAt].s]
            .visitado) {
      printf("Entrou na detectção de ciclo\n");
      pair desiredCell;
      node *queueElement = queuePrimeiro(queue);
      if (queueElement != NULL) desiredCell = queueElement->info;

      lookAt = noPath(grid, desiredCell, stack, lookAt);
      empilha(stack, desiredCell);

      printf("lookAt depois de sair doPath: %d\n", lookAt);

      judgeAns = doAction(sensor);

      int frente = (judgeAns >> 0) & 1;
      int direita = (judgeAns >> 1) & 1;
      int tras = (judgeAns >> 2) & 1;
      int esquerda = (judgeAns >> 3) & 1;
      printf("%d%d%d%d\n", esquerda, tras, direita, frente);

      int flag = 0;

      if (frente && !isVisited(grid, desiredCell, lookAt)) flag++;
      if (esquerda && !isVisited(grid, desiredCell, ((lookAt + 1) % 4))) flag++;
      if (direita && !isVisited(grid, desiredCell, ((lookAt + 3) % 4)))
        flag++, printf("computou que é a desgraça de um caminho livre.\n");
      printf("valor da flag: %d\n", flag);
      pair discardCell;
      if (!(flag - 1))
        discardCell = desenfileira(queue), printf("desenfileiramos!\n");

      if (frente && !isVisited(grid, desiredCell, lookAt))
        explore(desiredCell);
      else if (esquerda && !isVisited(grid, desiredCell, ((lookAt + 1) % 4)))
        doAction(esquerdinha), lookAt = (lookAt + 1) % 4, explore(desiredCell);
      else if (direita && !isVisited(grid, desiredCell, ((lookAt + 3) % 4)))
        doAction(direitinha), lookAt = (lookAt + 3) % 4, explore(desiredCell);

      return;
    }

    pair reloadedCoord = locomover(grid, coord, lookAt);
    empilha(stack, reloadedCoord);
    printf("pair empilhado: {%d, %d}\n", reloadedCoord.p, reloadedCoord.s);

    judgeAns = doAction(sensor);  // usa o sensor

    // respostas do sensor (1 -> livre e 0 -> parede)
    int frente = (judgeAns >> 0) & 1;
    int direita = (judgeAns >> 1) & 1;
    int tras = (judgeAns >> 2) & 1;
    int esquerda = (judgeAns >> 3) & 1;

    if ((frente + direita + esquerda) > 1) {
      enfileira(queue, reloadedCoord);
      printf("pair enfileirado: {%d, %d}\n", reloadedCoord.p, reloadedCoord.s);
    }

    explore(reloadedCoord);
  } else if (judgeAns == 2) {
    printf("Achou a saída!!!\n");
    empilha(stack, coord);
    return;
  }
}

int main() {
  queue = criar_queue();
  stack = criar_stack();
  for (int i = 0; i < MAX_ROW; i++) {
    for (int j = 0; j < MAX_COL; j++) {
      grid[i][j].visitado = false;
    }
  }
  pair coord_inicial = {MAX_ROW / 2, MAX_COL / 2};
  grid[MAX_ROW / 2][MAX_COL / 2].visitado = true;

  int judgeAns = doAction(sensor);
  int frente = (judgeAns >> 0) & 1;
  int direita = (judgeAns >> 1) & 1;
  int tras = (judgeAns >> 2) & 1;
  int esquerda = (judgeAns >> 3) & 1;

  if ((frente + direita + esquerda + tras) > 1) enfileira(queue, coord_inicial);

  empilha(stack, coord_inicial);

  explore(coord_inicial);
}
