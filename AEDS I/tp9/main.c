#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int carta(char s[3])
{
    switch (s[0])
    {
    case 'A':
        return 1;
    case 'K':
    case 'Q':
    case 'J':
        return 10;
    default:
        return s[0] - 48;
    }
}

void status(int jog[2])
{
    if (jog[0] > 21 && jog[1] > 21)
        printf("Empate");
    else if (jog[0] <= 21 && (jog[1] > 21 || jog[0] > jog[1]))
        printf("Joaozinho");
    else if (jog[1] <= 21 && (jog[0] > 21 || jog[1] > jog[0]))
        printf("Zezinho");
    else
        printf("Empate");
}

void main()
{
    int i;

    int jog[2] = {0, 0};
    char vez = 0;
    char cartas[3];
    int monte[48];
    for (i = 0; i < 48; i++)
    {
        scanf("%s", &cartas);
        monte[i] = carta(cartas);
    }
    i = 0;
    while (2 > vez)
    {
        unsigned int p;
        scanf("%u", &p);
        if (!p)
        {
            vez++;
            printf("Parou\n");
        }
        else
        {
            jog[vez] += monte[i];
            printf("%d\n", jog[vez]);
            if (jog[vez] > 21)
            {
                printf("Estourou\n");
                vez++;
            }
            i++;
        }
    }
    status(jog);
    return;
}
