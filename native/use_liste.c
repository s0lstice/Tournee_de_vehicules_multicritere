#include "create_bd.h"
#include "erreur.h"
#include "use_liste.h"
#include <stdlib.h>

int liste_lieu_coef(Donnee *data, int id_table){
    return data->liste_lieu[id_table].coef;
}

Lieu *str_lieu_liste(Donnee *data, int id_table){
    return data->liste_lieu[id_table].lieu;
}

int id_lieu_liste(Donnee *data, int id_table){
    return data->liste_lieu[id_table].lieu->id;
}

void unall_liste(Donnee *data){
    free(data->liste_lieu);
}
