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
