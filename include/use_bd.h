#ifndef USE_BD_H_INCLUDED
#define USE_BD_H_INCLUDED

char * nom_lieu(Donnee * data, int id_lieu);
int interet_lieu(Donnee * data, int id_lieu);
int destination_arc(Donnee * data, int id_lieu, int id_arc);
int depart_arc(Donnee * data, int id_lieu, int id_arc);
int distance_arc(Donnee * data, int id_lieu, int id_arc);
int insecurite_arc(Donnee * data, int id_lieu, int id_arc);
int nb_arc(Donnee *data, int id_lieu);
void maj_nb_arc(Donnee *data, int id_lieu, int nb_arc);
int interet_destination(Donnee *data, int id_lieu,int id_arc);
void maj_nb_destination_lieu(Donnee *data, int id_lieu, int nb_destination);
Arc *pointeur_arc(Donnee *data, int id_lieu, int id_arc);
void maj_pointeur_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc);
void spr_pointeur_arc(Donnee *data, int id_lieu, int id_arc);

#endif // USE_BD_H_INCLUDED
