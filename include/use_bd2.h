#ifndef USE_BD2_H_INCLUDED
#define USE_BD2_H_INCLUDED

#include "create_bd.h"

int nb_arc_total(Donnee *data);
int nb_lieu(Donnee *data);
int temps_execution(Donnee *data);
char tris_coef_lieu(Donnee *data);
Lieu *str_lieu(Donnee data, int id_lieu);
int id_lieu(Lieu *lieu);
int interet_lieu(Lieu *lieu);
int nb_arc_lieu(Lieu *lieu);
char * nom_lieu(Lieu *lieu);
Arc *str_map_arc(Donnee data, int id_lieu, int id_arc);
int depart_arc(Arc arc);
int destination_arc(Arc arc);
int distance_arc(Arc arc);
int insecurite_arc(Arc arc);
Coef_lieu str_liste(Donnee data, int id_lieu);
int coef_liste(Coef_lieu coef_lieu);
Lieu *lieu_liste(Coef_lieu coef_lieu);

#endif // USE_BD2_H_INCLUDED
