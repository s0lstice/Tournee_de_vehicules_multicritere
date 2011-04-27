#ifndef USE_VISITE_H_INCLUDED
#define USE_VISITE_H_INCLUDED

int nb_visite_lieu(Donnee * data, int id_lieu_depart, int id_lieu_destination);
void maj_nb_visite_lieu(Donnee * data, int id_lieu_depart, int id_lieu_destination, int nb_visite);
void unall_visite(Donnee *data);

#endif // USE_VISITE_H_INCLUDED
