#include <stdio.h>

void le_matrizes(int l, int c, int n, int matriz[n][l][c])
{
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < l; i++)
            for (j = 0; j < c; j++)
                scanf("%d", &matriz[k][i][j]);    
}

void gera_media(int l, int c, int n, int matriz[n][l][c], float media[l][c])
{
    int k, i, j;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < l; i++)
        {
            for (j = 0; j < c; j++)
                media[i][j] = media[i][j] + matriz[k][i][j];
        }
    }
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            media[i][j] /= n;
}

void main()
{
    int N, L, C;
    int i, j;
    scanf("%d %d %d", &N, &L, &C);

    int matriz[N][L][C];
    le_matrizes(L, C, N, matriz);

    float media[L][C];
    for (i = 0; i < L; i++)
        for (j = 0; j < C; j++)
            media[i][j] = 0.0;
    gera_media(L, C, N, matriz, media);

    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++)
            printf("%.2f ", media[i][j]);
        printf("\n");
    }
}