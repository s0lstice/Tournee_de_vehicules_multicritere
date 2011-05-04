#ifndef USE_MAP_H_INCLUDED
#define USE_MAP_H_INCLUDED

int destination_map_arc(Donnee * data, int id_lieu, int id_arc);
int depart_map_arc(Donnee * data, int id_lieu, int id_arc);
int distance_map_arc(Donnee * data, int id_lieu, int id_arc);
int insecurite_map_arc(Donnee * data, int id_lieu, int id_arc);
int interet_map_destination(Donnee *data, int id_lieu, int id_arc);
char *nom_destination(Donnee *data, int id_lieu, int id_arc);
Arc *str_map_arc(Donnee *data, int id_lieu, int id_arc);
int existe_map_arc(Donnee *data, int id_lieu, int id_arc);
void maj_str_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc);
Lieu *depart_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
Lieu *destination_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int distance_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int insecurite_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
int interet_destination_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset);
void unall_map(Donnee *data);
void spr_str_map_arc(Donnee *data, int id_lieu, int id_arc);

#endif // USE_MAP_H_INCLUDED
