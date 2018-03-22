#include <stdio.h>

void main()
{
    while (1)
    {
        int H, M, S, aH, aM, aS;
        scanf("%d %d %d %d %d %d", &H, &M, &S, &aH, &aM, &aS);
        if (H < 0)
            return;
        S += (H * 60 + M) * 60;
        aS += (aH * 60 + aM) * 60;
        int tempo = (aS < S) ? (aS + 86400) - S : aS - S;
        printf("%02d:%02d:%02d\n", tempo / 3600, (tempo % 3600) / 60, tempo % 60);
    }
}