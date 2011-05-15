
/**
 * \file main.c
 * \brief corps du programme.
 * \author Mickael PURET
 * \date 21 mars 2011
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "create_bd.h"
#include "resultats.h"
#include "chemin.h"
#include "use_bd.h"
#include <time.h>
#include "use_solution.h"

int main(int argc , char * argv [])
{
    Donnee * data;
    time_t debut, fin, stop, temps_recherche;
    int i, j;

    if(argc != 1)
        printf("lecture du fichier %s .\n", argv[1]);
    else
        printf("probléme dans les parametres d'entrées\n");

    printf("debut : %ld \n", time(&debut));
    data = main_create_db(argv[1]);

    stop = debut + temps_execution(data);

    while((time(NULL) < stop) && (chemin_base(data) == 1)){
        j = nb_solution(data);
        all_parcourt(data, 1);
        cpy_solution(data, j, 0);
        i = nb_solution(data);
        //create_chemin_solution(data, j-1, i);
    }

    time(&temps_recherche);

    print_result(data);

    free_db(data);
    printf("fin : %ld \n", time(&fin));
    printf("temps de recherche : %ld\n", temps_recherche - debut);
    printf("duree : %ld \n", fin - debut);
    return 0;
}
