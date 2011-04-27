#include "create_bd.h"
#include "erreur.h"
#include "use_visite.h"
#include <stdlib.h>

int nb_visite_lieu(Donnee * data, int id_lieu_depart, int id_lieu_destination){
    return data->visite_lieu[id_lieu_depart][id_lieu_destination];
}

void maj_nb_visite_lieu(Donnee * data, int id_lieu_depart, int id_lieu_destination, int nb_visite){
    data->visite_lieu[id_lieu_depart][id_lieu_destination] = nb_visite;
}

void unall_visite(Donnee *data){
    int i;
    for(i = 0; i < data->nb_lieux_total; ++i){
        free(data->visite_lieu[i]);
    }
    free(data->visite_lieu);
}
