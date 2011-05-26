#ifndef USE_INDEX_H_INCLUDED
#define USE_INDEX_H_INCLUDED

Index_arc *pointeur_index_arc(Donnee *data, int id_depart, int id_arrive);
int index_id_arc(Donnee *data, int id_depart, int id_arrive);
int index_nb_arc(Donnee *data, int id_depart, int id_arrive);
int relation_index_lieu(Donnee *data, int id_lieu_depart, int id_lieu_arrive);
void unall_index(Donnee *data);

#endif // USE_INDEX_H_INCLUDED
