#include <stdio.h>

typedef struct
{
    int Ti, Tf;
    int Xp, Yp;
} Portal;

short check(int Xj, int Yj, int T, Portal ps[], int P)
{
    int i, j;
    for (i = 0; i < P; i++)
    {
        if (ps[i].Ti <= T && ps[i].Tf >= T)
            if (Xj == ps[i].Xp && Yj == ps[i].Yp)
                return 1;
    }
    return 0;
}

void main()
{
    int T, P;
    scanf("%d %d", &T, &P);

    int i;
    Portal ps[P];
    for (i = 0; i < P; i++)
        scanf("%d %d %d %d ", &ps[i].Ti, &ps[i].Tf, &ps[i].Xp, &ps[i].Yp);
    int Xj = 0, Yj = 0;
    char M;
    for (i = 0; i < T; i++)
    {
        printf("Tempo %d (%d, %d): ", i, Xj, Yj);
        if (check(Xj, Yj, i, ps, P))
        {
            puts("N");
            return;
        }
        else
            puts("S");
        scanf("%c ", &M);
        switch (M)
        {
        case 'E':
            Xj--;
            break;
        case 'D':
            Xj++;
            break;
        case 'C':
            Yj++;
            break;
        case 'B':
            Yj--;
            break;
        }
    }
}