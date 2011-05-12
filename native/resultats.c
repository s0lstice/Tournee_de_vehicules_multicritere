/**
 * \file resultat.c
 * \brief affiche l'ensemble des donnees contenuent en memoire.
 * \author Mickael PURET
 * \date 25 mars 2011
 *
 */

#include "resultats.h"
#include "use_bd.h"
#include "use_map.h"
#include "use_index.h"
#include "use_solution.h"
#include "use_liste.h"
#include "use_bd.h"

/**
 * \fn static FILE * open_file(char * path)
 * \brief affiche l'ensemble des donnees contenuent en memoire..
 *
 * \param Un pointeur sur une structure Donnee.
 */
void print_result(Donnee * data){
    int i, j;

    /*afficage des paramtres*/
    printf("*** Test de create_bd ***\n");
    printf("\n** Affichage des parametres **\n");
    printf("Temps d'executions du programme : %d s\n", temps_execution(data));
    printf("Nombres de lieux totales : %d\n", nb_lieu(data));
    printf("Nombres d'arcs totales : %d\n", nb_arc_total(data));

    /*affichage des lieux*/
    printf("\n** Affichage des lieux **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("Lieu n° %d (%s) d'interet %d avec %d arcs\n", i, nom_lieu(data, i), interet_lieu(data, i), nb_arc(data, i));
    }

    /*affichage des arcs*/
    printf("\n** Affichage des arcs **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("* Lieu de depart N° %d (%s)\n", i, data->lieux[i].nom);
            for(j = 0; j < nb_arc(data, i) ; ++j)
            printf("[%d/%d] destination N° %d (%s) d'interet : %d | distance : %d | insecuritee : %d |\n",
                   j+1, nb_arc(data, i),
                   destination_map_arc(data, i, j),
                   nom_destination(data, i, j),
                   interet_map_destination(data, i, j),
                   distance_map_arc(data, i, j),
                   insecurite_map_arc(data, i, j));
    }

    /*affichage de l'index*/
    printf("\n** Affichage des index **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("* Lieu de depart N° %d (%s)\n", i, data->lieux[i].nom);
            for(j = 0; j < nb_lieu(data); ++j){
                if(pointeur_index_arc(data, i, j) == NULL)
                    printf("destination N° %d (%s) PAS DE CORESSPONDANCE\n", j, nom_lieu(data, j));
                else
                    printf("destination N° %d (%s) nombre d'arc : %d position du premier %d\n", j, nom_lieu(data, j), index_nb_arc(data, i, j), index_id_arc(data, i, j));

            }
    }

    /*affichage de la liste tree*/
    printf("\n** Affichage des interets **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("liste_lieu : interet %d id %d\n", liste_lieu_coef(data, i), data->liste_lieu[i].lieu->id);
    }

    /*affichage des chemins*/
    for(i = 0; i < nb_solution(data); ++i){
        printf("\n*** chemin n° %d ***\n",i);
        if(existe_solution(data) == 1){
            printf("**cara : \n distance : %d \n insecurite : %d \n interet : %d \n nb_lieux_total : %d \n nb_lieux_utile : %d\n",
                data->solution[i]->carac.distance,
                data->solution[i]->carac.insecurite,
                data->solution[i]->carac.interet,
                data->solution[i]->carac.nb_lieux_total,
                data->solution[i]->carac.nb_lieux_utile);
            for(j = 0; j < nb_arc_solution(data, i); ++j){
                printf("**trajet : \n depart : %d \n destination : %d \n distance : %d \n insecurite : %d \n",
                    id_depart_trajet_solution(data, i, j),
                    id_destination_trajet_solution(data, i, j),
                    distance_arc_solution(data, i, j),
                    insecurite_arc_solution(data, i, j));
            }
            for(j = 0; j < nb_lieu_total_solution(data, i); ++j){
                printf("**lieu : \n id_lieu : %d \n interet : %d \n",
                    id_lieu_solution(data, i, j),
                    interet_lieu_solution(data, i, j));
            }
        }
        else
            printf("/!\\ il n'y a pas de solutions /!\\ \n");
    }
}
