#include "use_resultat.h"
#include "use_solution.h"
#include <stdlib.h>
#include "erreur.h"

void init_resultat(Donnee *data){
    data->resultat.nb_lieux = 0;
    data->resultat.nb_resultats = NULL;
    data->resultat.resultats = NULL;
}

int nb_lieu_resultats(Donnee *data){
    return data->resultat.nb_lieux;
}


void all_resultats(Donnee *data, int nb_lieux, int nb_ajout){
    int **tmp_doubptr_int;
    int i, nb_l;
    Parcourt ***tmp_tripptr_parcourt;
    Parcourt **tmp_doubptr_parcourt;

    /*ajout de parcourt*/
    if(data->resultat.nb_lieux < nb_lieux){
        /*reallocation de la table des parcourts enxistant en fonction des leux*/
        tmp_doubptr_int = (int**)realloc(data->resultat.nb_resultats, nb_lieux*sizeof(int*));
        if(tmp_doubptr_int == NULL) fatalerreur(data, "all_resultats : echeque de la reallocation de la table des resultats lv1");
        data->resultat.nb_resultats = tmp_doubptr_int;

        for(i = data->resultat.nb_lieux; i < nb_lieux; ++i){
            data->resultat.nb_resultats[i] = (int*)malloc(2*sizeof(int));
            if(data->resultat.nb_resultats[i] == NULL) fatalerreur(data, "all_resultats : echeque de la reallocation de la table des resultats lv2");
            data->resultat.nb_resultats[i][0] = 0;
            data->resultat.nb_resultats[i][1] = 0;
        }

        /*realocation des parcourts*/
        tmp_tripptr_parcourt = (Parcourt ***)realloc(data->resultat.resultats, nb_lieux*sizeof(Parcourt**));
        if(tmp_tripptr_parcourt == NULL) fatalerreur(data, "all_resultats : echeque de la reallocation des parcourts lv1");
        data->resultat.resultats = tmp_tripptr_parcourt;

        for( i = data->resultat.nb_lieux; i < nb_lieux; ++i)
            data->resultat.resultats[i] = NULL;

        /* mise a jour du maximium de lieux utilise*/
        data->resultat.nb_lieux = nb_lieux;
    }

    /*allocation des nouveaux resultat*/
    nb_l = data->resultat.nb_resultats[nb_lieux -1][1] + nb_ajout;
    tmp_doubptr_parcourt = (Parcourt **)realloc(data->resultat.resultats[nb_lieux -1], (nb_l)*sizeof(Parcourt*));
    if(tmp_doubptr_parcourt == NULL) fatalerreur(data, "all_resultats : echeque de la reallocation des parcourts lv2");
    data->resultat.resultats[nb_lieux -1] = tmp_doubptr_parcourt;


    /*initialisation de la partie rajoute*/
    for(i = data->resultat.nb_resultats[nb_lieux -1][1]; i < data->resultat.nb_resultats[nb_lieux -1][1] + nb_ajout; ++i){
        /*creation des desultat*/
        data->resultat.resultats[nb_lieux -1][i] = (Parcourt *)malloc(sizeof(Parcourt));
        if(data->resultat.resultats[nb_lieux -1][i] == NULL) fatalerreur(data, "all_resultats : echeque de l'allocation des resultats vl3");

        /*initialisation des caracteristique*/
        data->resultat.resultats[nb_lieux -1][i]->carac.distance = 0;
        data->resultat.resultats[nb_lieux -1][i]->carac.insecurite = 0;
        data->resultat.resultats[nb_lieux -1][i]->carac.interet = 0;
        data->resultat.resultats[nb_lieux -1][i]->carac.nb_lieux_total = 0;
        data->resultat.resultats[nb_lieux -1][i]->carac.nb_lieux_utile = 0;
        data->resultat.resultats[nb_lieux -1][i]->carac.nb_arc = 0;

        data->resultat.resultats[nb_lieux -1][i]->itineraire  = NULL;
        data->resultat.resultats[nb_lieux -1][i]->trajet = NULL;
        data->resultat.resultats[nb_lieux -1][i]->visite = NULL;
    }

    /*mise a jour du nombre de resultats en fonction du nombre de lieux*/
    data->resultat.nb_resultats[nb_lieux -1][1] += nb_ajout;
}

