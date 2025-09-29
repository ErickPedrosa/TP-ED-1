#ifndef CENA_H
#define CENA_H

#include <fstream>
#include "objeto.h"
#define TAM_MAX_CENA 100

typedef struct SegmentoVisivel_struct {
    int idObjeto;
    double inicio;
    double fim;
} SegmentoVisivel;

class Cena {
private:
    SegmentoVisivel segmentos[TAM_MAX_CENA];
    int numSegmentos;
    int capacidadeSegmentos;

    void adicionarSegmento(int id, double inicio, double fim);

public:
    Cena();
    ~Cena();

    void processarObjeto(const Objeto& obj);

    void gravarCena(std::ofstream& arquivoSaida, int tempo);
};

#endif 