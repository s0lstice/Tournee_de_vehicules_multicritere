#include "use_db2.h"


/**
 * \fn int nb_arc_total(Donnee *data).
 * \brief renvoie le nombre d'arc dans le systeme
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le nombre d'arc dans le systeme.
 */
int nb_arc_total(Donnee *data){
    return data->nb_arcs;
}

/**
 * \fn int nb_lieu(Donnee *data).
 * \brief renvoie le nombre de lieu dans le systeme.
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le nombre de lieux.
 */
int nb_lieu(Donnee *data){
    return data->nb_lieux_total;
}

/**
 * \fn int temps_execution(Donnee *data).
 * \brief renvoie le temps de recherche impartie.
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le temps de recherche impartie.
 */
int temps_execution(Donnee *data){
    return data->temps_execution;
}

/**
 * \fn char tris_coef_lieu(Donnee *data).
 * \brief {c|d} determine si les chemins sont construt par interet croissant ou decroissant
 *
 * \param Un pointeur sur une structure Donnee.
 * \return le caracter inscrit dans le fichier source.
 */
char tris_coef_lieu(Donnee *data){
    return data->ordre_lieu;
}

/**
 * \fn Lieu *str_lieu(Donnee data, id_lieu).
 * \brief permet d'obtenir le lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi un pointeur sur la tructure d'un lieu contenu dans la table des lieux.
 */
Lieu *str_lieu(Donnee *data, int id_lieu){
    return data->lieux[id_lieu];
}

/**
 * \fn int id_lieu(Lieu *lieu).
 * \brief permet d'obtenir l'identifiant du lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi l'indentifiant du lieu.
 */
int id_lieu(Lieu *lieu){
    return lieu->id;
}

/**
 * \fn int interet_lieu(Lieu *lieu).
 * \brief permet d'obtenir l'interet du lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi l'interet du lieu.
 */
int interet_lieu(Lieu *lieu){
    return lieu->interet;
}

/**
 * \fn int nb_arc_lieu(Lieu *lieu).
 * \brief permet d'obtenir le nombre d'arc du lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi le nombre d'arc du lieu.
 */
int nb_arc_lieu(Lieu *lieu){
    return lieu->nb_arc;
}

/**
 * \fn int nb_arc_lieu(Lieu *lieu).
 * \brief permet d'obtenir le nombre d'arc du lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi le nombre d'arc du lieu.
 */
char * nom_lieu(Lieu *lieu){
    return lieu->nom;
}


/**
 * \fn Arc *str_map_arc(Donnee data, id_lieu, id_arc).
 * \brief permet d'obtenir l'arc contenu dans map et definit par un lieu et un identifiant
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \param un identifiant de l'arc
 * \return renvoi un pointeur sur un arc.
 */
Arc *str_map_arc(Donnee *data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc];
}

/**
 * \fn int depart_arc(Arc arc).
 * \brief permet d'obtenir l'identifiant du lieu de depart.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi l'identifiant du lieu de depart.
 */
int depart_arc(Arc *arc){
    return arc->depart;
}

/**
 * \fn int destination_arc(Arc arc).
 * \brief permet d'obtenir l'identifiant du lieu de destination.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi l'identifiant du lieu de destination.
 */
int destination_arc(Arc *arc){
    return arc->destination;
}

/**
 * \fn int distance_arc(Arc arc).
 * \brief permet d'obtenir la distance de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi la distance de l'arc.
 */
int distance_arc(Arc *arc){
    return arc->distance;
}

/**
 * \fn int insecurite_arc(Arc arc).
 * \brief permet d'obtenir l'insecurite de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi l'insecurite de l'arc.
 */
int insecurite_arc(Arc *arc){
    return arc->insecurite;
}

/**
 * \fn int destination_arc(Arc arc).
 * \brief permet d'obtenir le nom du lieu de destination.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un pointeur sur un arc
 * \return renvoi le nom du lieu de destination.
 */
char * nom_destination_arc(Donnee *data, Arc *arc){
    return data->lieux[arc->destination]->nom;
}

/**
 * \fn int destination_arc(Arc arc).
 * \brief permet d'obtenir l'interet du lieu de destination.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un pointeur sur un arc
 * \return renvoi l'inetert du lieu de destination.
 */
char * nom_destination_arc(Donnee *data, Arc *arc){
    return data->lieux[arc->destination]->nom;
}

/**
 * \fn Coef_lieu str_liste(Donnee data, id_lieu).
 * \brief permet d'obtenir la structure d'id_lieu contenu dans la liste de lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi un pointeur sur la structure Coef_lieu.
 */
Coef_lieu *str_liste(Donnee *data, id_lieu){
    return data->liste_lieu[id_lieu];
}

/**
 * \fn int coef_liste(Coef_lieu coef_lieu).
 * \brief permet d'obtenir le coeficient associé a un lieu.
 *
 * \param la structure de type Coef_lieu.
 * \return renvoi le coeficient.
 */
int coef_liste(Coef_lieu *coef_lieu){
    return coef_lieu->coef;
}

/**
 * \fn Lieu *lieu_liste(Coef_lieu coef_lieu).
 * \brief permet d'obtenir le lieu associe au coeficient.
 *
 * \param la structure de type Coef_lieu.
 * \return renvoi un structure de type lieu.
 */
Lieu *lieu_liste(Coef_lieu *coef_lieu){
    return coef_lieu->lieu;
}
