#include <stdio.h>

typedef struct abacaxi_Struct
{
    int Ad;
    float Ap, Vc;
} abacaxi;

void le_escolhe(int N)
{
    abacaxi a[N];
    int i;

    for (i = 0; i < N; i++)
        scanf("%d", &a[i].Ad);
    for (i = 0; i < N; i++)
        scanf("%f", &a[i].Ap);
    for (i = 0; i < N; i++)
        scanf("%f", &a[i].Vc);

    // Índice do abacaxi escolhido
    int escolhido = 0;
    float Ag_escolhido = 0;
    for (i = 0; i < N; i++)
    {
        float Ag = (float)((a[i].Ad * a[i].Vc) / a[i].Ap);
        if (Ag_escolhido < Ag)
        {
            escolhido = i;
            Ag_escolhido = Ag;
        }
    }
    printf("%d %.2f %.5f %.5f\n", a[escolhido].Ad, a[escolhido].Ap, a[escolhido].Vc, Ag_escolhido);
}

void main()
{
    // Número de abacaxis
    int N;
    while (1)
    {
        scanf("%d", &N);
        if (N == 0)
            return;
        le_escolhe(N);
    }
}