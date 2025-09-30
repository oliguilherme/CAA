#include <stdio.h>
#include <stdlib.h>

int ordenaArray(int arr[], int tam) {
    int count = 0;
    for (int i = 0; i <= tam; i++) {
        int aux;
        for (int j = 0; j < tam - i; j++) {
            count++;
            if (arr[j] > arr[j + 1]) {
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }

    return count;
}

int main() {
    system("clear");
    int countMelhor, countMedio, countPior;

    int arrMelhorCaso[] = {1, 2, 3, 4, 5};
    int arrCasoMedio[] = {1, 3, 2, 4, 5};
    int arrPiorCaso[] = {5, 4, 3, 2, 1};
    
    countMelhor = ordenaArray(arrMelhorCaso, 5);
    countMedio = ordenaArray(arrCasoMedio, 5);
    countPior = ordenaArray(arrPiorCaso, 5);


    for (int i = 0; i <= 4; i++) {
        printf("%d ", arrMelhorCaso[i]);
    }
    printf("\nTotal comparacoes (melhor caso): %d\n", countMelhor);

    for (int i = 0; i <= 4; i++) {
        printf("%d ", arrCasoMedio[i]);
    }
    printf("\nTotal comparacoes (caso medio): %d\n", countMedio);

    for (int i = 0; i <= 4; i++) {
        printf("%d ", arrPiorCaso[i]);
    }
    printf("\nTotal comparacoes (pior caso): %d\n", countPior);

    return 0;
}