#include "../include/cena.h"
#include <iostream>
#include <iomanip> 

struct Intervalo {
    double inicio;
    double fim;
};

Cena::Cena() {
    capacidadeSegmentos = 100;
    numSegmentos = 0;
}

Cena::~Cena() {
    delete[] segmentos;
}

void Cena::adicionarSegmento(int id, double inicio, double fim) {
    if (numSegmentos >= capacidadeSegmentos) {
        return;
    }
    segmentos[numSegmentos].idObjeto = id;
    segmentos[numSegmentos].inicio = inicio;
    segmentos[numSegmentos].fim = fim;
    numSegmentos++;
}

// Algoritmo de oclusão: verifica quais partes do novo objeto não foram cobertas ainda
void Cena::processarObjeto(const Objeto& obj) {
    double objInicio = obj.getInicioX();
    double objFim = obj.getFimX();

    // Se o objeto não tem largura, não é visível
    if (objInicio >= objFim) {
        return;
    }

    // Intervalos que o objeto atual precisa preencher
    Intervalo aCobrir[numSegmentos + 1];
    int aCobrirCount = 1;
    aCobrir[0] = {objInicio, objFim};

    // Para cada segmento já visível na cena (de objetos mais à frente)
    for (int i = 0; i < numSegmentos; ++i) {
        int novoACobrirCount = 0;
        Intervalo novoACobrir[numSegmentos + 1];

        // Para cada pedaço do objeto atual que ainda está visível
        for (int j = 0; j < aCobrirCount; ++j) {
            double segInicio = segmentos[i].inicio;
            double segFim = segmentos[i].fim;
            
            double atualInicio = aCobrir[j].inicio;
            double atualFim = aCobrir[j].fim;

            // Calcula a parte que sobra à esquerda e à direita da intersecção
            double parteEsquerdaFim = std::min(atualFim, segInicio);
            double parteDireitaInicio = std::max(atualInicio, segFim);

            if (atualInicio < parteEsquerdaFim) {
                novoACobrir[novoACobrirCount++] = {atualInicio, parteEsquerdaFim};
            }
            if (parteDireitaInicio < atualFim) {
                novoACobrir[novoACobrirCount++] = {parteDireitaInicio, atualFim};
            }
        }
        
        // Atualiza a lista de intervalos a cobrir
        aCobrirCount = novoACobrirCount;
        for(int k=0; k<aCobrirCount; ++k) {
            aCobrir[k] = novoACobrir[k];
        }
    }

    // Adiciona os novos segmentos visíveis (o que sobrou)
    for (int i = 0; i < aCobrirCount; ++i) {
        adicionarSegmento(obj.getId(), aCobrir[i].inicio, aCobrir[i].fim);
    }
}


void Cena::gravarCena(std::ofstream& arquivoSaida, int tempo) {
    for (int i = 0; i < numSegmentos; ++i) {
        arquivoSaida << "S " << tempo << " " << segmentos[i].idObjeto << " "
                     << std::fixed << std::setprecision(2) << segmentos[i].inicio << " "
                     << std::fixed << std::setprecision(2) << segmentos[i].fim << std::endl;
    }
}