#include <stdlib.h>
#include <stdio.h>

// funcao : calcula o digito verificador de isbn13 dados seus digitos
// recebe : arranjo de numeros contendo os digitos do isbn13
// retorna: valor do digito verificador do isbn13

int checa_isbn13(int *d, int v)
{
    // soma das posicoes pares
    int pares = d[0] + d[2] + d[4] + d[6] + d[8] + d[10];
    // soma das posicoes impares
    int impares = d[1] + d[3] + d[5] + d[7] + d[9] + d[11];

    // soma final
    int soma = pares + (impares * 3);

    // calcula digito verificador
    int dv = 10 - (soma % 10);

    // corrige digito verificador caso ele seja igual a 10
    if (dv == 10)
    {
        dv = 0;
    }
    return dv == v ? 1 : 0;
}

// funcao : calcula o digito verificador de cpf dados seus digitos
// recebe : arranjo de numeros contendo os digitos do cpf
// retorna: valor do digito verificador do cpf

int checa_cpf(int *d, int v)
{
    // primeira soma de produtos
    int soma = d[8] * 2 + d[7] * 3 + d[6] * 4 + d[5] * 5 +
               d[4] * 6 + d[3] * 7 + d[2] * 8 + d[1] * 9 + d[0] * 10;

    // resto da soma
    int resto = soma % 11;
    // variaveis auxiliares
    int dezena, unidade;

    // define valor da dezena
    if (resto == 0 || resto == 1)
    {
        dezena = 0;
    }
    else
    {
        dezena = 11 - resto;
    }

    // segunda soma de produtos
    soma = dezena * 2 + d[8] * 3 + d[7] * 4 + d[6] * 5 + d[5] * 6 +
           d[4] * 7 + d[3] * 8 + d[2] * 9 + d[1] * 10 + d[0] * 11;

    // resto da soma
    resto = soma % 11;

    // define valor da unidade
    if (resto == 0 || resto == 1)
    {
        unidade = 0;
    }
    else
    {
        unidade = 11 - resto;
    }

    int dv = dezena * 10 + unidade;
    return dv == v ? 1 : 0;
}

// funcao : calcula o digito verificador de cnpj dados seus digitos
// recebe : arranjo de numeros contendo os digitos do cnpj
// retorna: valor do digito verificador do cnpj

int checa_cnpj(int *d, int v)
{
    // primeira soma de produtos
    int soma = d[11] * 2 + d[10] * 3 + d[9] * 4 + d[8] * 5 + d[7] * 6 + d[6] * 7 +
               d[5] * 8 + d[4] * 9 + d[3] * 2 + d[2] * 3 + d[1] * 4 + d[0] * 5;

    // resto da soma
    int resto = soma % 11;
    // variaveis auxiliares
    int dezena, unidade;

    // define valor da dezena
    if (resto == 0 || resto == 1)
    {
        dezena = 0;
    }
    else
    {
        dezena = 11 - resto;
    }

    // segunda soma de produtos
    soma = dezena * 2 + d[11] * 3 + d[10] * 4 + d[9] * 5 + d[8] * 6 + d[7] * 7 +
           d[6] * 8 + d[5] * 9 + d[4] * 2 + d[3] * 3 + d[2] * 4 + d[1] * 5 +
           d[0] * 6;

    // resto da soma
    resto = soma % 11;

    // define valor da unidade
    if (resto == 0 || resto == 1)
    {
        unidade = 0;
    }
    else
    {
        unidade = 11 - resto;
    }

    // retorna digito verificador
    int dv = dezena * 10 + unidade;
    return dv == v ? 1 : 0;
}

int main(int argc, char **argv)
{
    int tipo, i, dv, j, r;
    int num[12];
    while (1)
    {
        scanf("%d", &tipo);
        if (tipo == 0)
            return 0;
        else if (tipo == 1 || tipo == 3)
            j = 12;
        else
            j = 9;
        for (i = 0; i < j; i++)
            scanf("%d", &num[i]);
        scanf("%d", &dv);
        switch (tipo)
        {
        case 1:
            r = checa_isbn13(num, dv);
            break;
        case 2:
            r = checa_cpf(num, dv);
            break;
        case 3:
            r = checa_cnpj(num, dv);
            break;
        case 0:
            return 0;
        }
        if (r)
            printf("valido\n");
        else
            printf("invalido\n");
    }
}