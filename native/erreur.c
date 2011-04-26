#include "erreur.h"
#include <stdio.h>
#include <stdlib.h>

void fatalerreur(char * txt){
    printf("[erreur] %s", txt);
    exit(-1);
}
