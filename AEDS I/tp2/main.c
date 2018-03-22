#include <stdio.h>
#include <string.h>

/* Processa cada partida, 
retorna 1 se J ganha, -1 se Z, e 0 se empatam */
int play()
{
    int j = 0, z = 0, jR = -1, zR = -1;
    while (1)
    {
        if (jR != 0)
        {
            scanf("%d", &jR);
            j += jR;
            printf("J+ %d\n", jR);
        }
        if (zR != 0)
        {
            scanf("%d", &zR);
            z += zR;
            printf("Z+ %d\n", zR);
        }
        if (jR == 0 && zR == 0)
        {
            int jDis = abs(j - 21), zDis = abs(z - 21);
            printf("Diff:\nJ: %d\nZ:%d", jDis, zDis);
            if (jDis == zDis)
                return 0;
            else
                return (jDis < zDis) ? 1 : -1;
        }
    }
}

void main()
{
    int partidas;
    int score[2] = {0, 0};
    //Só to usando pq é FIFO e prático de guardar output
    FILE *output;
    output = tmpfile();

    for (scanf("%d", &partidas); partidas > 0; partidas--)
    {
        switch (play())
        {
        case 1:
            score[0] += 2;
            score[1] -= 1;
            break;
        case -1:
            score[0] -= 1;
            score[1] += 2;
            break;
        case 0:
            score[0] += 1;
            score[1] += 1;
            break;
        }
        printf("Placar: %d x %d\n", score[0], score[1]);
    }
    if (score[0] < score[1])
        printf("Joaozinho\n");
    else if (score[0] > score[1])
        printf("Zezinho\n");
    else
        printf("Ambos\n");
    return 0;
}
