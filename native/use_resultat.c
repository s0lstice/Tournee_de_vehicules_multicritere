#include "use_resultat.h"
#include "use_solution.h"
#include "use_map.h"
#include "use_index.h"
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


    if(nb_ajout > 0){

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
    }
    else{
        for(i = data->resultat.nb_resultats[nb_lieux -1][1] + nb_ajout; i < data->resultat.nb_resultats[nb_lieux -1][1]; ++i){
            free(data->resultat.resultats[nb_lieux -1][i]->trajet);
            free(data->resultat.resultats[nb_lieux -1][i]->itineraire);

            if(data->resultat.resultats[nb_lieux -1][i]->visite != NULL)
                free(data->resultat.resultats[nb_lieux -1][i]->visite);

            free(data->resultat.resultats[nb_lieux -1][i]);
        }

        /*desallocation des resultat*/
        nb_l = data->resultat.nb_resultats[nb_lieux -1][1] + nb_ajout;
        tmp_doubptr_parcourt = (Parcourt **)realloc(data->resultat.resultats[nb_lieux -1], (nb_l)*sizeof(Parcourt*));
        if(tmp_doubptr_parcourt == NULL) fatalerreur(data, "all_resultats : echeque de la reallocation des parcourts lv2");
        data->resultat.resultats[nb_lieux -1] = tmp_doubptr_parcourt;
    }

    /*mise a jour du nombre de resultats en fonction du nombre de lieux*/
    if(data->resultat.nb_resultats[nb_lieux -1][1] + nb_ajout < data->resultat.nb_resultats[nb_lieux -1][0])
        data->resultat.nb_resultats[nb_lieux -1][0] = data->resultat.nb_resultats[nb_lieux -1][1] + nb_ajout;

    data->resultat.nb_resultats[nb_lieux -1][1] += nb_ajout;
}

static void replace_resultat(Donnee *data, int nb_lieux, int id_resultat_destination, int id_resultat_source){

    free(data->resultat.resultats[nb_lieux -1][id_resultat_destination]->itineraire);
    data->resultat.resultats[nb_lieux -1][id_resultat_destination]->itineraire = NULL;

    free(data->resultat.resultats[nb_lieux -1][id_resultat_destination]->trajet);
    data->resultat.resultats[nb_lieux -1][id_resultat_destination]->trajet = NULL;

    if(data->resultat.resultats[nb_lieux -1][id_resultat_destination]->visite != NULL){
        free(data->resultat.resultats[nb_lieux -1][id_resultat_destination]->visite);
    }

    cpy_resultat(data, nb_lieux, id_resultat_destination, id_resultat_source);
}

