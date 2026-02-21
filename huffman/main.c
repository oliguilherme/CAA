#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 256

typedef struct no {
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo; //*dir e *esq são para a ávore; *proximo, para a lista
} No;

typedef struct {
    No *inicio; //ponteiro para o primeiro nó da nossa lista
    int tam;
} Lista;


/* ------------------------------------------------ 1 - TABELA DE FREQUENCIA ------------------------------------------------ */
void inicializa_tabela_com_zero(unsigned int tab[]);
void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[]);
void imprime_tab_frequencia(unsigned int tab[]);


/* ------------------------------------------------ 2 - LISTA DE FREQUÊNCIA ------------------------------------------------ */
void criar_lista(Lista *lista);
void inserir_ordenado(Lista *lista, No *no);
void preencher_lista(int unsigned tab[], Lista *lista);
void imprimir_lista(Lista *lista);


/* ------------------------------------------------ 3 - MONTAR ÁRVORE DE HUFFMAN ------------------------------------------------ */
No* remove_no_inicio(Lista *lista);
No* montar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int tam);


/* ------------------------------------------------ 4 - MONTAR O DICIONÁRIO ------------------------------------------------ */
int altura_arvore(No *raiz);
char** aloca_dicionario(int colunas);
void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas);
void imprime_dicionario(char **dicionario);



/* ------------------------------------------------ 5 - GERA CODIGO ------------------------------------------------ */
int calcula_tamanho_string(char **dicionario, unsigned char *texto);
char* codificar(char **dicionario, char unsigned *texto);


/* ------------------------------------------------ 6 - DECODIFICACAO ------------------------------------------------ */
char* decodificar(unsigned char texto[], No *raiz);

int main() {
    system("clear");
    
    unsigned char texto[] = "EU SOU FODA"; //unsigned para resolver problemas como acentuação
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arv;
    int colunas;
    char **dicionario;
    char *codificado, *decodificado;
    
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(texto, tabela_frequencia);
    imprime_tab_frequencia(tabela_frequencia);

    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista);

    arv = montar_arvore(&lista);
    printf("\n\tArvore de Huffman\n");
    imprimir_arvore(arv, 0);

    colunas = altura_arvore(arv) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arv, "", colunas);
    imprime_dicionario(dicionario);

    codificado = codificar(dicionario, texto);
    printf("\n\tTexto codificado: %s", codificado);

    decodificado = decodificar(codificado, arv);
    printf("\n\tTexto decodificado: %s\n", decodificado);

    int bits_original = strlen(texto) * 8;
    int bits_codificado = strlen(codificado);
    float economia = 100.0 * (1 - (float)bits_codificado/bits_original);

    printf("\n\tBits original: %d", bits_original);
    printf("\n\tBits codificado: %d", bits_codificado);
    printf("\n\tEconomia: %.2f: ", economia);

    return 0;
}

/* ------------------------------------------------ 1 - TABELA DE FREQUENCIA ------------------------------------------------ */

void inicializa_tabela_com_zero(unsigned int tab[]) {
    for(int i = 0; i < TAM; i++) {
        tab[i] = 0;
    }
}

void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[]) {
    int i = 0;
    while(texto[i] != '\0') {
        tab[texto[i]]++;
        i++;
    }
}

void imprime_tab_frequencia(unsigned int tab[]) {
    for(int i = 0; i < TAM; i++) {
        if (tab[i] != 0) 
            printf("%d = %d = %c\n", i, tab[i], i);
    }
}

/* ------------------------------------------------ 2 - LISTA DE FREQUÊNCIA ------------------------------------------------ */

void criar_lista(Lista *lista) { //inicializando a lista
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no) {
    No *aux;
    // a lista está vazia?
    if (lista->inicio == NULL) {
        lista->inicio = no;
    } else if (no->frequencia < lista->inicio->frequencia) { //tem freq menor que o do inicio da lista?
        no->proximo = lista->inicio; //nó aponta para o início da lista
        lista->inicio = no;
    } else { //insercao no meio (percorrer a lista)
        aux = lista->inicio;
        while (aux->proximo != NULL && aux->proximo->frequencia <= no->frequencia ) {
            aux = aux->proximo;
        }
        no->proximo = aux->proximo; //o novo no aponta para o nó imediatamente posterior a ele na frequencia
        aux->proximo = no; //o no anterior aponta para o novo no.
    }
    lista->tam++;
}

