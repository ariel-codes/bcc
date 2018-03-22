#include <stdio.h>
#include <stdlib.h>

int *setInterval(unsigned int inicio, unsigned int fim, unsigned int *data, unsigned int value)
{
    for (; inicio <= fim; inicio++)
        data[inicio] = value;
}

unsigned char intervalos(unsigned int fim, unsigned int *data)
{
    char found = 0;
    unsigned int pointer = 0;
    while (pointer < fim)
    {
        int start = pointer;
        while (start < fim)
        {
            if (data[start])
            {
                found = 1;
                printf("%u ", start);
                break;
            }
            else
                start++;
        }
        int end = start;
        while (start < fim)
        {
            if (data[end])
                end++;
            else
            {
                printf("%u\n", end-1);
                break;
            }
        }
        
        pointer = end;
    }
    return found;
}

void main()
{
    while (1)
    {
        int P, S, V, i;
        scanf("%d %d %d", &P, &S, &V);
        if (!P)
            return;
        // Because space efficiency doesn't matter anymore
        unsigned int *praia = (int *)calloc(P, sizeof(int));
        for (i = 0; i < S; i++)
        {
            unsigned int u, w;
            scanf("%u %u", &u, &w);
            setInterval(u, w, praia, 1);
        }
        for (i = 0; i < V; i++)
        {
            unsigned int u, w;
            scanf("%u %u", &u, &w);
            setInterval(u, w, praia, 0);
        }
        if (!intervalos(P, praia))
            printf("Nao ha vagas\n");
        free(praia);
    }
}