#include "create_bd.h"
#include "erreur.h"
#include "use_solution.h"
#include "use_bd.h"
#include "use_lieu.h"
#include "use_index.h"
#include "use_map.h"
#include <string.h>
#include <stdlib.h>

void init_solution(Donnee *data){
    data->solution.nb_solution = 0;
    data->solution.solution = NULL;
}

int nb_solution(Donnee *data){
    return data->solution.nb_solution;
}

Parcourt *str_parcourt(Donnee *data, int id_parcourt){
    return data->solution.solution[id_parcourt];
}

int existe_solution(Donnee *data){
    if(data->solution.solution == NULL) return 0;
    return 1;
}

void all_parcourt(Donnee *data, int nb_ajout){
    int nb_solution_totale = nb_solution(data);
    int nb_reallocation = nb_solution_totale + nb_ajout;
    int i;
    Parcourt **temp_doublep;

    /*on redimentionne la table du nombre specifie*/
    temp_doublep = (Parcourt **)realloc(data->solution.solution, nb_reallocation*sizeof(Parcourt*));
    if(temp_doublep == NULL) fatalerreur(data, "all_Parcourt : echeque de l'allocation");
    data->solution.solution = temp_doublep;

    /*definition des nouvelles tables*/
    for(i = data->solution.nb_solution; i < nb_reallocation; ++i){
        /*creation de la solution*/
        data->solution.solution[i] = (Parcourt *)malloc(sizeof(Parcourt));
        if(data->solution.solution[i] == NULL) fatalerreur(data, "all_parcourt : echeque de l'allocation de all_parcourt");

        /*initialisation des caracteristique*/
        data->solution.solution[i]->carac.distance = 0;
        data->solution.solution[i]->carac.insecurite = 0;
        data->solution.solution[i]->carac.interet = 0;
        data->solution.solution[i]->carac.nb_lieux_total = 0;
        data->solution.solution[i]->carac.nb_lieux_utile = 0;
        data->solution.solution[i]->carac.nb_arc = 0;

        data->solution.solution[i]->itineraire = NULL;
        data->solution.solution[i]->trajet = NULL;
        data->solution.solution[i]->visite = NULL;
    }

    /* mise a jour du nombre de solution*/
    data->solution.nb_solution = nb_reallocation;
}

void unall_parcourt(Donnee *data, int nb_suppretion){
    int nb_solution_totale = nb_solution(data);
    int nb_solution_restant = nb_solution_totale - nb_suppretion;
    int i;
    Parcourt **temp_doublep;

    for(i = nb_solution_restant; i < nb_solution_totale; ++i){
        if(data->solution.solution[i]->visite != NULL)
            free(data->solution.solution[i]->visite);

        free(data->solution.solution[i]->trajet);

        free(data->solution.solution[i]->itineraire);

        free(data->solution.solution[i]);
    }

    temp_doublep = (Parcourt **)realloc(data->solution.solution, nb_solution_restant*sizeof(Parcourt*));
    if(temp_doublep == NULL) fatalerreur(data, "unall_parcourt : echeque de la reallocation");
    data->solution.solution = temp_doublep;

    data->solution.nb_solution = nb_solution_restant;
}

void add_lieu_solution(Donnee *data, int id_solution, int id_lieu){
    int nb_lieu = data->solution.solution[id_solution]->carac.nb_lieux_total++;
    Lieu **temp;

    /*on augmente l'itineraire de 1*/
    temp = (Lieu **)realloc(data->solution.solution[id_solution]->itineraire, (nb_lieu +1)*sizeof(Lieu *));
    if(temp == NULL) fatalerreur(data, "add_lieu_solution : echeque de la realocation");
    data->solution.solution[id_solution]->itineraire = temp;

    /*on affecte l'adresse du lieu*/
    data->solution.solution[id_solution]->itineraire[nb_lieu] = str_lieu(data, id_lieu);
}

int id_last_lieu_solution(Donnee *data, int id_solution){
    int nb_lieu = data->solution.solution[id_solution]->carac.nb_lieux_total;
    return data->solution.solution[id_solution]->itineraire[nb_lieu -1]->id;
}

