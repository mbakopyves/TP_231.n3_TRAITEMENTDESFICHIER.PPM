# MANIPULATION DES MATRICE DANS LE CONTEXTE DES IMAGES A EXTENSION .ppm

## DESCRIPTION EN PREMIER VUE DU PROGRAMME
ce programme regroupe en sont sein plusieur fonction dans la manioulation des image a extension .ppm

NB: dans tou les fonction ci dessous il est demander a un utilisateur d'entrer de lui meme sont image.ppm a fin que celle ci soit traiter a ssa convenant. les parametre d'utilisation vous seron detailler

## INSTRUCTION DE COMPILATION

```bash
gcc *c -o ppmviewer.exe
./ppmviewer.exe
```

### 1. foncer ou eclaisir un fichier.ppm
le taritement de cet fonction a ete d'une difficulter considerable surtout dans la detection des parametres de saisi des utilisateur et dans sont traitement

##### mode d'emploi
commande: dom c val fichier.ppm

    dom represente la commande appelant la fonction 
    c represente la couleur, elle a pour valeurs (R, G ou B)
    val est l’entier à ajouter ou à retrancher. Si val< 0 alors il s’agira d’éclaircir        l’image sinon il s’agira plutôt de la foncer. 
    fichier.ppm est le nom du fichier à traiter

##### exemple d'utilisation et resultat
![capture resultat de cet fonction](capture_resultat/Capture%20d’écran%20du%202025-10-10%2009-23-28.png)

sur cet image vous pouver constater que l'utilisateur est entre en parametre 'R' '-50' Shelton.512.ppm' et regardons le resultat

![capture rasultat](capture_resultat/Capture%20d’écran%20du%202025-10-10%2009-26-16.png)

sur cet image de Shelton.512 vous pouver constater que la valeur de val etant de -50 indiquais que la couleur rouge devrais s'eclaisir et nous pouvons constater un leger changement de couleur au niveau des balafons dont celui de droit est l'originale et celui de droit est l'image modifier.


### 2.passer en noir et blanc (griser l'image)
le taritement de cet fonction a ete d'une difficulter considerable surtout dans la detection des parametres de saisi des utilisateur et dans sont traitement

##### mode d'emploi
commande : gris image.ppm 

    gris reprente la commande appelant la fonction
    image.ppm est le nom du fichier a traiter

##### exemple d'utilisation et resultat
![capture de resultat](capture_resultat/Capture%20d’écran%20du%202025-10-10%2009-23-28.png)

sur cet capture vous pouvez constater que l'utilisteur a entrer comme parametre le nom de son fichier

![capture resultat](capture_resultat/Capture%20d’écran%20du%202025-10-09%2010-25-44.png)

sur cet nouvelle image de Shelton.512 vous pouvez constater que il y'a eu une modification de l'image originale de droit et sa modification de droit.


### 3.afficher la taille d'une image
le taritement de cet fonction a ete d'une difficulter considerable surtout dans la detection des parametres de saisi des utilisateur et dans sont traitement

##### mode d'emploi
commande size nom_fichier.ppm
    size c'est la commande appelant la fonction pouvant calculer la taille de l'image
    nom_fichier.ppm c'est le nom du fichier a inserer

##### exemple d'utilisation et resultat
![capture de la commande](capture_resultat/Capture%20d’écran%20du%202025-10-10%2012-43-49.png)

vous pouvez constater par vous meme quant inserant une image avec la commande size sa nous resort le format, la largeur, la hauteur, et le nombre total de pixel. pour notre image Shelton.512 nous avons une taille de 262144


### 4.decouper une partie de l'image
le taritement de cet fonction a ete d'une difficulter considerable surtout dans la detection des parametres de saisi des utilisateur et dans sont traitement

##### mode d'emploi
commande: cut fichier_source.ppm l1 l2 c1 c2 fichier_resultat
    cut commande appelant la fonction de decoupage de l'image source
    fichier_source.ppm; le fichier a decouper
    l1: le coordonner 1 en hauteur
    l2: le coordonner 2 en hauteur
    c1: le coordonner 1 en largeur
    c2: le coordonner 2 en largeur
    fichier_resultat: le fichier ou se trouvera la partie couper de l'image

bien a savoir:  Le traitement n’est exécuté que si les valeurs de l1, l2 , c1 et c2 sont bonnes ; c’est-à-dire l1 < l2 ≤ hauteur et c1 < c2 ≤ largeur. fichier_resultat.ppm est le nom du fichier dans lequel sera sauvegardé l’image découpée.

##### exemple d'utilisation et resultat
![capture commande](capture_resultat/Capture%20d’écran%20du%202025-10-10%2012-59-09.png)

sut cet image nous pouvaon voir que c'est avec un succes que le fichier a ete decouper. avec les parametre lu

![capture commande](capture_resultat/Capture%20d’écran%20du%202025-10-10%2013-07-15.png)

l'image du resultat montre une imagerie couper de l'image Shelton.512

### 5.negatif d'une image
le taritement de cet fonction a ete d'une difficulter considerable surtout dans la detection des parametres de saisi des utilisateur et dans sont traitement

##### mode d'emploi
commande: neg fichier source.ppm fichier_sortie.ppm

    neg: commande appelant la fonction de de traitement
    fichier_source.ppm: fichier a traiter
    fichier_sortie.ppm: fichier qui resevra la negation du fichier en entrer

##### exemple d'utilisation et mode d'emploie
![capture commande](capture_resultat/Capture%20d’écran%20du%202025-10-10%2013-19-12.png) 

cet image un exemple d'essaie avec la comande neg

![capture resultat](capture_resultat/Capture%20d’écran%20du%202025-10-10%2013-07-15.png)

nous devons avoue que le resultat de la negation de Shelton.512 est un success mais son resultat laisse a desirer.

### 6.filtre median
le taritement de cet fonction a ete d'une difficulter considerable surtout dans la detection des parametres de saisi des utilisateur et dans sont traitement

##### mode d'emploie
commande: fil fichier.ppm fichier_resulat.ppm

    fil: commande appelant la fonction qui applique le filtre median
    fichier.ppm: fichier d'entrer  de l'utilisateur
    fichier_resultat.ppm: fichier de recuperation de la modification

##### exemple d'utilisation et resultat
![capture commande](capture_resultat/Capture%20d’écran%20du%202025-10-10%2013-30-42.png)

sur cet image les commande entrer son parfaite. maintenant ragadons le resultat

![capture resultat](capture_resultat/Capture%20d’écran%20du%202025-10-10%2013-35-16.png)

faut avoue que ici aussi le resultat est bonne mais son ergonnaomie n'est pas presentable

## Structure du projet
- Un fichier source par fonctionnalité
- Un main.c pour le menu et l’appel des fonctions
- Un README.md pour la documentation


## Remarques
- Les images doivent être placées dans le dossier du projet ou un sous-dossier (ex : `images/`).
- Modifie ce README pour ajouter tes propres captures et informations.
- Un main.c pour le menu et l’appel des fonctions
- Un README.md pour la documentation

#   FIN
