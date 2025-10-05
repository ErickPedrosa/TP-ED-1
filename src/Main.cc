#include <iostream>
#include <fstream>
#include <string>
#include "../include/objeto.h"
#include "../include/cena.h"
#include "../include/sort.h"


//Função para encontrar um objeto a partir do id dele.
Objeto* encontrarObjeto(int id, Objeto* vobj, int numObj) {
    for (int i = 0; i < numObj; ++i) {
        if (vobj[i].getId() == id) {
            return &vobj[i];
        }
    }
    return nullptr; 
}


int main(int argc, char* argv[]) {
    //Verificação do número de argumentos e da validade desses argumentos.
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

    //Definição do maximo de objetos que o programa pode ter.
    const int MAX_OBJETOS = 1000;
    Objeto objetos[MAX_OBJETOS];
    int numObjetos = 0;


    //Looping Principal
    //Pega o caractere de comando do arquivo e realiza a respectiva operação
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
            
            ordenaPorY(objetos, numObjetos);

            Cena cena;

            for (int i = 0; i < numObjetos; ++i) {
                cena.processarObjeto(objetos[i]);
                
            }
            
            cena.gravarCena(arquivoSaida, tempo);
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}