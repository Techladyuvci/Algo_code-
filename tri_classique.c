#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Fonction pour générer un tableau de taille donnée avec des valeurs aléatoires
void GenererTableau(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100; // Valeurs entre 0 et 99
    }
}

// Algorithme de tri par sélection classique
void TriParSelectionClassique(int A[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_index = i;
        for (int j = i+1; j < n; j++) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }
        int temp = A[min_index];
        A[min_index] = A[i];
        A[i] = temp;
    }
}

// Fonction pour afficher le tableau
void AfficherTableau(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Fonction pour mesurer le temps d'exécution
double MesurerTemps(void (*tri)(int[], int), int A[], int n, int repetitions) {
    clock_t debut = clock();
    for (int i = 0; i < repetitions; i++) {
        int *B = (int *)malloc(n * sizeof(int));
        memcpy(B, A, n * sizeof(int));
        tri(B, n);
        free(B);
    }
    clock_t fin = clock();
    return (double)(fin - debut) / (CLOCKS_PER_SEC * repetitions);
}

int main() {
    int tailles[] = {100, 200, 400, 600, 800, 1000};
    int nombreTailles = sizeof(tailles) / sizeof(tailles[0]);
    int repetitions = 1000;

    for (int i = 0; i < nombreTailles; i++) {
        int n = tailles[i];
        int *A = (int *)malloc(n * sizeof(int));

        GenererTableau(A, n);

        double tempsClassique = MesurerTemps(TriParSelectionClassique, A, n, repetitions);
        printf("Taille : %d, Temps (Classique) : %f secondes\n", n, tempsClassique);

        free(A);
    }

    return 0;
}
