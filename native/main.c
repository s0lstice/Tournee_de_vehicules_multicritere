
/**
 * \file main.c
 * \brief corps du programme.
 * \author Mickael PURET
 * \date 21 mars 2011
 *
 */
/*! mainpage Tournée de véhicules ulticritère
 *
 *\section intro_sec Introduction
 * Ce projet a pour but de crée un solveur de trajet multicritaires.
 * Parmis un ensemble de lieux relié ensemble par des arcs,
 * il faut trouver les chemins qui maximisent l'interet, diminue la distance et l'insecurité.
 * L'ineteret est le poids du lieu, cela corespond à l'importance que l'utilisateur souhaite lui affecter
 * les arcs, chemins entres chaque lieu et caracteriesé par une distance et un insecurité.
 */

#include <stdio.h>
#include <stdlib.h>
#include "create_bd.h"
#include "create_bd_unit.h"
int main(int argc , char * argv [])
{
    Donnee * data;
    if(argc != 1)
        printf("lecture du fichier %s .\n", argv[1]);
    else
        printf("probléme dans les parametres d'entrées\n");

    data = main_create_db(argv[1]);

    test_unit_create_bd(data);

    free_db(data);
    return 0;
}
