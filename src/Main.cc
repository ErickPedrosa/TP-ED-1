#include <iostream>
#include <fstream>
#include <string>
#include "../include/objeto.h"
#include "../include/cena.h"

// Função para ordenar o vetor de objetos com base na coordenada Y (profundidade)
// Implementação simples de Selection Sort para cumprir o requisito de não usar std::sort
void ordenaPorY(Objeto* vobj, int numObj) {
    for (int i = 0; i < numObj - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < numObj; j++) {
            if (vobj[j].getY() < vobj[min_idx].getY()) {
                min_idx = j;
            }
        }
        // Troca
        Objeto temp = vobj[min_idx];
        vobj[min_idx] = vobj[i];
        vobj[i] = temp;
    }
}

// Função para encontrar um objeto no array pelo seu ID
Objeto* encontrarObjeto(int id, Objeto* vobj, int numObj) {
    for (int i = 0; i < numObj; ++i) {
        if (vobj[i].getId() == id) {
            return &vobj[i];
        }
    }
    return nullptr; // Não encontrado
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: ./tp1.out <arquivo_entrada> <arquivo_saida>" << std::endl;
        return 1;
    }

    std::ifstream arquivoEntrada(argv[1]);
    if (!arquivoEntrada.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream arquivoSaida(argv[2]);
    if (!arquivoSaida.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saida: " << argv[2] << std::endl;
        return 1;
    }

    const int MAX_OBJETOS = 100;
    Objeto objetos[MAX_OBJETOS];
    int numObjetos = 0;

    char comando;
    while (arquivoEntrada >> comando) {
        if (comando == 'O') {
            int id;
            double x, y, largura;
            arquivoEntrada >> id >> x >> y >> largura;
            if (numObjetos < MAX_OBJETOS) {
                objetos[numObjetos].inicializar(id, x, y, largura);
                numObjetos++;
            }
        } else if (comando == 'M') {
            int tempo, id;
            double x, y;
            arquivoEntrada >> tempo >> id >> x >> y;
            Objeto* obj = encontrarObjeto(id, objetos, numObjetos);
            if (obj != nullptr) {
                obj->atualizarPosicao(x, y);
            }
        } else if (comando == 'C') {
            int tempo;
            arquivoEntrada >> tempo;
            
            // 1. Ordena os objetos por profundidade (Y)
            ordenaPorY(objetos, numObjetos);

            // 2. Cria uma nova cena
            Cena cena;

            // 3. Processa cada objeto para determinar visibilidade
            for (int i = 0; i < numObjetos; ++i) {
                cena.processarObjeto(objetos[i]);
            }
            
            // 4. Grava a cena resultante no arquivo de saída
            cena.gravarCena(arquivoSaida, tempo);
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}