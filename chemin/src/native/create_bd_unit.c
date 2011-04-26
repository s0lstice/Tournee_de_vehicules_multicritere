/**
 * \file create_bd_unit.c
 * \brief permet de verifier les donnée en stocké mémoire en les affichant.
 * \author Mickael PURET
 * \date 25 mars 2011
 *
 */

#include "create_bd_unit.h"
#include "use_bd.h"

void test_unit_create_bd(Donnee * data){
    int i, j;

    printf("*** Test de create_bd ***\n");
    printf("\n** Affichage des parametres **\n");
    printf("Temps d'executions du programme : %d s\n", temps_execution(data));
    printf("Nombres de lieux totales : %d\n", nb_lieu(data));
    printf("Nombres d'arcs totales : %d\n", nb_arc_total(data));

    printf("\n** Affichage des lieux **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("Lieu n° %d (%s) d'interet %d avec %d arcs\n", i, nom_lieu(data, i), interet_lieu(data, i), nb_arc(data, i));
    }

    printf("\n** Affichage des arcs **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("* Lieu de depart N° %d (%s)\n", i, data->lieux[i].nom);
            for(j = 0; j < nb_arc(data, i) ; ++j)
            printf("[%d/%d] destination N° %d (%s) d'interet : %d | distance : %d | insecuritee : %d |\n",
                   j+1, nb_arc(data, i),
                   destination_arc(data, i, j),
                   nom_destination(data, i, j),
                   interet_destination(data, i, j),
                   distance_arc(data, i, j),
                   insecurite_arc(data, i, j));
    }

    printf("\n** Affichage des index **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("* Lieu de depart N° %d (%s)\n", i, data->lieux[i].nom);
            for(j = 0; j < nb_lieu(data); ++j){
                if(pointeur_index_arc(data, i, j) == NULL)
                    printf("destination N° %d (%s) PAS DE CORESSPONDANCE\n", j, nom_lieu(data, j));
                else
                    printf("destination N° %d (%s) nombre d'arc : %d position du premier %d\n", j, nom_lieu(data, j), index_nb_arc(data, i, j), index_destination(data, i, j));

            }
    }

    printf("\n** Affichage des iinteret **\n");
    for(i = 0; i < nb_lieu(data); ++i){
        printf("table_interet : interet %d id %d\n", table_interet_interet(data, i), data->table_interet[i].lieu->id);
    }
}
