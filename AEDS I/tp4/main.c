#include <tgmath.h>
#include <stdio.h>

int main()
{
    while (1)
    {
        int n, p, o;
        scanf("%d %d", &n, &p);
        if (n == 0 && p == 0)
            return 0;
        putchar('P');
        for (o = ceil((float)n / p); o > 0; o--)
        {
            putchar('o');
        }
        puts("dle");
    }
}