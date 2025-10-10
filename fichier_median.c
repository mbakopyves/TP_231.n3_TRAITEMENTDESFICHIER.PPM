#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === Fonction utilitaire : tri d'un tableau de 9 éléments ===
void trier_tableau(unsigned char tab[9]) {
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (tab[j] < tab[i]) {
                unsigned char tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// === Fonction principale : filtre médian ===
void filtre_median_ppm(const char *fichier_source, const char *fichier_resultat) {
    FILE *src = fopen(fichier_source, "r");
    if (!src) {
        printf(" Erreur : impossible d'ouvrir %s\n", fichier_source);
        return;
    }

    char format[3];
    int largeur, hauteur, max;

    fscanf(src, "%2s", format);
    fscanf(src, "%d %d", &largeur, &hauteur);
    fscanf(src, "%d", &max);

    int total_pixels = largeur * hauteur;
    unsigned char *pixels = malloc(total_pixels * 3);
    if (!pixels) {
        printf(" Erreur d'allocation mémoire\n");
        fclose(src);
        return;
    }

    for (int i = 0; i < total_pixels * 3; i++) {
        fscanf(src, "%hhu", &pixels[i]);
    }
    fclose(src);

    // Préparer le tableau pour le résultat
    unsigned char *result = malloc(total_pixels * 3);
    if (!result) {
        printf(" Erreur d'allocation mémoire pour le résultat\n");
        free(pixels);
        return;
    }

    // Appliquer le filtre médian sur chaque pixel (sauf les bords)
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            unsigned char voisinR[9], voisinG[9], voisinB[9];
            int index = 0;

            // Parcourir les voisins dans une fenêtre 3x3
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // Si le voisin est hors de l'image, on prend le pixel courant
                    if (nx < 0) nx = x;
                    if (ny < 0) ny = y;
                    if (nx >= largeur) nx = x;
                    if (ny >= hauteur) ny = y;

                    int pos = (ny * largeur + nx) * 3;
                    voisinR[index] = pixels[pos];
                    voisinG[index] = pixels[pos + 1];
                    voisinB[index] = pixels[pos + 2];
                    index++;
                }
            }

            // Trier pour trouver la médiane
            trier_tableau(voisinR);
            trier_tableau(voisinG);
            trier_tableau(voisinB);

            int pos_courant = (y * largeur + x) * 3;
            result[pos_courant] = voisinR[4];
            result[pos_courant + 1] = voisinG[4];
            result[pos_courant + 2] = voisinB[4];
        }
    }

    // Écriture du fichier résultat
    FILE *res = fopen(fichier_resultat, "w");
    if (!res) {
        printf(" Erreur : impossible de créer %s\n", fichier_resultat);
        free(pixels);
        free(result);
        return;
    }

    fprintf(res, "%s\n%d %d\n%d\n", format, largeur, hauteur, max);
    for (int i = 0; i < total_pixels * 3; i++) {
        fprintf(res, "%d ", result[i]);
    }

    fclose(res);
    free(pixels);
    free(result);
    printf("Filtre médian appliqué avec succès dans %s\n", fichier_resultat);
}
