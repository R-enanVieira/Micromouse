#include "lib.c"

// iniciando a matrix
mapa grid[MAX_ROW][MAX_COL];

// variavel que diz a direção que o rato está olhando
int lookAt = 1;  // fala que ele nasce olhando pra esquerda

// inicaliza nossa fila e stack
head *queue;
head *stack;

void explore(pair coord) {
  int judgeAns = doAction(frentinha);

  // if (grid[coord.p][coord.s].visitado) {
  //   pair reloadedCoord = ciclePath(grid, coord, desenfileira(queue), stack);
  // }

  if (judgeAns == 0) {
    setWall(grid, coord, lookAt);

    judgeAns = doAction(sensor);  // usa o sensor

    // respostas do sensor (1 -> livre e 0 -> parede)
    int frente = (judgeAns >> 0) & 1;
    int direita = (judgeAns >> 1) & 1;
    int tras = (judgeAns >> 2) & 1;
    int esquerda = (judgeAns >> 3) & 1;

    if (direita && esquerda) enfileira(queue, coord);

    if (esquerda)
      doAction(esquerdinha), lookAt = (lookAt + 1) % 4, explore(coord);
    else if (direita)
      doAction(direitinha), lookAt = (lookAt + 3) % 4, explore(coord);
    else {
      pair desiredCell = desenfileira(queue);
      int lookAt = noPath(grid, desiredCell, stack, lookAt);

      judgeAns = doAction(sensor);

      frente = (judgeAns >> 0) & 1;
      direita = (judgeAns >> 1) & 1;
      tras = (judgeAns >> 2) & 1;
      esquerda = (judgeAns >> 3) & 1;

      if (frente && !isVisited(grid, desiredCell, lookAt))
        explore(desiredCell);
      else if (esquerda && !isVisited(grid, desiredCell, ((lookAt + 1) % 4)))
        doAction(esquerdinha), lookAt = (lookAt + 1) % 4, explore(desiredCell);
      else if (direita && !isVisited(grid, desiredCell, ((lookAt + 3) % 4)))
        doAction(direitinha), lookAt = (lookAt + 3) % 4, explore(desiredCell);

      // tavez precise considerar o caso em que visitou todos os caminhos da
      // intersecção e vai ter que voltar pro outro no enfileirado que é uma
      // intersecção;
    }

  } else if (judgeAns == 1) {
    pair reloadedCoord = locomover(grid, coord, lookAt);
    empilha(stack, reloadedCoord);

    judgeAns = doAction(sensor);  // usa o sensor

    // respostas do sensor (1 -> livre e 0 -> parede)
    int frente = (judgeAns >> 0) & 1;
    int direita = (judgeAns >> 1) & 1;
    int tras = (judgeAns >> 2) & 1;
    int esquerda = (judgeAns >> 3) & 1;

    if ((frente + direita + esquerda) > 1) enfileira(queue, reloadedCoord);

    explore(reloadedCoord);
  }
  if (judgeAns == 2) {
  }
}

int main() {
  queue = criar_queue();
  stack = criar_stack();

  pair coord_inicial = {MAX_ROW / 2, MAX_COL / 2};

  empilha(stack, coord_inicial);

  explore(coord_inicial, frentinha);
}
