#ifndef USE_BD_H_INCLUDED
#define USE_BD_H_INCLUDED

#include "create_bd.h"

char * nom_lieu(Donnee * data, int id_lieu);
int interet_lieu(Donnee * data, int id_lieu);
int destination_arc(Donnee * data, int id_lieu, int id_arc);
int depart_arc(Donnee * data, int id_lieu, int id_arc);
int distance_arc(Donnee * data, int id_lieu, int id_arc);
int insecurite_arc(Donnee * data, int id_lieu, int id_arc);
int nb_arc(Donnee *data, int id_lieu);
int nb_arc_total(Donnee *data);
int nb_lieu(Donnee *data);
int temps_execution(Donnee *data);
void maj_nb_arc(Donnee *data, int id_lieu, int nb_arc);
int interet_destination(Donnee *data, int id_lieu, int id_arc);
char *nom_destination(Donnee *data, int id_lieu, int id_arc);
Arc *pointeur_map_arc(Donnee *data, int id_lieu, int id_arc);
void maj_pointeur_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc);
void spr_pointeur_map_arc(Donnee *data, int id_lieu, int id_arc);
Index_arc *pointeur_index_arc(Donnee *data, int id_depart, int id_arrive);
int index_destination(Donnee *data, int id_depart, int id_arrive);
int index_nb_arc(Donnee *data, int id_depart, int id_arrive);
int liste_lieu_interet(Donnee *data, int id_table);

Lieu *liste_lieu_lieu(Donnee *data, int id_table);





#endif // USE_BD_H_INCLUDED
