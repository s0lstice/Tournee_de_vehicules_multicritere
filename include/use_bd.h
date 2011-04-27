#ifndef USE_BD_H_INCLUDED
#define USE_BD_H_INCLUDED

#include "create_bd.h"

char * nom_lieu(Donnee * data, int id_lieu);
int interet_lieu(Donnee * data, int id_lieu);
int destination_map_arc(Donnee * data, int id_lieu, int id_arc);
int depart_map_arc(Donnee * data, int id_lieu, int id_arc);
int distance_map_arc(Donnee * data, int id_lieu, int id_arc);
int insecurite_map_arc(Donnee * data, int id_lieu, int id_arc);
int nb_arc(Donnee *data, int id_lieu);
int nb_arc_total(Donnee *data);
int nb_lieu(Donnee *data);
int temps_execution(Donnee *data);
void maj_nb_arc(Donnee *data, int id_lieu, int nb_arc);
int interet_map_destination(Donnee *data, int id_lieu, int id_arc);
char *nom_destination(Donnee *data, int id_lieu, int id_arc);
Arc *str_map_arc(Donnee *data, int id_lieu, int id_arc);
void maj_str_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc);
void spr_str_map_arc(Donnee *data, int id_lieu, int id_arc);
Index_arc *pointeur_index_arc(Donnee *data, int id_depart, int id_arrive);
int index_id_arc(Donnee *data, int id_depart, int id_arrive);
int index_nb_arc(Donnee *data, int id_depart, int id_arrive);
int liste_lieu_coef(Donnee *data, int id_table);
Lieu *str_lieu_liste(Donnee *data, int id_table);
Parcourt *str_parcourt(Donnee *data, int id_parcourt);
void all_parcourt(Donnee *data, int nb_reallocation);
int relation_index_lieu(Donnee *data, int id_lieu_depart, int id_lieu_arrive);
int id_lieu(Lieu *lieu);
int nb_visite_lieu(Donnee * data, int id_lieu_depart, int id_lieu_destination);
void maj_nb_visite_lieu(Donnee * data, int id_lieu_depart, int id_lieu_destination, int nb_visite);
Lieu *str_lieu(Donnee *data, int id_lieu);
void add_lieu_solution(Donnee *data, int id_solution, int id_lieu);
int id_last_lieu_solution(Donnee *data, int id_solution);
void add_arc_solution(Donnee *data, int id_solution, int id_lieu_depart, int id_lieu_arrive, int offset);
int nb_lieu_total_solution(Donnee * data, int id_solution);
void maj_nb_lieu_total_solution(Donnee * data, int id_solution, int nb_lieu_totale);
int nb_lieu_solution(Donnee * data, int id_solution);
void maj_nb_lieu_solution(Donnee * data, int id_solution, int nb_lieu);
int existe_map_arc(Donnee *data, int id_lieu, int id_arc);
int existe_solution(Donnee *data);
int id_lieu_liste(Donnee *data, int id_table);
int distance_totale_solution(Donnee * data, int id_solution);
void maj_distance_totale_solution(Donnee * data, int id_solution, int distance);
int insecurite_solution(Donnee * data, int id_solution);
void maj_insecurite_solution(Donnee * data, int id_solution, int insecurite);
int interet_solution(Donnee * data, int id_solution);
void maj_interet_solution(Donnee * data, int id_solution, int interet);
Lieu *depart_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
Lieu *destination_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int distance_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int insecurite_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int interet_destination_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int id_lieu_solution(Donnee * data, int id_solution, int id_lieu);
int id_depart_trajet_solution(Donnee * data, int id_solution, int id_lieu);
int id_destination_trajet_solution(Donnee * data, int id_solution, int id_lieu);
int distance_arc_solution(Donnee *data, int id_solution, int id_arc);
int insecurite_arc_solution(Donnee *data, int id_solution, int id_arc);
int nb_arc_solution(Donnee * data, int id_solution);
int interet_lieu_solution(Donnee *data, int id_solution, int id_lieu);
void unall_solution(Donnee *data);
#endif // USE_BD_H_INCLUDED
