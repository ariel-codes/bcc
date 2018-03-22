#include <stdio.h>
#include <string.h>

//Processa cada conjunto de depósitos
void depositos(int iter, int n)
{
    int j = 0, z = 0, i = n - 1;
    printf("Teste %d\n", iter + 1);
    for (; n > 0; n--)
    {
        int dj, dz; // depósito da rodada
        scanf("%d %d", &dj, &dz);
        if (dj < 0 || dz < 0)
            printf("Vovo Vitoria nao tira dinheiro dos cofrinhos.\n");
        else
        {
            j += dj;
            z += dz;
            printf("%d\n", j - z);
        }
    }
}

void main()
{
    int linhas, iter;
    for (iter = 0;; iter++)
    {
        scanf("%d", &linhas);
        if (linhas == 0)
            break;
        else
        {
            depositos(iter, linhas);
        }
        if(linhas>1)
            printf("\n");
    }
}
