#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Oq o enunciado pediu
int pwr(int base, int expo)
{
    if (expo == 1)
        return base;
    else
        return base * pwr(base, expo - 1);
}

void main()
{
    int N, B;
    scanf("%d %d", &N, &B);
    while (N)
    {
        int P, Q, res;
        char C;
        scanf("%d %c %d", &P, &C, &Q);
        switch (C)
        {
        case '+':
            res = P + Q;
            break;
        case '*':
            res = P * Q;
        }
        if(pwr(2,B)>res)
            printf("OK\n");
        else printf("OVERFLOW\n");
        N--;
    }
}
