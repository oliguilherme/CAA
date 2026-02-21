#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5 

int minChave(int chave[], bool mstSet[]) {
    int minimo = INT_MAX, indice_minimo;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && chave[v] < minimo) {
            minimo = chave[v];
            indice_minimo = v;
        }
    }
    return indice_minimo;
}

void primMST(int grafo[V][V]) {
    int pai[V];       
    int chave[V];     
    bool mstSet[V];   

    for (int i = 0; i < V; i++) {
        chave[i] = INT_MAX;
        mstSet[i] = false;
    }

    chave[0] = 0;     
    pai[0] = -1;      

    for (int count = 0; count < V - 1; count++) {
        int u = minChave(chave, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (grafo[u][v] && mstSet[v] == false && grafo[u][v] < chave[v]) {
                pai[v] = u;
                chave[v] = grafo[u][v];
            }
        }
    }

    int custo_mst = 0;
    printf("Arestas da MST (Prim):\n");
    for (int i = 1; i < V; i++) {
        int peso_aresta = grafo[i][pai[i]];
        printf("%d - %d peso = %d\n", pai[i], i, peso_aresta);
        custo_mst += peso_aresta;
    }

    int custo_grafo = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (grafo[i][j] != 0) {
                custo_grafo += grafo[i][j];
            }
        }
    }

    printf("\nCusto total do grafo original: %d\n", custo_grafo);
    printf("Economia obtida: %d\n", custo_grafo - custo_mst);
    
    printf("\nCusto total da MST: %d\n", custo_mst);
    printf("OK: MST gerada com %d arestas\n", V - 1);
}

int main() {
    int grafo[V][V] = {
        {0, 2, 8, 6, 0},
        {2, 0, 3, 0, 5},
        {8, 3, 0, 7, 0},
        {6, 0, 7, 0, 9},
        {0, 5, 0, 9, 0}
    };

    primMST(grafo);

    return 0;
}