void cpy_resultat(Donnee *data, int nb_lieux, int id_resultat_destination, int id_resultat_source){
    int i, nb_lieux_total;
    Arc **temp_arc;
    Lieu **temp_lieu;
    Parcourt *destination_resultat = data->resultat.resultats[nb_lieux -1][id_resultat_destination];
    Parcourt *source_resultat = data->resultat.resultats[nb_lieux -1][id_resultat_source];

    if(data->resultat.nb_resultats[nb_lieux -1][1]-data->resultat.nb_resultats[nb_lieux -1][0] < 1)
        all_resultats(data, nb_lieux, 1);

    /*copy des caracteristique*/
    destination_resultat->carac.distance = source_resultat->carac.distance;
    destination_resultat->carac.insecurite = source_resultat->carac.insecurite;
    destination_resultat->carac.interet = source_resultat->carac.interet;
    destination_resultat->carac.nb_arc = source_resultat->carac.nb_arc;
    destination_resultat->carac.nb_lieux_total = source_resultat->carac.nb_lieux_total;
    destination_resultat->carac.nb_lieux_utile = source_resultat->carac.nb_lieux_utile;

    /*copy de l'itineraire*/
    nb_lieux_total = destination_resultat->carac.nb_lieux_total;

    /*on augmente l'itineraire de nb_lieux_total*/
    temp_lieu = (Lieu **)realloc(destination_resultat->itineraire, (nb_lieux_total)*sizeof(Lieu *));
    if(temp_lieu == NULL) fatalerreur(data, "cpy_resultat : echeque de la realocation de itineraire");
    destination_resultat->itineraire = temp_lieu;

    for(i = 0; i < nb_lieux_total; ++i){
        destination_resultat->itineraire[i] = source_resultat->itineraire[i];
    }

    /*copy du trajet*/
    /*on augmante le trajet de nb_lieux_total*/
    temp_arc = (Arc **)realloc(destination_resultat->trajet, (nb_lieux_total -1)*sizeof(Arc *)); //-1 : il y a un arc de moins que de lieu
    if(temp_arc == NULL) fatalerreur(data, "cpy_resultat : echeque de la realocation de trajet");
    destination_resultat->trajet = temp_arc;

    /*on affecte l'adresse de l'arc*/
    for(i = 0; i < nb_lieux_total -1; ++i){
        destination_resultat->trajet[i] = source_resultat->trajet[i];
    }

    data->resultat.nb_resultats[nb_lieux -1][0]++;//augmante de 1 le nombre de resultats utilise
    /*on ne copy pas la table des visites car elle n'est utilisé que pour la generation de chemin de referance*/
}

