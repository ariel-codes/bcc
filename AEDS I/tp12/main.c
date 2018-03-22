#include <stdio.h>

void main()
{
    int i;
    float x, y;
    for (scanf("%d %f %f", &i, &x, &y); i > 0; i--)
    {
        float pX, pY;
        scanf("%f %f", &pX, &pY);

        if (pY > y)
            putchar('S');
        else
            putchar('N');
        if (pX > x)
            putchar('E');
        else
            putchar('O');
        putchar('\n');
    }
}