#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "foncer_eclaisir_fichier.ppm.h"
#include "convertier_en_gris.h"
#include "taille_fichier.h"
#include "decoupe_partie.h"
#include "negatif.h"
#include "fichier_median.h"
// #include "foncer_eclaisir_fichier.ppm.c"

int main(){
    char commande[100];
    char nom_fichier[100];
    char fichier_source[100]="";
    char fichier_resultat[100]="";
    int l1, l2, c1, c2;
    char couleur[100];
    int val = 0;
    int taille=0;
    printf("Application de traitement d’images PPM réalisée par l'equipe LOTUS\n");
    // fonction de manipulation
    l1: 
    printf("\nppmviewer> ");
    fgets(commande,sizeof(commande),stdin);
    if(commande[strlen(commande)-1]=='\n'){
        commande[strlen(commande)-1]='\0';
    }
    //comparaison de commande a ce que l'utilisateur entre
    // commande de passage au foncer ou eclaicie
    if(strstr(commande,"dom")!=NULL){

    char *token = strtok(commande, " ");
    while (token != NULL) {
        // Couleur
        if ((strcmp(token, "R") == 0) || (strcmp(token, "G") == 0) || (strcmp(token, "B") == 0)) {
            strcpy(couleur,token);
        }
        // Fichier .ppm
        else if (strstr(token, ".ppm") != NULL) {
            strcpy(nom_fichier, token);
        }
        // Valeur (positive ou négative)
        else {
            int est_nombre = 1;
            for (int i = 0; token[i] != '\0'; i++) {
                if (!isdigit(token[i]) && !(i == 0 && token[i] == '-')) {
                    est_nombre = 0;
                    break;
                }
            }
            if (est_nombre) {
                val = atoi(token);
            }
        }
        token = strtok(NULL, " ");
    }
     modifier_dominante(couleur[0],val,nom_fichier);
        goto l1;
    }
    // commande avec le passe au gris
    if(strstr(commande,"gris")!=NULL){
        char *mot = strtok(commande," ");
    while (mot != NULL) {
        if (strstr(mot, ".ppm") != NULL) {
            strcpy(nom_fichier, mot);
            break;
        }
        mot = strtok(NULL, " ");
    }
        convertir_ppm_en_gris(nom_fichier);
        //fonction 2
        goto l1;
    }
    //commande de calcule e taille
    if(strstr(commande,"size")!=NULL){
          char *mot = strtok(commande," ");
    while (mot != NULL) {
        if (strstr(mot, ".ppm") != NULL) {
            strcpy(nom_fichier, mot);
            break;
        }
        mot = strtok(NULL, " ");
    }
    taille=taille_pixels_ppm(nom_fichier);
        goto l1;
    }
    //commande de passage au decoupage du fichier
    if(strstr(commande,"cut")!=NULL){
    char *token = strtok(commande, " ");
    int valeurs_trouvees = 0;

    while (token != NULL) {
        // Fichier .ppm source ou résultat
        if (strstr(token, ".ppm") != NULL) {
                if (fichier_source[0] == '\0') {
                strcpy(fichier_source, token);
            } else {
                strcpy(fichier_resultat, token);
            }
        }
        // Valeurs numériques
        else {
            int est_nombre = 1;
            for (int i = 0; token[i] != '\0'; i++) {
                if (!isdigit(token[i])) {
                    est_nombre = 0;
                    break;
                }
            }
            if (est_nombre) {
                switch (valeurs_trouvees) {
                    case 0: l1 = atoi(token); break;
                    case 1: l2 = atoi(token); break;
                    case 2: c1 = atoi(token); break;
                    case 3: c2 = atoi(token); break;
                }
                valeurs_trouvees++;
            }
        }
        token = strtok(NULL, " ");
    }
    decouper_ppm(fichier_source,fichier_resultat,l1,l2,c1,c2);

        // fonction 4
        goto l1;
    }
    // commande de passage aune negation
    if(strstr(commande,"neg")!=NULL){

    char *token = strtok(commande, " ");
    while (token != NULL) {
        if (strstr(token, ".ppm") != NULL) {
            if (fichier_source[0] == '\0')
                strcpy(fichier_source, token);
            else
                strcpy(fichier_resultat, token);
        }
        token = strtok(NULL, " ");
    }
    negatif_ppm(fichier_source,fichier_resultat);
        // fonction 5
        goto l1;
    }
    // commande de passage au filtre meian
    if(strstr(commande,"fil")!=NULL){
        char *token = strtok(commande, " ");
    while (token != NULL) {
        if (strstr(token, ".ppm") != NULL) {
            if (fichier_source[0] == '\0')
                strcpy(fichier_source, token);
            else
                strcpy(fichier_resultat, token);
        }
        token = strtok(NULL, " ");
    }
    filtre_median_ppm(fichier_source,fichier_resultat);
        // fonction 6
        goto l1;
    }
    // commande pour quitter du programme
    if(strstr(commande,"quit")!=NULL){
        return 0;
    }
}