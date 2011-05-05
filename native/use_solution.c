#include "create_bd.h"
#include "erreur.h"
#include "use_solution.h"
#include "use_bd.h"
#include "use_lieu.h"
#include "use_index.h"
#include "use_map.h"
#include <string.h>
#include <stdlib.h>

Parcourt *str_parcourt(Donnee *data, int id_parcourt){
    return data->solution[id_parcourt];
}

int existe_solution(Donnee *data){
    if(data->solution == NULL) return 0;
    return 1;
}

void all_parcourt(Donnee *data, int nb_reallocation){
    int i;
    Parcourt **temp_doublep;

    /*on redimentionne la table du nombre specifie*/
    temp_doublep = (Parcourt **)realloc(data->solution, nb_reallocation*sizeof(Parcourt*));
    if(temp_doublep == NULL) fatalerreur(data, "all_Parcourt : echeque de l'allocation");
    data->solution = temp_doublep;

    /*definition des nouvelles tables*/
    for(i = data->nb_solution; i < nb_reallocation; ++i){
        /*creation de la solution*/
        data->solution[i] = (Parcourt *)malloc(sizeof(Parcourt));
        if(data->solution[i] == NULL) fatalerreur(data, "all_parcourt : echeque de l'allocation de all_parcourt");

        /*initialisation des caracteristique*/
        data->solution[i]->carac.distance = 0;
        data->solution[i]->carac.insecurite = 0;
        data->solution[i]->carac.interet = 0;
        data->solution[i]->carac.nb_lieux_total = 0;
        data->solution[i]->carac.nb_lieux_utile = 0;
        data->solution[i]->carac.nb_arc = 0;

        /*creation de l'itineraire*/
        data->solution[i]->itineraire = (Lieu **)malloc(sizeof(Lieu*));
        if(data->solution[i]->itineraire == NULL) fatalerreur(data, "all_parcourt : echeque de l'allocation d'itineraire");

        /*creation du trajet*/
        data->solution[i]->trajet = (Arc **)malloc(sizeof(Arc*));
        if(data->solution[i]->trajet == NULL) fatalerreur(data, "all_parcourt : echeque de l'allocation d'trajet");

        /* initialisation des visite a null (n'est pas toujours utile*/
        data->solution[i]->visite = NULL;
    }

    /* mise a jour du nombre de solution*/
    data->nb_solution = nb_reallocation;
}

void add_lieu_solution(Donnee *data, int id_solution, int id_lieu){
    int nb_lieu = data->solution[id_solution]->carac.nb_lieux_total++;
    Lieu **temp;

    /*on augmente l'itineraire de 1*/
    temp = (Lieu **)realloc(data->solution[id_solution]->itineraire, (nb_lieu +1)*sizeof(Lieu *));
    if(temp == NULL) fatalerreur(data, "add_lieu_solution : echeque de la realocation");
    data->solution[id_solution]->itineraire = temp;

    /*on affecte l'adresse du lieu*/
    data->solution[id_solution]->itineraire[nb_lieu] = str_lieu(data, id_lieu);
}

int id_last_lieu_solution(Donnee *data, int id_solution){
    int nb_lieu = data->solution[id_solution]->carac.nb_lieux_total;
    return data->solution[id_solution]->itineraire[nb_lieu -1]->id;
}

void add_arc_solution(Donnee *data, int id_solution, int id_lieu_depart, int id_lieu_arrive, int offset){
    int nb_arc = data->solution[id_solution]->carac.nb_arc++;
    Arc **temp;
    int id_arc;
    Arc *arc;

    /*recupere la position du premier arc disponible*/
    id_arc = index_id_arc(data, id_lieu_depart, id_lieu_arrive);
    arc = str_map_arc(data, id_lieu_depart, id_arc);

    /*on augmante le trajet de 1*/
    temp = (Arc **)realloc(data->solution[id_solution]->trajet, (nb_arc +1)*sizeof(Arc *));
    if(temp == NULL) fatalerreur(data, "add_lieu_solution : echeque de la realocation");
    data->solution[id_solution]->trajet = temp;

    /*on affecte l'adresse de l'arc*/
    data->solution[id_solution]->trajet[nb_arc] = arc;
}

int nb_lieu_total_solution(Donnee * data, int id_solution){
    return data->solution[id_solution]->carac.nb_lieux_total;
}

void maj_nb_lieu_total_solution(Donnee * data, int id_solution, int nb_lieu_totale){
    data->solution[id_solution]->carac.nb_lieux_total = nb_lieu_totale;
}

