#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char palavra[50];
    int distancia;
} Sugestao;

int min(int a, int b) {
    if (a >= b) 
        return b;
    else
        return a;
}

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}

int levensthein_pd(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    int dp[len1 + 1][len2 + 1];

    //preenchendo as primeiras linha e coluna
    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    for (int i = 1; i <= len1; i++) { //
        for (int j = 1; j <= len2; j++) {
            //verificar se a letra da palavra 1 é igual à letra da palavra 2
            //indices de texto em c começa na posicao 0
            int custo = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            dp[i][j] = min3(
                dp[i - 1][j] + 1, //topo
                dp[i][j - 1] + 1, //esquerda
                dp[i - 1][j - 1] + custo // diagonal
            );
        }
    }

    return dp[len1][len2];
}

int comparar_sugestoes(const void *a, const void *b) {
    Sugestao *sA = (Sugestao *)a;
    Sugestao *sB = (Sugestao *)b;

    return (sA->distancia - sB->distancia);
}

int main() {
    //criar dicionario
    const char *dicionario[] = {"programa", "programador", "programacao", "problema", "diagrama"};
    int num_palavras_dicionario = 5;
    const char *input = "progama"; //palavra com erro

    int limite = 2;

    //lista vazia para guardar as palavras que passarem no teste
    Sugestao sugestao_valida[100];
    int cont_validas_teste = 0;

    //varrer dicionario
    for (int i = 0; i < num_palavras_dicionario; i++) {
        //achar dist entre a palavra com erro e a palavra atual do dicionario 
        int dist = levensthein_pd(input, dicionario[i]);

        if (dist <= limite) {
            strcpy(sugestao_valida[cont_validas_teste].palavra, dicionario[i]);
            sugestao_valida[cont_validas_teste].distancia = dist;
            cont_validas_teste++;
        }
    }
    //ordernar sugestoes
    qsort(sugestao_valida, cont_validas_teste, sizeof(Sugestao), comparar_sugestoes);
    //sizeof(Sugestao) para o qsort saber quantos bytes pular do primeiro indice para o segundo.

    printf("Input: \"%s\"\n", input);
    printf("Sugestoes: [");
    for (int i = 0; i < cont_validas_teste; i++) {
        printf("\"%s\" (Dist: %d)", sugestao_valida[i].palavra, sugestao_valida[i].distancia);
        if (i < cont_validas_teste - 1) printf(", ");
    }
    printf("]\n");
}