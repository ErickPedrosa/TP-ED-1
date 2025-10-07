#include <iostream>
#include <fstream>
#include <string>
#include "../include/objeto.h"
#include "../include/cena.h"
#include "../include/sort.h"
#include <chrono> // Para medição de tempo


/*/Função para encontrar um objeto a partir do id dele.
Objeto* encontrarObjeto(int id, Objeto* vobj, int numObj) {
    for (int i = 0; i < numObj; ++i) {
        if (vobj[i].getId() == id) {
            return &vobj[i];
        }
    }
    return nullptr; 
}
*/

// Função para encontrar o ÍNDICE de um objeto no array pelo seu ID
// Modificada para retornar o índice, necessário para checar os vizinhos.
int encontrarIndiceObjeto(int id, Objeto* vobj, int numObj) {
    for (int i = 0; i < numObj; ++i) {
        if (vobj[i].getId() == id) {
            return i;
        }
    }
    return -1; // Não encontrado
}

int main(int argc, char* argv[]) {
    //Verificação do número de argumentos e da validade desses argumentos.
    if (argc != 4) {
        std::cerr << "Uso: ./tp1.out <arquivo_entrada> <arquivo_saida> <limiar>" << std::endl;
        std::cerr << "  <limiar> = -1  (Ordenação Preguiçosa: apenas na cena)" << std::endl;
        std::cerr << "  <limiar> = 0   (Ordenação Ansiosa: a cada desordem)" << std::endl;
        std::cerr << "  <limiar> > 0   (Ordenação por Limiar: quando a desordem atingir o valor)" << std::endl;
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

    // Converte o argumento de limiar para inteiro
    int limiarReordenacao = std::stoi(argv[3]);
    int contadorDesordem = 0;

    //Definição do maximo de objetos que o programa pode ter.
    const int MAX_OBJETOS = 10000;
    Objeto objetos[MAX_OBJETOS];
    int numObjetos = 0;

    // Inicia a contagem de tempo para a análise experimental
    auto inicio = std::chrono::high_resolution_clock::now();

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

            }else{
                std::cerr << "Limite de Objetos Atingido." << std::endl;
            }


        } else if (comando == 'M') {
             int tempo, id;
            double x, y;
            arquivoEntrada >> tempo >> id >> x >> y;
            int indiceObj = encontrarIndiceObjeto(id, objetos, numObjetos);
            
            if (indiceObj != -1) {
                bool desordenou = false;
                if (limiarReordenacao >= 0) {
                    
                    // --- CORREÇÃO APLICADA AQUI ---
                    // Lógica de verificação refatorada para maior segurança e clareza.
                    
                    // 1. Verifica o estado ANTES da atualização
                    bool vizinhoEsquerdoOkAntes = (indiceObj == 0) || (objetos[indiceObj - 1].getY() <= objetos[indiceObj].getY());
                    bool vizinhoDireitoOkAntes = (indiceObj == numObjetos - 1) || (objetos[indiceObj].getY() <= objetos[indiceObj + 1].getY());
                    bool estavaOrdenadoAntes = vizinhoEsquerdoOkAntes && vizinhoDireitoOkAntes;

                    // 2. Atualiza a posição
                    objetos[indiceObj].atualizarPosicao(x, y);

                    // 3. Verifica o estado DEPOIS da atualização
                    bool vizinhoEsquerdoOkAgora = (indiceObj == 0) || (objetos[indiceObj - 1].getY() <= objetos[indiceObj].getY());
                    bool vizinhoDireitoOkAgora = (indiceObj == numObjetos - 1) || (objetos[indiceObj].getY() <= objetos[indiceObj + 1].getY());
                    bool estaOrdenadoAgora = vizinhoEsquerdoOkAgora && vizinhoDireitoOkAgora;
                    
                    // --- FIM DA CORREÇÃO ---

                    if (estavaOrdenadoAntes && !estaOrdenadoAgora) {
                        contadorDesordem++;
                        desordenou = true;
                    } else if (!estavaOrdenadoAntes && estaOrdenadoAgora) {
                        if (contadorDesordem > 0) contadorDesordem--;
                    }
                } else {
                    objetos[indiceObj].atualizarPosicao(x, y);
                }

                // Lógica do gatilho de reordenação (inalterada)
                if (limiarReordenacao == 0 && desordenou) {
                    ordenaPorY(objetos, numObjetos);
                    contadorDesordem = 0;
                } else if (limiarReordenacao > 0 && contadorDesordem >= limiarReordenacao) {
                    ordenaPorY(objetos, numObjetos);
                    contadorDesordem = 0;
                }
            }


        } else if (comando == 'C') {
            int tempo;
            arquivoEntrada >> tempo;
            
            // A ordenação aqui é essencial para a estratégia Preguiçosa (limiar < 0)
            // e também garante a corretude para as outras estratégias.
            ordenaPorY(objetos, numObjetos);
            contadorDesordem = 0; // Gerar a cena requer ordenação, então a desordem é resolvida.


            Cena cena;

            for (int i = 0; i < numObjetos; ++i) {
                cena.processarObjeto(objetos[i]);

            }
            
            cena.gravarCena(arquivoSaida, tempo);
        }
    }

     // --- PASSO 3: FINALIZAÇÃO E EXIBIÇÃO DOS RESULTADOS DO EXPERIMENTO ---
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;

    arquivoEntrada.close();
    arquivoSaida.close();
    
    // Imprime o tempo de execução na saída de erro padrão para não poluir o arquivo de resultado
    std::cerr << "Execucao finalizada." << std::endl;
    std::cerr << "  - Limiar utilizado: " << limiarReordenacao << std::endl;
    std::cerr << "  - Tempo total: " << duracao.count() << " segundos" << std::endl;

    return 0;
}