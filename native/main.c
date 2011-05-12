
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
    time_t debut, fin, stop;
    int i;

    if(argc != 1)
        printf("lecture du fichier %s .\n", argv[1]);
    else
        printf("probléme dans les parametres d'entrées\n");

    printf("debut : %ld \n", time(&debut));
    data = main_create_db(argv[1]);

    stop = debut + temps_execution(data);
    i = 2;

    while((time(NULL) < stop) && (chemin_base(data) == 1)){
        all_parcourt(data, i);
        cpy_solution(data, i-1, 0);
        ++i;
    }

    print_result(data);

    free_db(data);
    printf("fin : %ld \n", time(&fin));
    printf("duree : %ld \n", fin - debut);
    return 0;
}
