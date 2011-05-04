#ifndef USE_SOLUTION_H_INCLUDED
#define USE_SOLUTION_H_INCLUDED

Parcourt *str_parcourt(Donnee *data, int id_parcourt);
int existe_solution(Donnee *data);
void all_parcourt(Donnee *data, int nb_reallocation);
void add_lieu_solution(Donnee *data, int id_solution, int id_lieu);
int id_last_lieu_solution(Donnee *data, int id_solution);
void add_arc_solution(Donnee *data, int id_solution, int id_lieu_depart, int id_lieu_arrive, int offset);
int nb_lieu_total_solution(Donnee * data, int id_solution);
void maj_nb_lieu_total_solution(Donnee * data, int id_solution, int nb_lieu_totale);
int nb_lieu_solution(Donnee * data, int id_solution);
int nb_arc_solution(Donnee * data, int id_solution);
void maj_nb_lieu_solution(Donnee * data, int id_solution, int nb_lieu);
int distance_totale_solution(Donnee * data, int id_solution);
void maj_distance_totale_solution(Donnee * data, int id_solution, int distance);
int insecurite_solution(Donnee * data, int id_solution);
void maj_insecurite_solution(Donnee * data, int id_solution, int insecurite);
int interet_solution(Donnee * data, int id_solution);
void maj_interet_solution(Donnee * data, int id_solution, int interet);
int id_lieu_solution(Donnee * data, int id_solution, int id_lieu);
int id_depart_trajet_solution(Donnee * data, int id_solution, int id_lieu);
int id_destination_trajet_solution(Donnee * data, int id_solution, int id_lieu);
int distance_arc_solution(Donnee *data, int id_solution, int id_arc);
int insecurite_arc_solution(Donnee *data, int id_solution, int id_arc);
int interet_lieu_solution(Donnee *data, int id_solution, int id_lieu);
void unall_solution(Donnee *data);
void all_visite_solution(Donnee *data, int id_solution);
void initi_visite_solution(Donnee *data, int id_solution);
int nb_visite_solution(Donnee *data, int id_solution, int id_lieu);
void maj_nb_visite_solution(Donnee *data, int id_solution, int id_lieu, int value);
int nb_passage_solution(Donnee *data,int id_solution, int id_lieu);
void maj_nb_passage_solution(Donnee *data,int id_solution, int id_lieu, int value);
int existe_visite_solution(Donnee *data, int id_solution);

#endif // USE_SOLUTION_H_INCLUDED
