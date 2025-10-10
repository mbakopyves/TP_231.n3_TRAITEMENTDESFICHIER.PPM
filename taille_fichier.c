#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Retourne le nombre total de pixels dans un fichier PPM
// et affiche aussi la largeur et la hauteur
int taille_pixels_ppm(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_fichier);
        return -1;
    }

    char format[3];
    int largeur, hauteur, max;

    // Lire l'en-tête du fichier PPM
    if (fscanf(f, "%2s", format) != 1) {
        printf("Erreur : impossible de lire le format du fichier.\n");
        fclose(f);
        return -1;
    }

    // Ignorer les commentaires éventuels (# ...)
    char ligne[256];
    do {
        if (fscanf(f, "%d %d", &largeur, &hauteur) == 2)
            break;
        fgets(ligne, sizeof(ligne), f);
    } while (1);

    fscanf(f, "%d", &max); // valeur max (souvent 255)

    fclose(f);

    int total_pixels = largeur * hauteur;
    printf("Format : %s\n", format);
    printf("Largeur : %d pixels\n", largeur);
    printf("Hauteur : %d pixels\n", hauteur);
    printf("Nombre total de pixels : %d\n", total_pixels);

    return total_pixels;
}