void cpy_resultat(Donnee *data, int nb_lieux, int id_resultat_destination, int id_resultat_source){
    int i, nb_lieux_total;
    Arc **temp_arc;
    Lieu **temp_lieu;
    Parcourt *destination_resultat = data->resultat.resultats[nb_lieux -1][id_resultat_destination];
    Parcourt *source_resultat = data->resultat.resultats[nb_lieux -1][id_resultat_source];

    if(destination_resultat == NULL){
        data->resultat.resultats[nb_lieux -1][id_resultat_destination] = (Parcourt *)malloc(sizeof(Parcourt));
        destination_resultat = data->resultat.resultats[nb_lieux -1][id_resultat_destination];
    }

    if(destination_resultat == NULL) fatalerreur(data, "cpy_resultat : echeque de l'allocation des resultats vl3");


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

    if(id_resultat_destination >= data->resultat.nb_resultats[nb_lieux -1][0]) //il y a une nouvelle solution que si sa position de destination est plus grand que le nombre de resultat deja utilise
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

    /*recupere le nombre de resultat utilisé. comme ils sont contenuent dans un tableau (debut a 0), cela corespond aussi a la position du nouvel element*/
    id_resultat = nb_resultats_use_by_lieu(data, nb_lieux);

    /*libere cette espace, en effet contrairement a copie, cette espace existe deja dans le tableau des solutions*/
    free(data->resultat.resultats[nb_lieux -1][id_resultat]);

    /*cpoie de l'adresse*/
    data->resultat.resultats[nb_lieux -1][id_resultat] = data->solution.solution[id_solution];

    /*increùmantation du nombre de resultats utilisé*/
    data->resultat.nb_resultats[nb_lieux -1][0]++;

    /*comble le vide engendre dans le tableau des solutions*/
    while(id_solution < data->solution.nb_solution -1){
        data->solution.solution[id_solution] = data->solution.solution[id_solution +1];
        id_solution++;
    }

    /*desaloue la derniere solution du tableaux, si le tableau est vide, il est suprimé*/
    if(data->solution.nb_solution == 1){
        data->solution.nb_solution = 0;

         free(data->solution.solution);
    }
    else{
        data->solution.nb_solution -= 1;
        //unall_solution(data, data->solution.nb_solution);

        tmp = (Parcourt **)realloc(data->solution.solution, (data->solution.nb_solution)*sizeof(Parcourt*));
        if(tmp == NULL) fatalerreur(data, "cut_solution_to_resultat : echeque de la reallocation");
        data->solution.solution = tmp;
    }

    /*renvoie la pisiont de destination*/
    return id_resultat;
}

int distance_arc_resultat(Donnee *data, int nb_lieux, int id_resultat, int id_arc){
    return data->resultat.resultats[nb_lieux -1][id_resultat]->trajet[id_arc]->distance;
}

int insecurite_arc_resultat(Donnee *data, int nb_lieux, int id_resultat, int id_arc){
    return data->resultat.resultats[nb_lieux -1][id_resultat]->trajet[id_arc]->insecurite;
}

int distance_totale_resultat(Donnee * data, int nb_lieux, int id_resultat){
    return data->resultat.resultats[nb_lieux -1][id_resultat]->carac.distance;
}

int insecurite_totale_resultat(Donnee * data, int nb_lieux, int id_resultat){
    return data->resultat.resultats[nb_lieux -1][id_resultat]->carac.insecurite;
}

void change_arc_resultat(Donnee *data, int nb_lieux, int id_resultat, int id_arc, int id_depart, int id_destination, int id_offcet){
    data->resultat.resultats[nb_lieux -1][id_resultat]->carac.distance = distance_totale_resultat(data, nb_lieux, id_resultat) - distance_arc_resultat(data, nb_lieux, id_resultat, id_arc) + distance_arc(data, id_depart, id_destination, id_offcet);
    data->resultat.resultats[nb_lieux -1][id_resultat]->carac.insecurite =  data->resultat.resultats[nb_lieux -1][id_resultat]->carac.insecurite - insecurite_arc_resultat(data, nb_lieux, id_resultat, id_arc) + insecurite_arc(data, id_depart, id_destination, id_offcet);

    data->resultat.resultats[nb_lieux -1][id_resultat]->trajet[id_arc] = ptr_arc(data, id_depart, id_destination, id_offcet);
}