int cpy_solution_to_resultat(Donnee *data, int nb_lieux, int id_solution){
    int i, nb_lieux_total;
    Arc **temp_arc;
    Lieu **temp_lieu;
    Parcourt *destination_resultat;
    Parcourt *source_solution;
    int id_resultat;

    /*si la table de resultat n'existe pas encore, on la cree*/
    if(data->resultat.nb_lieux < nb_lieux)
        all_resultats(data, nb_lieux, 1);

    id_resultat = nb_resultats_use_by_lieu(data, nb_lieux);

    if(id_resultat >= nb_resultats_all_by_lieu(data, nb_lieux))
        all_resultats(data, nb_lieux, 1);

    destination_resultat = data->resultat.resultats[nb_lieux -1][id_resultat];
    source_solution = data->solution.solution[id_solution];

    /*copy des caracteristique*/
    destination_resultat->carac.distance = source_solution->carac.distance;
    destination_resultat->carac.insecurite = source_solution->carac.insecurite;
    destination_resultat->carac.interet = source_solution->carac.interet;
    destination_resultat->carac.nb_arc = source_solution->carac.nb_arc;
    destination_resultat->carac.nb_lieux_total = source_solution->carac.nb_lieux_total;
    destination_resultat->carac.nb_lieux_utile = source_solution->carac.nb_lieux_utile;

    /*copy de l'itineraire*/
    nb_lieux_total = destination_resultat->carac.nb_lieux_total;

    /*on augmente l'itineraire de nb_lieux_total*/
    temp_lieu = (Lieu **)realloc(destination_resultat->itineraire, (nb_lieux_total)*sizeof(Lieu *));
    if(temp_lieu == NULL) fatalerreur(data, "cpy_solution_to_resultat : echeque de la realocation de itineraire");
    destination_resultat->itineraire = temp_lieu;

    for(i = 0; i < nb_lieux_total; ++i){
        destination_resultat->itineraire[i] = source_solution->itineraire[i];
    }

    /*copy du trajet*/
    /*on augmante le trajet de nb_lieux_total*/
    temp_arc = (Arc **)realloc(destination_resultat->trajet, (nb_lieux_total -1)*sizeof(Arc *)); //-1 : il y a un arc de moins que de lieu
    if(temp_arc == NULL) fatalerreur(data, "cpy_solution_to_resultat : echeque de la realocation de trajet");
    destination_resultat->trajet = temp_arc;

    /*on affecte l'adresse de l'arc*/
    for(i = 0; i < nb_lieux_total -1; ++i){
        destination_resultat->trajet[i] = source_solution->trajet[i];
    }

    data->resultat.nb_resultats[nb_lieux -1][0]++; //augmante de 1 le nombre de resultat utilise
    /*on ne copy pas la table des visites car elle n'est utilisé que pour la generation de chemin de referance*/
    return id_resultat;// renvoi la position de la copie
}

int nb_resultats_all_by_lieu(Donnee *data, int nb_lieux){
    return data->resultat.nb_resultats[nb_lieux-1][1];
}

int nb_resultats_use_by_lieu(Donnee *data, int nb_lieux){
    return data->resultat.nb_resultats[nb_lieux -1][0];
}

int cut_solution_to_resultat(Donnee *data, int nb_lieux, int id_solution){
    int id_resultat;
    Parcourt **tmp;

    id_resultat = nb_resultats_use_by_lieu(data, nb_lieux);

    free(data->resultat.resultats[nb_lieux -1][id_resultat]);

    data->resultat.resultats[nb_lieux -1][id_resultat] = data->solution.solution[id_solution];

    data->resultat.nb_resultats[nb_lieux -1][0]++;

    while(id_solution < data->solution.nb_solution -1){
        data->solution.solution[id_solution] = data->solution.solution[id_solution +1];
        id_solution++;
    }

    if(data->solution.nb_solution == 1){
        data->solution.nb_solution = 0;

        //unall_solution(data, data->solution.nb_solution);
        free(data->solution.solution);
    }
    else{
        data->solution.nb_solution -= 1;
        //unall_solution(data, data->solution.nb_solution);

        tmp = (Parcourt **)realloc(data->solution.solution, (data->solution.nb_solution)*sizeof(Parcourt*));
        if(tmp == NULL) fatalerreur(data, "cut_solution_to_resultat : echeque de la reallocation");
        data->solution.solution = tmp;
    }

    return id_resultat;
}

void unall_resultats(Donnee *data){
    int i, j;

    for(i = 0; i < data->resultat.nb_lieux ; ++i){
        if(data->resultat.resultats[i] != NULL){
            for(j = 0; j < data->resultat.nb_resultats[i][1]; ++j){

                free(data->resultat.resultats[i][j]->itineraire);
                free(data->resultat.resultats[i][j]->trajet);

                if(data->resultat.resultats[i][j]->visite != NULL){
                    free(data->resultat.resultats[i][j]->visite);
                }

                free(data->resultat.resultats[i][j]);
            }

            free(data->resultat.resultats[i]);
        }
    }
    free(data->resultat.resultats);

    for(i = 0; i < data->resultat.nb_lieux; ++i){
        free(data->resultat.nb_resultats[i]);
    }
    free(data->resultat.nb_resultats);
}