void add_arc_solution(Donnee *data, int id_solution, int id_lieu_depart, int id_lieu_arrive, int offset){
    int nb_arc = data->solution.solution[id_solution]->carac.nb_arc++;
    Arc **temp;
    int id_arc;
    Arc *arc;

    /*recupere la position du premier arc disponible*/
    id_arc = index_id_arc(data, id_lieu_depart, id_lieu_arrive);
    arc = str_map_arc(data, id_lieu_depart, id_arc);

    /*on augmante le trajet de 1*/
    temp = (Arc **)realloc(data->solution.solution[id_solution]->trajet, (nb_arc +1)*sizeof(Arc *));
    if(temp == NULL) fatalerreur(data, "add_lieu_solution : echeque de la realocation");
    data->solution.solution[id_solution]->trajet = temp;

    /*on affecte l'adresse de l'arc*/
    data->solution.solution[id_solution]->trajet[nb_arc] = arc;
}

int nb_lieu_total_solution(Donnee * data, int id_solution){
    return data->solution.solution[id_solution]->carac.nb_lieux_total;
}

void maj_nb_lieu_total_solution(Donnee * data, int id_solution, int nb_lieu_totale){
    data->solution.solution[id_solution]->carac.nb_lieux_total = nb_lieu_totale;
}

int nb_lieu_solution(Donnee * data, int id_solution){
    return data->solution.solution[id_solution]->carac.nb_lieux_utile;
}

int nb_arc_solution(Donnee * data, int id_solution){
    return data->solution.solution[id_solution]->carac.nb_arc;
}

void maj_nb_lieu_solution(Donnee * data, int id_solution, int nb_lieu){
    data->solution.solution[id_solution]->carac.nb_lieux_utile = nb_lieu;
}

int distance_totale_solution(Donnee * data, int id_solution){
    return data->solution.solution[id_solution]->carac.distance;
}

void maj_distance_totale_solution(Donnee * data, int id_solution, int distance){
    data->solution.solution[id_solution]->carac.distance = distance;
}

int insecurite_solution(Donnee * data, int id_solution){
    return data->solution.solution[id_solution]->carac.insecurite;
}

void maj_insecurite_solution(Donnee * data, int id_solution, int insecurite){
    data->solution.solution[id_solution]->carac.insecurite = insecurite;
}

int interet_solution(Donnee * data, int id_solution){
    return data->solution.solution[id_solution]->carac.interet;
}

void maj_interet_solution(Donnee * data, int id_solution, int interet){
    data->solution.solution[id_solution]->carac.interet = interet;
}

int id_lieu_solution(Donnee * data, int id_solution, int id_lieu){
    return data->solution.solution[id_solution]->itineraire[id_lieu]->id;
}

int id_depart_trajet_solution(Donnee * data, int id_solution, int id_lieu){
    return data->solution.solution[id_solution]->trajet[id_lieu]->depart->id;
}

int id_destination_trajet_solution(Donnee * data, int id_solution, int id_lieu){
    return data->solution.solution[id_solution]->trajet[id_lieu]->destination->id;
}

int distance_arc_solution(Donnee *data, int id_solution, int id_arc){
    return data->solution.solution[id_solution]->trajet[id_arc]->distance;
}

int insecurite_arc_solution(Donnee *data, int id_solution, int id_arc){
    return data->solution.solution[id_solution]->trajet[id_arc]->insecurite;
}

int interet_lieu_solution(Donnee *data, int id_solution, int id_lieu){
    return data->solution.solution[id_solution]->itineraire[id_lieu]->interet;
}

void unall_solution(Donnee *data, int id_solution){

    free(data->solution.solution[id_solution]->itineraire);
    free(data->solution.solution[id_solution]->trajet);

    if(data->solution.solution[id_solution]->visite != NULL){

        free(data->solution.solution[id_solution]->visite);
        data->solution.solution[id_solution]->visite = NULL;
    }

    free(data->solution.solution[id_solution]);

    data->solution.solution[id_solution] = NULL;
}

void unall_solutions(Donnee *data){
    int i;

    for(i = 0; i < data->solution.nb_solution; ++i){
        free(data->solution.solution[i]->itineraire);
        free(data->solution.solution[i]->trajet);

        if(data->solution.solution[i]->visite != NULL){

            free(data->solution.solution[i]->visite);
            data->solution.solution[i]->visite = NULL;
        }

        free(data->solution.solution[i]);
    }
    free(data->solution.solution);
}