void genere_resultats(Donnee *data, int nb_lieux){
    int id_resultat = data->resultat.nb_resultats[nb_lieux -1][0] -1;
    int nb_lieux_resultat = data->resultat.resultats[nb_lieux -1][id_resultat]->carac.nb_arc;
    int lieu, arc;
    Parcourt* table_resultat = data->resultat.resultats[nb_lieux -1][id_resultat];
    int id_destination, id_depart;
    int nb_arc_genere;
    int nb_resutats_vide;
    int id_write_resultat = id_resultat + 1;
    int distance_new, insecurite_new;
    int distance_ref, insecurite_ref;

    /*pour tous les lieux du chemin*/
    for(lieu = 0; lieu < nb_lieux_resultat; ++lieu){
        /* on recupere leur valeur*/
        id_depart = table_resultat->itineraire[lieu]->id;
        id_destination = table_resultat->itineraire[lieu + 1]->id;
        nb_arc_genere = index_nb_arc(data, id_depart, id_destination); //nombre d'arc entre le depart et la destination
        nb_resutats_vide =  data->resultat.nb_resultats[nb_lieux -1][1] - data->resultat.nb_resultats[nb_lieux -1][0]; //nombre d'arc alloué et non utilise

        if(nb_resutats_vide < nb_arc_genere){ //on alloue si le nombre de resultat disponible est inferieur aux nombre de resultat necessaire
            all_resultats(data, nb_lieux, data->resultat.nb_resultats[nb_lieux -1][1] + nb_arc_genere - nb_resutats_vide); //allocation du nombre de resultat necessaire
        }

        distance_ref = distance_totale_resultat(data, nb_lieux, id_resultat);
        insecurite_ref = insecurite_totale_resultat(data, nb_lieux, id_resultat);

        /*pour tous les arcs disponible entre le lieu de depart et le lieu d'arrive*/
        for(arc = 1; arc < nb_arc_genere; ++arc){
            distance_new = distance_ref - distance_arc_resultat(data, nb_lieux, id_resultat, lieu) + distance_arc(data, id_depart, id_destination, arc);
            insecurite_new =  insecurite_ref - insecurite_arc_resultat(data, nb_lieux, id_resultat, lieu) + insecurite_arc(data, id_depart, id_destination, arc);

            if((distance_ref < distance_new)&&(insecurite_ref < insecurite_new)){
                continue; //new est dominé
            }
            if((distance_ref > distance_new)&&(insecurite_ref > insecurite_new)){
                /*le chemin de referance, est dominé, on modifi sont arc pour ne pas garder un chemin dominé, sur tout celui de la generation*/
                change_arc_resultat(data, nb_lieux, id_resultat, lieu, id_depart, id_destination, arc);

                distance_ref = distance_totale_resultat(data, nb_lieux, id_resultat);
                insecurite_ref = insecurite_totale_resultat(data, nb_lieux, id_resultat);
            }
            else{
                cpy_resultat(data, nb_lieux, id_write_resultat, id_resultat); /* c'est un nouveau chemin valide*/
                change_arc_resultat(data, nb_lieux, id_write_resultat, lieu, id_depart, id_destination, arc);
                id_write_resultat++;
            }
        }


    }

    all_resultats(data, nb_lieux, data->resultat.nb_resultats[nb_lieux -1][0] - data->resultat.nb_resultats[nb_lieux -1][1]);

}

static int compar_resultats(Donnee *data, int nb_lieux, int id_resultat1, int id_resultat2){
    int nb_arc_resultat = data->resultat.resultats[nb_lieux -1][id_resultat1]->carac.nb_arc;
    int i = 0;
    Arc **arc1;
    Arc **arc2;
    int test = 0;

    arc1 = data->resultat.resultats[nb_lieux -1][id_resultat1]->trajet;
    arc2 = data->resultat.resultats[nb_lieux -1][id_resultat2]->trajet;

    while( (i < nb_arc_resultat)&&(test == 0)){
        test = test + arc1[i]->depart->id - arc2[i]->depart->id;
        test = test + arc1[i]->destination->id - arc2[i]->destination->id ;
        test = test + arc1[i]->distance - arc2[i]->distance;
        test = test + arc1[i]->insecurite - arc2[i]->insecurite;

        i++;
    }

    if(test == 0) return 0;
    return 1;
}