int nb_lieu_solution(Donnee * data, int id_solution){
    return data->solution[id_solution]->carac.nb_lieux_utile;
}

int nb_arc_solution(Donnee * data, int id_solution){
    return data->solution[id_solution]->carac.nb_arc;
}

void maj_nb_lieu_solution(Donnee * data, int id_solution, int nb_lieu){
    data->solution[id_solution]->carac.nb_lieux_utile = nb_lieu;
}

int distance_totale_solution(Donnee * data, int id_solution){
    return data->solution[id_solution]->carac.distance;
}

void maj_distance_totale_solution(Donnee * data, int id_solution, int distance){
    data->solution[id_solution]->carac.distance = distance;
}

int insecurite_solution(Donnee * data, int id_solution){
    return data->solution[id_solution]->carac.insecurite;
}

void maj_insecurite_solution(Donnee * data, int id_solution, int insecurite){
    data->solution[id_solution]->carac.insecurite = insecurite;
}

int interet_solution(Donnee * data, int id_solution){
    return data->solution[id_solution]->carac.interet;
}

void maj_interet_solution(Donnee * data, int id_solution, int interet){
    data->solution[id_solution]->carac.interet = interet;
}

int id_lieu_solution(Donnee * data, int id_solution, int id_lieu){
    return data->solution[id_solution]->itineraire[id_lieu]->id;
}

int id_depart_trajet_solution(Donnee * data, int id_solution, int id_lieu){
    return data->solution[id_solution]->trajet[id_lieu]->depart->id;
}

int id_destination_trajet_solution(Donnee * data, int id_solution, int id_lieu){
    return data->solution[id_solution]->trajet[id_lieu]->destination->id;
}

int distance_arc_solution(Donnee *data, int id_solution, int id_arc){
    return data->solution[id_solution]->trajet[id_arc]->distance;
}

int insecurite_arc_solution(Donnee *data, int id_solution, int id_arc){
    return data->solution[id_solution]->trajet[id_arc]->insecurite;
}

int interet_lieu_solution(Donnee *data, int id_solution, int id_lieu){
    return data->solution[id_solution]->itineraire[id_lieu]->interet;
}

void unall_solution(Donnee *data){
    int i, nb_lieu_total = nb_lieu(data);

    for(i = 0; i < data->nb_solution; ++i){
        free(data->solution[i]->itineraire);
        free(data->solution[i]->trajet);

        if(data->solution[i]->visite != NULL){

            free(data->solution[i]->visite);
            data->solution[i]->visite = NULL;
        }

        free(data->solution[i]);
    }
    free(data->solution);
}

int existe_visite_solution(Donnee *data, int id_solution){
    if(data->solution[id_solution]->visite == NULL) return 0;
    return 1;
}

void all_visite_solution(Donnee *data, int id_solution){
    int i, nb_lieu_total = nb_lieu(data);

    /*creation du niveau 1 de visite*/
    data->solution[id_solution]->visite = (int*)malloc(nb_lieu_total*sizeof(int));
    if(data->solution[id_solution]->visite == NULL) fatalerreur(data, "all_visite_solution : echeque de l'allocation lv 1");

    for(i = 0; i < nb_lieu_total; ++i)
        data->solution[id_solution]->visite[i] = 0;

}

void initi_visite_solution(Donnee *data, int id_solution){
    int i, nb_solution, id_lieu;
    nb_solution = nb_lieu_total_solution(data, id_solution);

    for(i = 0; i < nb_solution; ++i){
        /*compte le nombre de fois que le lieu est present*/
        id_lieu = data->solution[id_solution]->itineraire[i]->id;
        data->solution[id_solution]->visite[id_lieu]++;


        /*cette estape peut etre remplacé par un teste ; une soustration de 2 à visite[id_lieu][0] ; ou autres.
        n'est pas tres optimise*/
    }
}

int nb_visite_solution(Donnee *data,int id_solution, int id_lieu){
    return data->solution[id_solution]->visite[id_lieu];
}

void maj_nb_visite_solution(Donnee *data,int id_solution, int id_lieu, int value){
    data->solution[id_solution]->visite[id_lieu] = value;
}

void unall_visite_solution(Donnee *data, int id_solution){
    int i, nb_lieu_total = nb_lieu(data);

    free(data->solution[id_solution]->visite);
    data->solution[id_solution]->visite = NULL;
}
