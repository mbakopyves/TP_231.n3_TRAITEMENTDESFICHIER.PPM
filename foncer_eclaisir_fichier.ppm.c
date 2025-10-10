#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction utilitaire : bornage pour rester entre 0 et max_val
int clamp(int valeur, int min, int max) {
    if (valeur < min) return min;
    if (valeur > max) return max;
    return valeur;
}

void modifier_dominante(char c, int val, const char *fichier) {
    FILE *in = fopen(fichier, "r");
    if (!in) {
        perror("Erreur d'ouverture du fichier d'entrée");
        return;
    }

    char type[3];
    int largeur, hauteur, max_val;

    // Lire l'en-tête PPM
    fscanf(in, "%2s", type);
    if (type[0] != 'P' || (type[1] != '3' && type[1] != '6')) {
        printf(" Format PPM non supporté (seuls P3 et P6 sont gérés)\n");
        fclose(in);
        return;
    }

    fscanf(in, "%d %d %d", &largeur, &hauteur, &max_val);

    int total_pixels = largeur * hauteur;

    // Vérifier la couleur demandée
    if (c != 'R' && c != 'G' && c != 'B' && c != 'r' && c != 'g' && c != 'b') {
        printf(" Couleur invalide : %c (utilise R, G ou B)\n", c);
        fclose(in);
        return;
    }

    // Pour simplifier la gestion, on normalise en majuscule
    if (c >= 'a' && c <= 'z') c -= 32;

    // Format texte (P3)
    if (type[1] == '3') {
        int *pixels = malloc(total_pixels * 3 * sizeof(int));
        if (!pixels) {
            printf("Erreur d'allocation mémoire\n");
            fclose(in);
            return;
        }

        for (int i = 0; i < total_pixels * 3; i++) {
            fscanf(in, "%d", &pixels[i]);
        }
        fclose(in);

        // Traitement pixel par pixel
        for (int i = 0; i < total_pixels; i++) {
            int r = pixels[i * 3];
            int g = pixels[i * 3 + 1];
            int b = pixels[i * 3 + 2];

            // Vérifie la dominante
            if ((c == 'R' && r > g && r > b) ||
                (c == 'G' && g > r && g > b) ||
                (c == 'B' && b > r && b > g)) {

                if (val < 0) { // éclaircir
                    r = clamp(r - val, 0, max_val);
                    g = clamp(g - val, 0, max_val);
                    b = clamp(b - val, 0, max_val);
                } else { // foncer
                    r = clamp(r - val, 0, max_val);
                    g = clamp(g - val, 0, max_val);
                    b = clamp(b - val, 0, max_val);
                }
            }

            pixels[i * 3] = r;
            pixels[i * 3 + 1] = g;
            pixels[i * 3 + 2] = b;
        }

        // Réécriture dans le même fichier
        FILE *out = fopen(fichier, "w");
        fprintf(out, "P3\n%d %d\n%d\n", largeur, hauteur, max_val);
        for (int i = 0; i < total_pixels; i++) {
            fprintf(out, "%d %d %d ", pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
        }
        fclose(out);
        free(pixels);
    }

    // Format binaire (P6)
    else if (type[1] == '6') {
        unsigned char *pixels = malloc(total_pixels * 3);
        if (!pixels) {
            printf("Erreur d'allocation mémoire\n");
            fclose(in);
            return;
        }

        fgetc(in); // sauter le \n
        fread(pixels, 3, total_pixels, in);
        fclose(in);

        for (int i = 0; i < total_pixels; i++) {
            int r = pixels[i * 3];
            int g = pixels[i * 3 + 1];
            int b = pixels[i * 3 + 2];

            if ((c == 'R' && r > g && r > b) ||
                (c == 'G' && g > r && g > b) ||
                (c == 'B' && b > r && b > g)) {

                if (val < 0) { // éclaircir
                    r = clamp(r - val, 0, max_val);
                    g = clamp(g - val, 0, max_val);
                    b = clamp(b - val, 0, max_val);
                } else { // foncer
                    r = clamp(r - val, 0, max_val);
                    g = clamp(g - val, 0, max_val);
                    b = clamp(b - val, 0, max_val);
                }
            }

            pixels[i * 3] = (unsigned char)r;
            pixels[i * 3 + 1] = (unsigned char)g;
            pixels[i * 3 + 2] = (unsigned char)b;
        }

        FILE *out = fopen(fichier, "wb");
        fprintf(out, "P6\n%d %d\n%d\n", largeur, hauteur, max_val);
        fwrite(pixels, 3, total_pixels, out);
        fclose(out);
        free(pixels);
    }

    printf(" Modification terminée sur %s : dominante %c, val = %d\n", fichier, c, val);
}
