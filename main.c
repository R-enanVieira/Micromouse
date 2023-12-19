#include "lib.c"

#define esquerdinha \
  'l'  // → rotacionar 90º para a esquerda (sentido anti-horário).
#define direitinha 'r'  // r → rotacionar 90º para a direita (sentido horário).
#define frentinha 'w'   // → caminhar para frente. (anda uma casa)
#define corridinha 'j'  // → corridinha para frente. (anda duas casas)
#define correr 'R'      // → correr para frente. (anda três casas)
#define corridona 's'  // → correr ao máximo para frente. (anda quatro casas)
#define sensor 'c'     // → ativar sensor de paredes próximas.
#define distancia_euclides 'd'  // → ativar sensor de proximidade do objetivo.

// iniciando a matrix
mapa grid[MAX_ROW][MAX_COL];

// variavel que diz a direção que o rato está olhando
int lookAt = 1;  // fala que ele nasce olhando pra esquerda

// inicaliza nossa fila e stack
head *queue;
head *stack;

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdin);

  int ans;
  scanf("%d", &ans);
  fflush(stdout);

  return ans;
}

bool explore(pair coord, char rDir) {
  int judgeAns = doAction(rDir);

  if (!grid[coord.p][coord.s].visitado) return false;
  // caso encontramos um nó que já foi visitado -> temo um looping
  // desenfilelira e aplica o goBack até chegarmos na coordenada que
  // desenfileiramos mudar a direcao pra andar pra tras

  if (judgeAns == 0) {
    setWall(grid, coord, lookAt);  // se move na matriz e mapeia aquela
                                   // celula de acordo com o judgeAns;

    judgeAns = doAction(sensor);  // usa o sensor

    // respostas do sensor (1 -> livre e 0 -> parede)
    int frente = (judgeAns >> 0) & 1;
    int direita = (judgeAns >> 1) & 1;
    int tras = (judgeAns >> 2) & 1;
    int esquerda = (judgeAns >> 3) & 1;

    if (direita && esquerda) enfileira(queue, coord);

    if (esquerda)
      doAction(esquerdinha), lookAt = 0, explore(coord, frente);
    else if (direita)
      doAction(direitinha), lookAt = 2, explore(coord, frente);
    else {
      // beco sem saída
      // desenfileirar a ultima intersecção e desempilhar até chegar nela(usar o
      // goBack)
    }
    // bateu na parede
    // marcar na matrix que encontrou uma parede
    // usar o sensor de paredes
    // rotacionar e chama a funcao explore
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

    explore(reloadedCoord, frente);
    // esta livre
    // anda pra frente ate bater numa parede
    // enquanto anda, empilha os nos
    // a cada passo, usa sensor
    // se achar no com intersecaao, emfileira
  }
  if (judgeAns == 2) {
    // achou a saida
    // desempilha ate chegar no primeiro no
    //
  }
}

int main() {
  queue = criar_queue();
  stack = criar_stack();

  pair coord_inicial = {MAX_ROW / 2, MAX_COL / 2};

  empilha(stack, coord_inicial);

  explore(coord_inicial, frentinha);
}
