#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "noeud.h"

// void initialiser_noeud(t_noeud* ceci, char* chaine, double distance) {
void initialiser_noeud(t_noeud* ceci, char* chaine) {
    // on vérifie que le noeud n'est pas vide
    if (ceci == NULL) {
        return;
    }

    if (chaine != NULL) {
        ceci->l_espece = malloc(strlen(chaine)+1);
        if (ceci->l_espece != NULL) {
            strcpy(ceci->l_espece, chaine);
            ceci->est_espece = 1;
        }
    } else {
        // cas où on a pas une espèce
        ceci->l_espece = NULL;
        ceci->est_espece = 0;
    }

    // ceci->la_distance = distance;
    // ceci->espece_gauche = NULL;
    // ceci->espece_droite = NULL;
    // // on va dire par défaut que ce n'est ^pas une racine
    // ceci->est_racine = 0;

    ceci->distance_gauche = 0.0;
    ceci->distance_droite = 0.0;
    ceci->espece_gauche = NULL;
    ceci->espece_droite = NULL;
}

void liberer_noeud(a_noeud ceci) {
    if (ceci == NULL) {
        return;
    }

    liberer_noeud(ceci->espece_gauche);
    liberer_noeud(ceci->espece_droite);
    if (ceci->est_espece && ceci->l_espece != NULL) {
        free(ceci->l_espece);
    }

    free(ceci);
}

// void copier_noeud(t_noeud* ceci, t_noeud* cela) {
//     if (ceci == NULL || cela == NULL) {
//         return;
//     }
//     if (ceci->est_espece) {
//         initialiser_noeud(cela, ceci->l_espece, ceci->la_distance);
//     } else {
//         initialiser_noeud(cela, NULL, ceci->la_distance);
//     }
//     cela->est_espece = ceci->est_espece;

//     if (ceci->espece_gauche != NULL) {
//         cela->espece_gauche = (t_noeud*)malloc(sizeof(t_noeud));
//         if (cela->espece_gauche != NULL) {
//             copier_noeud(ceci->espece_gauche, cela->espece_gauche);
//         }
//     }

//     if (ceci->espece_droite != NULL) {
//         cela->espece_droite = (t_noeud*)malloc(sizeof(t_noeud));
//         if (cela->espece_droite != NULL) {
//             copier_noeud(ceci->espece_droite, cela->espece_droite);
//         }
//     }
// }

// on considère que les deux noms existent déjà
void copier_noeud(t_noeud* ceci, t_noeud* cela) {
    if (ceci == NULL || cela == NULL) {
        return;
    }

    // if (ceci->est_espece) {
    //     cela = nouveau_noeud_espece(ceci->l_espece, ceci->la_distance);  
    // } else {
    //     cela = nouveau_noeud_arbre(ceci->la_distance, ceci->espece_gauche, ceci->espece_droite); 
    // }
    
    // cela->est_espece = ceci->est_espece;
    // cela->est_racine = ceci->est_racine;
    
    if (ceci->est_espece) {
        cela->l_espece = malloc(strlen(ceci->l_espece) + 1);
        if (cela->l_espece != NULL) {
            strcpy(cela->l_espece, ceci->l_espece);
        }
    } else {
        cela->l_espece = NULL;
    }

    cela->distance_gauche = ceci->distance_gauche;
    cela->distance_droite = ceci->distance_droite;
    cela->est_espece = ceci->est_espece;

    if (ceci->espece_gauche != NULL) {
        cela->espece_gauche = (t_noeud*)malloc(sizeof(t_noeud));
        if (cela->espece_gauche != NULL) {
            copier_noeud(ceci->espece_gauche, cela->espece_gauche);
        }
    } else {
        cela->espece_gauche = NULL;
    }

    if (ceci->espece_droite != NULL) {
        cela->espece_droite = (t_noeud*)malloc(sizeof(t_noeud));
        if (cela->espece_droite != NULL) {
            copier_noeud(ceci->espece_droite, cela->espece_droite);
        }
    } else {
        cela->espece_droite = NULL;
    }
}

// V1
// a_noeud nouveau_noeud_arbre(t_distance distance, a_noeud gauche, a_noeud droite) {
//     a_noeud noeud = (a_noeud) malloc(sizeof(t_noeud));
//     if (noeud == NULL) {
//         return NULL;
//     }
    
//     // initialiser_noeud(noeud, NULL, distance);
//     initialiser_noeud(noeud, NULL);

//     noeud->espece_gauche = gauche;
//     noeud->espece_droite = droite;
//     // comme c'est pas un noeud espèce on met à 0
//     noeud->est_espece = 0;
//     noeud->est_racine = 0;

//     return noeud;
// }

// V2
a_noeud nouveau_noeud_arbre(a_noeud gauche, a_noeud droite, t_distance distance_gauche, t_distance distance_droite) {
    a_noeud noeud = (a_noeud) malloc(sizeof(t_noeud));
    if (noeud == NULL) {
        return NULL;
    }
    
    initialiser_noeud(noeud, NULL);
    noeud->espece_gauche = gauche;
    noeud->espece_droite = droite;
    noeud->distance_droite = distance_droite;
    noeud->distance_gauche = distance_gauche;
    return noeud;
}

// stockage
// a_noeud nouveau_noeud_racine(a_noeud gauche, a_noeud droite) {
//     a_noeud noeud = (a_noeud) malloc(sizeof(t_noeud));
//     // initialiser_noeud(noeud, NULL, NULL);

//         // cas où on a pas une espèce
//     noeud->l_espece = NULL;
//     noeud->la_distance = 0;

//     noeud->espece_gauche = gauche;
//     noeud->espece_droite = droite;
//     // comme c'est pas un noeud espèce on met à 0
//     noeud->est_espece = 0;
//     noeud->est_racine = 1;

//     return noeud;
// }

// V2
// a_noeud nouveau_noeud_racine(a_noeud gauche, a_noeud droit) {
//     a_noeud noeud = (a_noeud) malloc(sizeof(t_noeud));
//     noeud->espece_gauche = gauche;
//     noeud->espece_droite = droit;
//     noeud->est_espece = 0;
//     noeud->est_racine = 1;
//     return noeud;
// }

// V2
// a_noeud nouveau_noeud_espece(t_nom_espece nom_espece, t_distance distance) {
//     a_noeud noeud = (a_noeud) malloc(sizeof(t_noeud));

//     initialiser_noeud(noeud, nom_espece, distance);

//     // comme c'est pas un noeud espèce on met à 1
//     noeud->est_espece = 1;
//     noeud->espece_gauche = NULL;
//     noeud->espece_droite = NULL;
//     noeud->est_racine = 0;

//     return noeud;
// }

// V3
a_noeud nouveau_noeud_espece(t_nom_espece l_espece) {
    a_noeud noeud = (a_noeud) malloc(sizeof(t_noeud));
    initialiser_noeud(noeud, l_espece);
    return noeud;
}

// int est_espece(a_noeud ceci) {
//     if (ceci == NULL) {
//         return 0;
//     }
//     return ceci->est_espece;
// }

//V2
int est_espece(a_noeud ceci) {
    if (ceci == NULL) {
        return 0;
    }
    return ceci->est_espece;
}

// int est_racine(a_noeud ceci) {
//     if (ceci == NULL) {
//         return 0;
//     }
//     return ceci->est_racine;
// }