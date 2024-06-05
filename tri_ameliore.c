#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structure pour une cellule de la file d'attente
typedef struct Cellule {
    int index;
    struct Cellule *suivant;
} Cellule;

// Fonctions pour manipuler la file d'attente
void Enfiler(Cellule **queue, int index) {
    Cellule *nouvelleCellule = (Cellule *)malloc(sizeof(Cellule));
    nouvelleCellule->index = index;
    nouvelleCellule->suivant = NULL;

    if (*queue == NULL) {
        *queue = nouvelleCellule;
    } else {
        Cellule *temp = *queue;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouvelleCellule;
    }
}

int Defiler(Cellule **queue) {
    if (*queue == NULL) {
        return -1; // File d'attente vide
    } else {
        int index = (*queue)->index;
        Cellule *temp = *queue;
        *queue = (*queue)->suivant;
        free(temp);
        return index;
    }
}

// Algorithme de tri par sélection amélioré
void TriParSelectionAmeliore(int A[], int n) {
    int i = 0;
    while (i < n - 1) {
        int j = 0;
        int max_index = i;
        Cellule *File_Q = NULL;
        Enfiler(&File_Q, i);

        int val = i + 1;
        while (val < n) {
            if (A[val] > A[max_index]) {
                max_index = val;
                // Réinitialiser la file d'attente car une nouvelle valeur maximale est trouvée
                while (File_Q != NULL) Defiler(&File_Q);
                Enfiler(&File_Q, val);
            } else if (A[val] == A[max_index]) {
                Enfiler(&File_Q, val);
            }
            val++;
        }

        int front = 0;
        while (File_Q != NULL) {
            int index = Defiler(&File_Q);
            // Échanger les valeurs
            int temp = A[index];
            A[index] = A[i];
            A[i] = temp;
            i++;
            front++;
        }
    }
}

// Fonction pour générer un tableau de taille donnée avec des valeurs aléatoires
void GenererTableau(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100; // Valeurs entre 0 et 99
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

        double tempsAmeliore = MesurerTemps(TriParSelectionAmeliore, A, n, repetitions);
        printf("Taille : %d, Temps (Amélioré) : %f secondes\n", n, tempsAmeliore);

        free(A);
    }

    return 0;
}