void preencher_lista(int unsigned tab[], Lista *lista) {
    No* novo;
    for (int i = 0; i < TAM; i++) {
        if (tab[i] > 0) {
            novo = malloc(sizeof(No));
            if (novo) {
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            } else {
                printf("\nERRO AO ALOCAR MEMORIA EM PREENCHER_LISTA!!!!\n");
            }
        }
    }
}

void imprimir_lista(Lista *lista) {
    No *aux = lista->inicio;
    printf("\nLISTA ORDENADA: TAMANHO: %d\n", lista->tam);

    while (aux != NULL) {
        printf("Caracter: %c | Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

/* ------------------------------------------------ 3 - MONTAR ÁRVORE DE HUFFMAN ------------------------------------------------ */
No* remove_no_inicio(Lista *lista) {
    No *aux = NULL; //caso lista vazia

    if (lista->inicio != NULL) { //removendo o primeiro nó
        aux = lista->inicio;
        lista->inicio = aux->proximo; //lista aponta agora para o nó que era apontado pelo até então primeiro nó
        aux->proximo = NULL;
        lista->tam--;
    }

    return aux;
}

No* montar_arvore(Lista *lista) {
    No *primeiro, *segundo, *novo;


    while (lista->tam > 1) {
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if (novo) {
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);

        } else {
            printf("\nErro ao alocar memoria em montar_arvore");
            break;
        }

    }

    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam) {
    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("\tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
    } else {
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}


/* ------------------------------------------------ 4 - MONTAR O DICIONÁRIO ------------------------------------------------ */
char** aloca_dicionario(int colunas) {
    char **dicionario;

    //alocacao dinamica para matriz

    dicionario = malloc(sizeof(char*) * TAM);

    for (int i = 0; i < TAM; i++)
        dicionario[i] = calloc(colunas, sizeof(char)); //calloc aloca, retorna memoria e limpa a regiao de memoria alocada; precisamos concatenar strings

    return dicionario;
}

int altura_arvore(No *raiz) {
    //qual o tamanho do caminhho até a folha mais distante?
    int esq, dir;

    if (raiz == NULL) //chegamos a uma folha
        return -1;
    else {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if (esq > dir)
            return esq;
        else
            return dir;
    }
}

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas) {
    char esquerda[colunas], direita[colunas];

    if (raiz->esq == NULL && raiz->dir == NULL)
        strcpy(dicionario[raiz->caracter], caminho); //salvando a string caminho (ex: 111001101) no nó folha
    else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void imprime_dicionario(char **dicionario) {

    printf("\n\tDicionario:\n");

    for (int i = 0; i < TAM; i++) {
        if (strlen(dicionario[i]) > 0)
            printf("\t%3d: %s\n", i, dicionario[i]);
    }
}


/* ------------------------------------------------ 5 - GERA CODIGO ------------------------------------------------ */
int calcula_tamanho_string(char **dicionario, unsigned char *texto) { //quantos caracteres para representar esse texto codificado?
    int i = 0, tam = 0;

    while (texto[i] != '\0') {
        tam += strlen(dicionario[texto[i]]);
        i++;
    }

    return tam + 1; //caracter de fim de string
}

char* codificar(char **dicionario, char unsigned *texto) {

    int i = 0, tam = calcula_tamanho_string(dicionario, texto);

    char *codigo = calloc(tam, sizeof(char));

    while (texto[i] != '\0') {
        strcat(codigo, dicionario[texto[i]]);//para cada caracter do nosso texto, pegamos o codigo desse caracter e colocamos na string codigo
        i++;
    }

    return codigo;
}



/* ------------------------------------------------ 6 - DECODIFICACAO ------------------------------------------------ */
char* decodificar(unsigned char texto[], No *raiz) {
    int i = 0;
    No *aux = raiz;
    char temp[2];
    char *decodificado = calloc(strlen(texto), sizeof(char));

    while (texto[i] != '\0') {
        if (texto[i] == '0')
            aux = aux->esq;
        else
            aux = aux->dir;
        
        if (aux->dir == NULL && aux->esq == NULL) { //no folha
            //crio uma string pq o strcat concatena apenas strings, e aux->caracter é um char
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        } 
        i++;
    }

    return decodificado;
}