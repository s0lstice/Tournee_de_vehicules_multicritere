/**
 * \file tri.c
 * \brief perment de trier les arcs selon l'interte de la destination, la distance et l'insecurité. Et la suppretion d'arcs dominés.
 * \author Mickael PURET
 * \date 27 mars 2011
 *
 */

#ifndef QSORT_H_INCLUDED
#define QSORT_H_INCLUDED

#include "create_bd.h"

void quicksort_map(Donnee * data, int id_lieu, int m, int n);
int epure_map(Donnee *data,int id_lieu);
#endif // QSORT_H_INCLUDED