int existe_visite_solution(Donnee *data, int id_solution){
    if(data->solution.solution[id_solution]->visite == NULL) return 0;
    return 1;
}

void all_visite_solution(Donnee *data, int id_solution){
    int i, nb_lieu_total = nb_lieu(data);

    /*creation du niveau 1 de visite*/
    data->solution.solution[id_solution]->visite = (int*)malloc(nb_lieu_total*sizeof(int));
    if(data->solution.solution[id_solution]->visite == NULL) fatalerreur(data, "all_visite_solution : echeque de l'allocation lv 1");

    for(i = 0; i < nb_lieu_total; ++i)
        data->solution.solution[id_solution]->visite[i] = 0;

}

void initi_visite_solution(Donnee *data, int id_solution){
    int i, nb_solution, id_lieu;
    nb_solution = nb_lieu_total_solution(data, id_solution);

    for(i = 0; i < nb_solution; ++i){
        /*compte le nombre de fois que le lieu est present*/
        id_lieu = data->solution.solution[id_solution]->itineraire[i]->id;
        data->solution.solution[id_solution]->visite[id_lieu]++;
    }
}

int nb_visite_solution(Donnee *data,int id_solution, int id_lieu){
    return data->solution.solution[id_solution]->visite[id_lieu];
}

void maj_nb_visite_solution(Donnee *data,int id_solution, int id_lieu, int value){
    data->solution.solution[id_solution]->visite[id_lieu] = value;
}

void unall_visite_solution(Donnee *data, int id_solution){
    free(data->solution.solution[id_solution]->visite);
    data->solution.solution[id_solution]->visite = NULL;
}

void cpy_solution(Donnee *data, int id_solution_destination, int id_solution_source){
    int i, nb_lieux_total;
    Arc **temp_arc;
    Lieu **temp_lieu;
    Parcourt *destination_solution = data->solution.solution[id_solution_destination];
    Parcourt *source_solution = data->solution.solution[id_solution_source];

    /*copy des caracteristique*/
    destination_solution->carac.distance = source_solution->carac.distance;
    destination_solution->carac.insecurite = source_solution->carac.insecurite;
    destination_solution->carac.interet = source_solution->carac.interet;
    destination_solution->carac.nb_arc = source_solution->carac.nb_arc;
    destination_solution->carac.nb_lieux_total = source_solution->carac.nb_lieux_total;
    destination_solution->carac.nb_lieux_utile = source_solution->carac.nb_lieux_utile;

    /*copy de l'itineraire*/
    nb_lieux_total = destination_solution->carac.nb_lieux_total;

    /*on augmente l'itineraire de nb_lieux_total*/
    temp_lieu = (Lieu **)realloc(destination_solution->itineraire, (nb_lieux_total)*sizeof(Lieu *));
    if(temp_lieu == NULL) fatalerreur(data, "cpy_solution : echeque de la realocation de itineraire");
    destination_solution->itineraire = temp_lieu;

    for(i = 0; i < nb_lieux_total; ++i){
        destination_solution->itineraire[i] = source_solution->itineraire[i];
    }

    /*copy du trajet*/
    /*on augmante le trajet de nb_lieux_total*/
    temp_arc = (Arc **)realloc(destination_solution->trajet, (nb_lieux_total -1)*sizeof(Arc *)); //-1 : il y a un arc de moins que de lieu
    if(temp_arc == NULL) fatalerreur(data, "cpy_solution : echeque de la realocation de trajet");
    destination_solution->trajet = temp_arc;

    /*on affecte l'adresse de l'arc*/
    for(i = 0; i < nb_lieux_total -1; ++i){
        destination_solution->trajet[i] = source_solution->trajet[i];
    }

    /*on ne copy pas la table des visites car elle n'est utilisé que pour la generation de chemin de referance*/
}

void change_arc_solution(Donnee *data, int id_solution, int id_arc, int id_depart, int id_destination, int id_offcet){
    data->solution.solution[id_solution]->carac.distance = data->solution.solution[id_solution]->carac.distance - distance_arc_solution(data, id_solution, id_arc) + distance_arc(data, id_depart, id_destination, id_offcet);
    data->solution.solution[id_solution]->carac.insecurite =  data->solution.solution[id_solution]->carac.insecurite - insecurite_arc_solution(data, id_solution, id_arc) + insecurite_arc(data, id_depart, id_destination, id_offcet);

    data->solution.solution[id_solution]->trajet[id_arc] = ptr_arc(data, id_depart, id_destination, id_offcet);
}

