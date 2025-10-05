#ifndef CENA_H
#define CENA_H

#include <fstream>
#include "objeto.h"
#define TAM_MAX_CENA 1000

//Um trecho da cena que contém um objeto que está visível.
typedef struct SegmentoVisivel_struct {
    int idObjeto;
    double inicio;
    double fim;
} SegmentoVisivel;


//Classe que representa a cena que conterá todos os objetos em segmentos que aparecerão na cena.
class Cena {
private:
    SegmentoVisivel segmentos[TAM_MAX_CENA];
    int numSegmentos;
    int capacidadeSegmentos;

    void adicionarSegmento(int id, double inicio, double fim);

public:
    Cena();

    void processarObjeto(const Objeto& obj);

    void gravarCena(std::ofstream& arquivoSaida, int tempo);
};

#endif 