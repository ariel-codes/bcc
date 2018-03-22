#include <stdio.h>

void printP(int* p, int cur)
{
    switch (cur)
    {
    case 0:
        fputs("Joaozinho ", stdout);
        break;
    case 1:
        fputs("Zezinho ", stdout);
        break;
    case 2:
        fputs("Pedro ", stdout);
        break;
    case 3:
        fputs("Maria ", stdout);
        break;
    }
    printf("%d x %d x %d x %d\n", p[0], p[1], p[2], p[3]);
}

main()
{
    int cur;
    int jzpm[] = {0, 0, 0, 0};
    scanf("%d", &cur);
    cur--;
    while (1)
    {
        int c, v;
        scanf("%d %d", &c, &v);
        if (c == 1)
        {
            cur = v - 1;
            printP(jzpm, cur);
        }
        else if (c == 2)
        {
            jzpm[cur] += v;
            if(jzpm[cur]<0)
                jzpm[cur] = 0;
            printP(jzpm, cur);
        }
        else
            return 0;
    }
}