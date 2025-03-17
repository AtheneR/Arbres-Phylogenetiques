#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "noeud.h"
#include "arbre_binaire.h"
#include "verification_grammaire.h"
extern char mon_caractere;

// on a une fonction pour regarder si un arbre est vide ou non
int est_arbre_vide(a_noeud ceci){
    return ceci==NULL;
}

// on a une fonction pour créer un arbre binaire avec les éléments qu'on lui met en paramètres
a_noeud nouveau_arbre_binaire(t_distance distance_gauche, t_distance distance_droite, t_nom_espece nom_espece, a_noeud gauche, a_noeud droite, int est_espece){
    if (est_espece){
        a_noeud arbre_binaire = nouveau_noeud_espece(nom_espece);
        return arbre_binaire;
    } else {
        a_noeud arbre_binaire = nouveau_noeud_arbre(gauche, droite, distance_gauche, distance_droite);
        return arbre_binaire;
    }
}

// marche pas actuellement
// ça marche seulement pour les arbres qui ont des enfants qui sont des arbres especes, mais pas les arbres imbriqués
int hauteur_arbre_binaire(a_noeud ceci) {
    if (ceci == NULL) {
        return 0;
    }

    if (ceci->est_espece) {
        // printf("\nhauteur espece : 1");
        return 1;
    }
    // printf("\n distance droite : %d\n", ceci->distance_droite);
    int hauteur_gauche = hauteur_arbre_binaire(ceci->espece_gauche);
    int hauteur_droite = hauteur_arbre_binaire(ceci->espece_droite);    
    int max_hauteur = (hauteur_gauche > hauteur_droite) ? hauteur_gauche : hauteur_droite;

    return 1 + max_hauteur;
}

int nb_elements_arbre_binaire(a_noeud ceci){
    if (ceci == NULL) {
        return 0;
    }

    if (ceci->est_espece){
        return 1;
    } else {
        int nb_gauche  = nb_elements_arbre_binaire(ceci->espece_gauche);
        int nb_droite = nb_elements_arbre_binaire(ceci->espece_droite); 
        return nb_gauche  + nb_droite;
    }
}

void detruire_arbre_binaire(a_noeud ceci){
    if (ceci!=NULL){
        detruire_arbre_binaire(ceci->espece_gauche);
        detruire_arbre_binaire(ceci->espece_droite);
        liberer_noeud(ceci);
    }
}

void finaliser_arbre_binaire(a_noeud* ceci){
    if (ceci != NULL && *ceci != NULL) {
        detruire_arbre_binaire(*ceci);
        *ceci = NULL;
    }
}

double recuperer_nombre_a_virgule() {
    double resultat = 0.0;
    double facteur = 1.0;
    int partie_decimale = 0;

    while (mon_caractere != ',' && mon_caractere != ' ' && mon_caractere != ')' && mon_caractere != '\t' && mon_caractere != '\n' && mon_caractere != '\r') {
        if (mon_caractere >= '0' && mon_caractere <= '9') {
            if (partie_decimale) {
                facteur /= 10.0;
                resultat += (mon_caractere - '0') * facteur;
            } else {
                resultat = resultat * 10 + (mon_caractere - '0');
            }
        } else if (mon_caractere == '.') {
            partie_decimale = 1;
        }

        lire_caractere_sans_affichage();
    }

    while (mon_caractere == ' ' || mon_caractere == '\t' || mon_caractere == '\n' || mon_caractere == '\r') {
        lire_caractere_sans_affichage();
    }

    // printf("%.2f", resultat);
    return resultat;
}

char* recuperer_nom() {
    char* nom = (char*)malloc(100 * sizeof(char));
    int i = 0;

    while (mon_caractere != ' ' && mon_caractere != ':' && mon_caractere != '\n' && mon_caractere != '(' && mon_caractere != ',' && mon_caractere != EOF) {
        nom[i++] = mon_caractere;
        // printf("%c", mon_caractere);
        lire_caractere_sans_affichage();
    }
    nom[i] = '\0';
    return nom;
}

a_noeud construire_arbre_phylogenetique() {
    if (est_par_ouvr()) {
        consommer_caractere_sans_affichage('(');
        separation_sans_affichage();

        a_noeud arbre_gauche = construire_arbre_phylogenetique();
        separation_sans_affichage();
        consommer_caractere_sans_affichage(':');
        separation_sans_affichage();

        t_distance distance_gauche = recuperer_nombre_a_virgule();

        consommer_caractere_sans_affichage(',');
        separation_sans_affichage();

        a_noeud arbre_droite = construire_arbre_phylogenetique();
        separation_sans_affichage();
        consommer_caractere_sans_affichage(':');
        separation_sans_affichage();

        t_distance distance_droite = recuperer_nombre_a_virgule();
        separation_sans_affichage();

        consommer_caractere_sans_affichage(')');
        
        return nouveau_arbre_binaire(distance_gauche, distance_droite, NULL, arbre_gauche, arbre_droite, 0);
    } else {
        t_nom_espece nom_espece = recuperer_nom();

        a_noeud espece = (a_noeud)malloc(sizeof(t_noeud));
        initialiser_noeud(espece, nom_espece);

        espece->est_espece = 1;

        return espece;
    }
}

void afficher_arbre(a_noeud ceci) {
    if (ceci == NULL) {
        printf("\nErreur : arbre NULL détecté !\n");
        return;
    }

    if (ceci->est_espece) {
        printf("%s", ceci->l_espece);
    } else {
        printf("(");
        if (ceci->espece_gauche){
            // printf("\npas nul");
        }
        
        afficher_arbre(ceci->espece_gauche);
        printf(":%.2f", ceci->distance_gauche);
        printf(", ");
        afficher_arbre(ceci->espece_droite);
        printf(":%.2f", ceci->distance_droite);
        printf(")");
    }
}