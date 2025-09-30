#ifndef SORT_H
#define SORT_H

#include "objeto.h"
#include "cena.h"


void troca(Objeto* vobj, int i, int j);
void ordenaPorY(Objeto* vobj, int numObj);
void ordenaPorId(SegmentoVisivel* segmentos, int numSegmentos);

#endif