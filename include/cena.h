#ifndef CENA_H
#define CENA_H

#include <fstream>
#include "objeto.h"
#define TAM_MAX_CENA 100

// Estrutura para representar um segmento visível na cena final
typedef struct SegmentoVisivel_struct {
    int idObjeto;
    double inicio;
    double fim;
} SegmentoVisivel;

class Cena {
private:
    // Arrays para armazenar os segmentos visiveis
    SegmentoVisivel segmentos[TAM_MAX_CENA];
    int numSegmentos;
    int capacidadeSegmentos;

    // Função auxiliar para adicionar um segmento visível à cena
    void adicionarSegmento(int id, double inicio, double fim);

public:
    Cena();
    ~Cena();

    // Processa um objeto e adiciona suas partes visíveis à cena
    // A lógica de oclusão acontece aqui
    void processarObjeto(const Objeto& obj);

    // Grava o resultado da cena no arquivo de saída
    void gravarCena(std::ofstream& arquivoSaida, int tempo);
};

#endif // CENA_H