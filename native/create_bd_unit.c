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
    printf("Temps d'executions du programme : %d s\n", data->temps_execution);
    printf("Nombres de lieux totales : %d\n", data->nb_lieux_total);
    printf("Nombres d'arcs totales : %d\n", data->nb_arcs);

    printf("\n** Affichage des lieux **\n");
    for(i = 0; i < data->nb_lieux_total; ++i){
        printf("Lieu n° %d (%s) d'interet %d avec %d chemins sortant\n", i, data->lieux[i].nom, data->lieux[i].interet, data->lieux[i].nb_arc);
    }

    printf("\n** Affichage des arcs **\n");
    for(i = 0; i < data->nb_lieux_total; ++i){
        printf("* Lieu de depart N° %d (%s)\n", i, data->lieux[i].nom);
            for(j = 0; j < data->lieux[i].nb_arc ; ++j)
            printf("[%d/%d] destination N° %d (%s) d'interet : %d | distance : %d | insecuritee : %d |\n",
                   j+1, data->lieux[i].nb_arc,
                   data->map[i][j]->destination,
                   data->lieux[data->map[i][j]->destination].nom,
                   interet_lieu(data, destination_arc(data, i, j)),
                   data->map[i][j]->distance,
                   data->map[i][j]->insecurite);
    }
}
