#ifndef USE_RESULTAT_H_INCLUDED
#define USE_RESULTAT_H_INCLUDED
#include "create_bd.h"

void all_resultats(Donnee *data, int nb_lieux, int nb_ajout);
void cpy_resultat(Donnee *data, int nb_lieux, int id_resultat_destination, int id_resultat_source);
int cpy_solution_to_resultat(Donnee *data, int nb_lieux, int id_solution);
void init_resultat(Donnee *data);
int nb_lieu_resultats(Donnee *data);
int nb_resultats_use_by_lieu(Donnee *data, int nb_lieux);
int nb_resultats_all_by_lieu(Donnee *data, int nb_lieux);
void unall_resultats(Donnee *data);
int cut_solution_to_resultat(Donnee *data, int nb_lieux, int id_solution);
int distance_arc_resultat(Donnee *data, int nb_lieux, int id_resultat, int id_arc);
int insecurite_arc_resultat(Donnee *data, int nb_lieux, int id_resultat, int id_arc);
int distance_totale_resultat(Donnee * data, int nb_lieux, int id_resultat);
int insecurite_totale_resultat(Donnee * data, int nb_lieux, int id_resultat);
void change_arc_resultat(Donnee *data, int nb_lieux, int id_resultat, int id_arc, int id_depart, int id_destination, int id_offcet);
void create_resultats(Donnee *data, int nb_lieux);
#endif // USE_RESULTAT_H_INCLUDED
