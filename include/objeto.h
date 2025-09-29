#ifndef OBJETO_H
#define OBJETO_H

class Objeto {
private:
    int id;
    double x; // Posição central no eixo x
    double y; // Posição de profundidade no eixo y
    double largura;

public:
    // Construtor padrão
    Objeto();
    // Função para inicializar um objeto com valores
    void inicializar(int id, double x, double y, double largura);

    // Função para atualizar a posição do objeto, conforme comando 'M'
    void atualizarPosicao(double novoX, double novoY);

    // Funções para obter as propriedades do objeto
    int getId() const;
    double getY() const;
    double getInicioX() const;
    double getFimX() const;
};

#endif // OBJETO_H