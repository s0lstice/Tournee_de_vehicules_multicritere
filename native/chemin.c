/**
 * \file chemin.c
 * \brief ajoute un lieu a la solution de base.
 * \author Mickael PURET
 * \date 24 avril 2011
 *
 */

#include "chemin.h"
#include "use_bd.h"
#include "use_map.h"
#include "use_index.h"
#include "use_liste.h"
#include "use_solution.h"
#include "erreur.h"
#include <stdlib.h>
#include <string.h>

/**
 * \fn static int tris_croissant (void const *pa, void const *pb);
 * \brief fonction utilisateur de comparaison fournie a qsort().
 *
 * \param pointeur sur un tableau a.
 * \param pointeur sur un tableau b.
 * \return une valeur accepté par qsort indiquent si a est supperieur à b.
 */
static int tris_croissant (void const *a, void const *b){
   /*
      Le tableau a trier a des elements de type int *
      On recoit l'adresse de l'element de type int*, soit int **
   */
   int const **ppa = (int const **)a;
   int const **ppb = (int const **)b;

   /* on recupere l'adresse de la ligne  */
   int const *pa = *ppa;
   int const *pb = *ppb;

   /*on teste la colonne 0 */
   return pa[0] - pb[0];
}

/**
 * \fn chemin_base(Donnee *data);
 * \brief ajoute un lieu a la solution de base en respectant la liste coute que coute. en gerant les retours en arriere.
 *
 * \param Un pointeur sur une structure Donnee.
 */
int chemin_base(Donnee *data){
    int nb_lieu_total, id_lieu_depart, id_sol, nb_visite, i, j, id_visite = 0, trouve = 0, tmp;
    int **visite = NULL;

    /* s'il n'y a pas de solution, on en ceree une*/
    if(existe_solution(data) == 0){
        all_parcourt(data, 1);
        add_lieu_solution(data, 0, 0);
    }

    /*initialisation da la table des visites*/
    if(existe_visite_solution(data, 0) == 0){
        all_visite_solution(data, 0);
        initi_visite_solution(data, 0);
    }

    nb_lieu_total = nb_lieu(data); //nombre de lieux dans la solution

    /*si le nombre de lieu utile est maximum on quite*/
    if((nb_lieu_total -1) == nb_lieu_solution(data, 0)) // -1, le depart n'est pas un lieu utile
        return 0; //ajout impossible

    /*decouverte de la solution*/
    id_lieu_depart = id_last_lieu_solution(data, 0); // derniere position dans le parcourt
    id_sol = 0; // identifiant de la solution dans la liste_lieu

    while((trouve == 0)&&(id_sol < nb_lieu_total)){
        /*teste si la destination est accessible*/
        if(relation_index_lieu(data, id_lieu_depart, id_sol) == 1){
            nb_visite = nb_visite_solution(data, 0, id_sol);
            /*la solution est elle dans la liste ?*/
            if(nb_visite == 0){

                trouve = 1;
                /*trouve !!*/
                break;
            }
            else{
                /*creation de la table visite si elle n'existe pas*/
                if(visite == NULL){
                    visite = (int**)malloc(nb_lieu_total*sizeof(int*));
                    if(visite == NULL) fatalerreur(data, "chemin_base : echeque de l'allocation de visite lv 1");

                    for(i = 0; i < nb_lieu_total; ++i){
                        visite[i] = (int*)malloc(2*sizeof(int));
                        if(visite == NULL) fatalerreur(data, "chemin_base : echeque de l'allocation de visite lv 2");
                        for(j = 0; j < 2; ++j){
                            visite[i][j]= 0;
                        }
                    }
                }

                /*mise en memoire au pouvoir etre trie*/
                visite[id_visite][0] = nb_visite_solution(data, 0, id_sol);
                visite[id_visite][1] = id_sol;

                id_visite++;
            }
        }
        id_sol++;
    }

    /* si la solution n'a pas ete trouve => tous les lieux utilent pour ce point de depart sont deja utilise*/
    if(trouve == 0){
        qsort(visite, id_visite, sizeof(visite), tris_croissant);

        id_sol = visite[0][1];
        maj_nb_visite_solution(data, 0, id_sol, visite[0][0] +1);
    }

    /*on augmente le nombre de fois qu'il a ete visité*/
    maj_nb_visite_solution(data, 0, id_sol, nb_visite +1);

    /*on l'ajoute au chemin de referance*/
    add_lieu_solution(data, 0, id_sol);

    /*ajout de l'arc*/
    add_arc_solution(data, 0, id_lieu_depart, id_sol, 0);

    /*maj nb lieu utile*/
    if(trouve == 1){
        tmp = nb_lieu_solution(data, 0) +1;
        maj_nb_lieu_solution(data, 0, tmp);

        tmp = interet_solution(data, 0) + interet_destination_arc(data, id_lieu_depart, id_sol, 0);
        maj_interet_solution(data, 0, tmp);
    }

    /*maj caracteristique*/
    tmp = distance_totale_solution(data, 0) + distance_arc(data, id_lieu_depart, id_sol, 0);
    maj_distance_totale_solution(data, 0, tmp);

    tmp = insecurite_solution(data, 0) + insecurite_arc(data, id_lieu_depart, id_sol, 0);
    maj_insecurite_solution(data, 0, tmp);

    /*desalocation de visite si cette table existe*/
    if(id_visite >= 1){
        for(i = 0; i < nb_lieu_total; ++i)
            free(visite[i]);
        free(visite);
    }

    return 1; //ajout effecté correctement
}
