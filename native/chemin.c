#include "chemin.h"
#include "use_bd.h"
#include "use_map.h"
#include "use_index.h"
#include "use_liste.h"
#include "use_solution.h"
#include "erreur.h"
#include <stdlib.h>

/* fonction utilisateur de comparaison fournie a qsort() */
static int tris_croissant (void const *pa, void const *pb)
{
   int const a = *((int const *)pa);
   int const b = *((int const *)pb);
   return a - b;
}

void chemin_base(Donnee *data, int nb_lieu_sol){
    int trouve = 0;
    int nb_lieu_total = 0;
    int id_lieu_depart = 0;
    int id_lieu_arrive = 0;
    int nb_visite = 0;
    int tmp = 0;
    int **distance;
    int i = 0;
    int tantative = 1;

    nb_lieu_total = nb_lieu(data);
    distance = (int**)malloc(nb_lieu_total*sizeof(int*));
    if(distance == NULL) fatalerreur("chemin_base : echeque de l'allocation de distance lv 1");

    for(i = 0; i < nb_lieu_total; ++i){
        distance[i] = (int*)malloc(nb_lieu_total*sizeof(int));
        if(distance == NULL) fatalerreur("chemin_base : echeque de l'allocation de distance lv 2");
    }

    if(existe_solution(data) == 0){
        all_parcourt(data, 1);
        add_lieu_solution(data, 0, 0);
    }

    id_lieu_depart = id_last_lieu_solution(data, 0);
    i = 0;

    while((trouve == 0)&&(tantative != nb_lieu_total)){
        /*recuperation de l'idantifiant du lieu suivant*/
        id_lieu_arrive = id_lieu_liste(data, nb_lieu_sol -1);

        /*destination future*/
        if(relation_index_lieu(data, id_lieu_depart, id_lieu_arrive) == 0){
            /*s'il n'y a pas de chemin pour le lieu suivant on change*/
            nb_lieu_sol++;
            continue;
        }
        else{
            /* si le chemin existe, onverifie que l'n ne tourne pas en rond*/
            nb_visite = nb_visite_lieu(data, id_lieu_depart, id_lieu_arrive);

            /*enregistrement de la distance et du lieu teste*/
            distance[i][0] = distance_arc(data, id_lieu_depart, id_lieu_arrive, 0);
            distance[i++][1] = id_lieu_arrive;

            if( nb_visite == 0){
                trouve = 1;
                break;
            }
            else{
                if(nb_visite == 1){
                    trouve = 2;
                    break;
                }
                else{
                    nb_lieu_sol++;
                }
            }
        }
    }

    if(trouve == 0){
        qsort(distance[0], nb_lieu_total, sizeof(int*), tris_croissant);

        /*on augmente le nombre de fois qu'il a ete visité*/
        maj_nb_visite_lieu(data, id_lieu_depart, id_lieu_arrive, distance[0][1]);
        /*on l'ajoute au chemin de referance*/
        add_lieu_solution(data, 0, id_lieu_arrive);

        /*ajout de l'arc*/
        add_arc_solution(data, 0, id_lieu_depart, id_lieu_arrive, 0);
    }

    /*on augmente le nombre de fois qu'il a ete visité*/
    maj_nb_visite_lieu(data, id_lieu_depart, id_lieu_arrive, nb_visite +1);
    /*on l'ajoute au chemin de referance*/
    add_lieu_solution(data, 0, id_lieu_arrive);

    /*ajout de l'arc*/
    add_arc_solution(data, 0, id_lieu_depart, id_lieu_arrive, 0);

    /*maj nb lieu utile*/
    if(trouve == 0){
        tmp = nb_lieu_solution(data, 0) +1;
        maj_nb_lieu_solution(data, 0, tmp);
    }

    /*maj caracteristique*/
    tmp = distance_totale_solution(data, 0) + distance_arc(data, id_lieu_depart, id_lieu_arrive, 0);
    maj_distance_totale_solution(data, 0, tmp);

    tmp = insecurite_solution(data, 0) + insecurite_arc(data, id_lieu_depart, id_lieu_arrive, 0);
    maj_insecurite_solution(data, 0, tmp);

    tmp = interet_solution(data, 0) + interet_destination_arc(data, id_lieu_depart, id_lieu_arrive, 0);
    maj_interet_solution(data, 0, tmp);

    for(i = 0; i < nb_lieu_total; ++i){
        free(distance[i]);
    }
    free(distance);
}
