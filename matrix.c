#include "lib.c"

void inicializarLabirinto(mapa labirinto[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            labirinto[i][j].paredes[0] = true;
            labirinto[i][j].paredes[1] = true;
            labirinto[i][j].paredes[2] = true;
            labirinto[i][j].paredes[3] = true;
            labirinto[i][j].dir = -1;
            labirinto[i][j].visitado = false;
            labirinto[i][j].pai.p = -1;
            labirinto[i][j].pai.s = -1;
        }
    }
}

void imprimiMaze(mapa labirinto[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        // Imprimir linha superior
        for (int j = 0; j < MAX_COL; j++) {
            printf("+");
            if (labirinto[i][j].paredes[0])
                printf("-----");
            else
                printf("     ");
        }
        printf("+\n");

        // Imprimir linha do meio
        for (int j = 0; j < MAX_COL; j++) {
            if (labirinto[i][j].paredes[1])
                printf("|");
            else
                printf(" ");

            if (labirinto[i][j].visitado)
                printf("  X  ");
            else
                printf("     ");
        }
        if (labirinto[i][MAX_COL - 1].paredes[3])
            printf("|");
        else
            printf(" ");
        printf("\n");
    }

    // Imprimir última linha inferior
    for (int j = 0; j < MAX_COL; j++) {
        printf("+");
        if (labirinto[MAX_ROW - 1][j].paredes[2])
            printf("-----");
        else
            printf("     ");
    }
    printf("+\n");
}

/*
int main() {
    srand(time(NULL));

    mapa labirinto[MAX_ROW][MAX_COL];
    inicializarLabirinto(labirinto);

     for (int i = 0; i < MAX_ROW; i++) {
            for (int j = 0; j < MAX_COL; j++) {
                if (rand() % 2 == 0)
                    labirinto[i][j].paredes[0] = false;
                if (rand() % 2 == 0)
                    labirinto[i][j].paredes[1] = false;
                if (rand() % 2 == 0)
                    labirinto[i][j].paredes[2] = false;
                if (rand() % 2 == 0)
                    labirinto[i][j].paredes[3] = false;
            }
        }



    pair posicaoSeta;
    posicaoSeta.p = 4;
    posicaoSeta.s = 4;

    imprimirLabirinto(grid, posicaoSeta);

    return 0;
}
*/
