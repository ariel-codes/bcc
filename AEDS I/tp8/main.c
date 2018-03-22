#include <stdio.h>
#include <stdlib.h>

typedef struct performance
{
    char nome[100];
    int **notas;
    int soma;
} escola;

int comp(const void *elem1, const void *elem2)
{
    int f = *((int *)elem1);
    int s = *((int *)elem2);
    if (f > s)
        return 1;
    if (f < s)
        return -1;
    return 0;
}

int calc_nota(escola *E, int Q)
{
    int i, j;
    for (i = 0; i < Q; i++)
    {
        qsort(E->notas[i], 5, sizeof(int), comp);
        for (j = 1; j < 4; j++)
            E->soma += E->notas[i][j];
    }
    return E->soma;
}

escola *le_escola(int Q, escola *E)
{
    int i, j, k;
    E->notas = malloc(sizeof(int *) * Q);
    for (i = 0; i < Q; i++)
    {
        E->notas[i] = malloc(sizeof(int) * 5);
    }

    E->soma = 0;
    scanf("%s", E->nome);
    for (i = 0; i < Q; i++)
    {
        scanf("%d %d %d %d %d", &E->notas[i][0], &E->notas[i][1], &E->notas[i][2], &E->notas[i][3], &E->notas[i][4]);
    }
    calc_nota(E, Q);
    return E;
}

void main()
{
    int N, Q, i, j, maior = 0;
    scanf("%d %d", &N, &Q);
    escola Es[N];
    for (i = 0; i < N; i++)
    {
        le_escola(Q, &Es[i]);
    }
    for (i = 0; i < N; i++)
    {
        if (Es[i].soma > maior)
        {
            maior = Es[i].soma;
            j = i;
        }
    }
    puts(Es[j].nome);

    // bora liberar a mem neh
    N--;
    Q--;
    while (N >= 0)
    {
        while (Q >= 0)
        {
            free(Es[N].notas[Q]);
            Q--;
        }
        free(Es[N].notas);
        N--;
    }
}