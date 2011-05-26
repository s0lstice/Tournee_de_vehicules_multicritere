#ifndef USE_BD_H_INCLUDED
#define USE_BD_H_INCLUDED

#include "create_bd.h"
char *nom_lieu(Donnee * data, int id_lieu);
int interet_lieu(Donnee * data, int id_lieu);
int nb_arc(Donnee *data, int id_lieu);
int nb_arc_total(Donnee *data);
int nb_lieu(Donnee *data);
int temps_execution(Donnee *data);
void maj_nb_arc(Donnee *data, int id_lieu, int nb_arc);
int next_lieu(Donnee *data, int id_lieu);
void maj_next_lieu(Donnee *data, int id_lieu, int valeu);

#endif // USE_BD_H_INCLUDED