/*
void create_chemin_solution(Donnee *data, int debut_generation, int fin_generation){
    //int nb_create_solution = fin_generation - debut_generation;
    int nb_arc_ref;
    int nb_arc_depart_destination;
    int id_solution, id_lieu, id_arc;
    int distance_new, insecurite_new;
    int distance_ref, insecurite_ref;
    int nb_solution_vide = 0, curseur_solution_vide;
    int lieu_depart, lieu_destination;

    for(id_solution = debut_generation; id_solution < fin_generation; ++id_solution){
        nb_arc_ref = nb_arc_solution(data, id_solution);

        distance_ref = distance_totale_solution(data, id_solution);
        insecurite_ref = insecurite_solution(data, id_solution);

        for(id_lieu = 0; id_lieu < nb_arc_ref; ++id_lieu){
            lieu_depart = id_depart_trajet_solution(data, id_solution, id_lieu);
            lieu_destination = id_destination_trajet_solution(data, id_solution, id_lieu);

            nb_arc_depart_destination = index_nb_arc(data, lieu_depart, lieu_destination);

            if(nb_arc_depart_destination == 1) continue; //s'il n'y  qu'un arc, on passe au lieu suivant
*/
            /*allocation de nb_arc_depart_destination solution*/
/*            curseur_solution_vide = nb_solution(data);
            all_parcourt(data, nb_arc_depart_destination - nb_solution_vide);
            nb_solution_vide = nb_arc_depart_destination;

            for(id_arc = 1; id_arc < nb_arc_depart_destination; ++id_arc){ //depart de l'arc 1 car on a deja l'arc 0
                distance_new = distance_ref - distance_arc_solution(data, id_solution, id_lieu) + distance_arc(data, lieu_depart, lieu_destination, id_arc);
                insecurite_new =  insecurite_ref - insecurite_arc_solution(data, id_solution, id_lieu) + insecurite_arc(data, lieu_depart, lieu_destination, id_arc);

                if((distance_ref < distance_new)&&(insecurite_ref < insecurite_new)){
                    continue;
                }
                if((distance_ref > distance_new)&&(insecurite_ref > insecurite_new)){
                    change_arc_solution(data, id_solution, id_lieu, lieu_depart, lieu_destination, id_arc);

                    distance_ref = distance_totale_solution(data, id_solution);
                    insecurite_ref = insecurite_solution(data, id_solution);
                }
                else{
                    cpy_solution(data, curseur_solution_vide, id_solution);
                    change_arc_solution(data, curseur_solution_vide, id_lieu, lieu_depart, lieu_destination, id_arc);

                    nb_solution_vide--;
                    curseur_solution_vide++;
                }
            }
        }
    }

    if(nb_solution_vide > 0)
        unall_parcourt(data, nb_solution_vide);
}
*/
/*
void supr_deminees_solutions(Donnee *data, int debut_generation, int fin_generation){
    int id_ref, id_sol, id_write;
    int nb_lieu_ref, distance_ref, insecurite_ref, interet_ref;
    int nb_lieu_sol, distance_sol, insecurit_sol, interet_sol;


    for (id_ref = debut_generation; id_ref < fin_generation; ++id_ref){
        nb_lieu_ref = nb_lieu_solution(data, id_ref);

        distance_ref = distance_totale_solution(data, id_ref);
        insecurite_ref = insecurite_solution(data, id_ref);
        interet_ref = interet_solution(data, in_ref);

        id_write = id_ref +1;

        for(id_sol = id_ref +1; id_sol < fin_generation; ++id_sol){
            distance_sol = distance_totale_solution(data, id_sol);
            insecurite_sol = insecurite_solution(data, id_sol);
            interet_sol = interet_solution(data, in_sol);

            if((distance_sol > distance_ref)&&(insecurite_sol > insecurite_ref)){
                unall_solution(data, id_sol);
                continue;
            }
            else{
                if(id_sol != id_write)
                    cpy_solution(data, id_write, id_sol);
                id_write++;
            }
        }
    }

    unall_parcourt(data, id_write, fin_generation);
}
*/