static void suprime_resultat(Donnee *data, int nb_lieux, int id_resultat){
    int i;
    //Parcourt **tmp_doubptr_parcourt;

    free(data->resultat.resultats[nb_lieux -1][id_resultat]->itineraire);
    free(data->resultat.resultats[nb_lieux -1][id_resultat]->trajet);
    if(data->resultat.resultats[nb_lieux -1][id_resultat]->visite != NULL){
        free(data->resultat.resultats[nb_lieux -1][id_resultat]->visite);
    }


    for(i = id_resultat; i < nb_resultats_use_by_lieu(data, nb_lieux) -1; ++i){
        data->resultat.resultats[nb_lieux -1][i] = data->resultat.resultats[nb_lieux -1][i +1];
    }

    data->resultat.resultats[nb_lieux -1][i] = NULL;

    /*free(data->resultat.resultats[nb_lieux -1][i]->itineraire);
    free(data->resultat.resultats[nb_lieux -1][i]->trajet);
    if(data->resultat.resultats[nb_lieux -1][i]->visite != NULL){
        free(data->resultat.resultats[nb_lieux -1][i]->visite);
    }

    tmp_doubptr_parcourt = (Parcourt **)realloc(data->resultat.resultats[nb_lieux -1], i*sizeof(Parcourt*));
    if(tmp_doubptr_parcourt == NULL) fatalerreur(data, "suprime_resultat :  echeque de la realocation de lv2");
    data->resultat.resultats[nb_lieux -1] = tmp_doubptr_parcourt;

    data->resultat.nb_resultats[nb_lieux -1][1] = i;
    */
    data->resultat.nb_resultats[nb_lieux -1][0]--;
}

void epure_resultats(Donnee *data, int nb_lieux){
    int id_referance, id_test;
    int interet_referance, distance_referance, insecurite_referance;
    int interet_test, distance_test, insecurite_test;

    for(id_referance = 0; id_referance < nb_resultats_use_by_lieu(data, nb_lieux); ++id_referance){

        interet_referance = data->resultat.resultats[nb_lieux -1][id_referance]->carac.interet;
        distance_referance = data->resultat.resultats[nb_lieux -1][id_referance]->carac.distance;
        insecurite_referance = data->resultat.resultats[nb_lieux -1][id_referance]->carac.insecurite;

        for(id_test = id_referance +1; id_test < nb_resultats_use_by_lieu(data, nb_lieux); ++id_test){

            interet_test = data->resultat.resultats[nb_lieux -1][id_test]->carac.interet;
            distance_test = data->resultat.resultats[nb_lieux -1][id_test]->carac.distance;
            insecurite_test = data->resultat.resultats[nb_lieux -1][id_test]->carac.insecurite;

            if((interet_referance == interet_test)&&(distance_referance == distance_test)&&(insecurite_referance == insecurite_test)){
                if(compar_resultats(data, nb_lieux, id_referance, id_test) == 0){// teste si les chemins sont idantiques
                    //suprimer test
                    suprime_resultat(data, nb_lieux, id_test);
                }
            }
            else {
                if((interet_referance >= interet_test)&&(distance_referance <= distance_test)&&(insecurite_referance <= insecurite_test)){
                    suprime_resultat(data, nb_lieux, id_test);
                }
                else {
                    if((interet_referance <= interet_test)&&(distance_referance >= distance_test)&&(insecurite_referance >= insecurite_test)){
                        replace_resultat(data, nb_lieux, id_referance, id_test);
                        suprime_resultat(data, nb_lieux, id_test);

                        interet_referance = interet_test;
                        distance_referance = distance_test;
                        insecurite_referance = insecurite_test;
                    }
                }
            }
        }
    }
}

void unall_resultats(Donnee *data){
    int i, j;

    for(i = 0; i < data->resultat.nb_lieux ; ++i){
        if(data->resultat.resultats[i] != NULL){
            for(j = 0; j < data->resultat.nb_resultats[i][1]; ++j){
                if(data->resultat.resultats[i][j] != NULL){
                    free(data->resultat.resultats[i][j]->itineraire);
                    free(data->resultat.resultats[i][j]->trajet);

                    if(data->resultat.resultats[i][j]->visite != NULL){
                        free(data->resultat.resultats[i][j]->visite);
                    }
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
