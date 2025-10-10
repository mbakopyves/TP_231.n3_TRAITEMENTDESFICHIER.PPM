#include <stdio.h>
#include <stdlib.h>

void convertir_ppm_en_gris(const char *fichier) {
    FILE *in = fopen(fichier, "r");
    if (!in) {
        perror("Erreur d'ouverture du fichier");
        return;
    }
    char type[3];
    int largeur, hauteur, max_val;
    if (fscanf(in, "%2s", type) != 1) {
        printf("Erreur: impossible de lire le type du fichier PPM\n");
        fclose(in);
        return;
    }
    if (type[0] != 'P' || (type[1] != '3' && type[1] != '6')) {
        printf("Erreur: format PPM non supporté (seuls P3 et P6 sont acceptés)\n");
        fclose(in);
        return;
    }
    // Lire largeur, hauteur, et valeur max
    fscanf(in, "%d %d %d", &largeur, &hauteur, &max_val);
    // Vérifier le type
    if (type[1] == '3') {
        // Format texte P3
        int total_pixels = largeur * hauteur;
        int *pixels = malloc(total_pixels * 3 * sizeof(int));
        if (!pixels) {
            printf("Erreur d'allocation mémoire.\n");
            fclose(in);
            return;
        }
        // Lire tous les pixels
        for (int i = 0; i < total_pixels * 3; i++) {
            fscanf(in, "%d", &pixels[i]);
        }
        // Convertir en niveaux de gris
        for (int i = 0; i < total_pixels; i++) {
            int r = pixels[i * 3];
            int g = pixels[i * 3 + 1];
            int b = pixels[i * 3 + 2];
            int gris = (r + g + b) / 3;
            pixels[i * 3] = pixels[i * 3 + 1] = pixels[i * 3 + 2] = gris;
        }
        fclose(in);
        // Réécrire dans le même fichier
        FILE *out = fopen(fichier, "w");
        fprintf(out, "P3\n%d %d\n%d\n", largeur, hauteur, max_val);
        for (int i = 0; i < total_pixels; i++) {
            fprintf(out, "%d %d %d ", pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
        }
        fclose(out);
        free(pixels);
    } 
    else if (type[1] == '6') {
        // Format binaire P6
        unsigned char *pixels;
        int total_pixels = largeur * hauteur;
        fgetc(in); // sauter le '\n' après le header

        pixels = malloc(total_pixels * 3);
        if (!pixels) {
            printf("Erreur d'allocation mémoire.\n");
            fclose(in);
            return;
        }
        fread(pixels, 3, total_pixels, in);
        fclose(in);
        // Conversion en gris
        for (int i = 0; i < total_pixels; i++) {
            unsigned char r = pixels[i * 3];
            unsigned char g = pixels[i * 3 + 1];
            unsigned char b = pixels[i * 3 + 2];
            unsigned char gris = (r + g + b) / 3;
            pixels[i * 3] = pixels[i * 3 + 1] = pixels[i * 3 + 2] = gris;
        }
        // Réécrire dans le même fichier
        FILE *out = fopen(fichier, "wb");
        fprintf(out, "P6\n%d %d\n%d\n", largeur, hauteur, max_val);
        fwrite(pixels, 3, total_pixels, out);
        fclose(out);
        free(pixels);
    }
    printf("Conversion terminée : le fichier '%s' a été mis à jour en niveaux de gris.\n", fichier);
}
