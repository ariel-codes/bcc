#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
    char nome[21];
    char sobre[21];
    char email[101];
} User;

void swap(User *us1, User *us2)
{
    User tmp;
    const int size = sizeof(User);
    memcpy(&tmp, us1, size);
    memcpy(us1, us2, size);
    memcpy(us2, &tmp, size);
}

void sort(int field, User us[], int size)
{
    int i, j;
    int offset = field * 21; // 21*0=0, 21*1=21, 21*2=42;
    for (j = 0; j < size; j++)
    {
        int iMin = j;
        for (i = j + 1; i < size; i++)
        {
            if (strcmp((char *)(us[i].nome + offset), (char *)(us[iMin].nome + offset)) <= 0)
            {
                iMin = i;
            }
        }
        if (iMin != j)
        {
            swap(&us[j], &us[iMin]);
        }
    }
}

void main()
{
    int N, F;
    int i;
    scanf("%d", &N);
    User us[N];
    for (i = 0; i < N; i++)
    {
        scanf("%s %s %s ", &us[i].nome, &us[i].sobre, &us[i].email);
    }
    scanf("%d", &F);
    sort(F, us, N);
    for (i = 0; i < N; i++)
    {
        printf("%s %s %s\n", us[i].nome, us[i].sobre, us[i].email);
    }
}