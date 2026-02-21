#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5
#define INF INT_MAX

int minDistancia(int dist[], bool visitado[]) {
    int min = INF, indice_min;
    for (int v = 0; v < V; v++) {
        if (visitado[v] == false && dist[v] <= min) {
            min = dist[v];
            indice_min = v;
        }
    }
    return indice_min;
}

void imprimirCaminho(int pai[], int j) {
    if (pai[j] == -1) {
        printf("%d", j);
        return;
    }
    imprimirCaminho(pai, pai[j]);
    printf(" -> %d", j);
}

void dijkstra(int grafo[V][V], int origem) {
    int dist[V];
    bool visitado[V];
    int pai[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visitado[i] = false;
        pai[i] = -1;
    }

    dist[origem] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(dist, visitado);
        visitado[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[u][v] && dist[u] != INF 
                && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                pai[v] = u;
            }
        }
    }

    printf("Origem: %d\n\n", origem);
    printf("Vértice | Distância | Caminho\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t| %d \t    | ", i, dist[i]);
        imprimirCaminho(pai, i);
        printf("\n");
    }

    printf("\nOK: menores caminhos calculados (Dijkstra)\n");
}

int main() {
    
    int grafo[V][V] = {
        {0, 10, 0, 5, 0},
        {0, 0, 1, 2, 0},
        {0, 0, 0, 0, 4},
        {0, 3, 9, 0, 2},
        {7, 0, 6, 0, 0}
    };

    dijkstra(grafo, 0);

    return 0;
}