#ifndef OBJETO_H
#define OBJETO_H

class Objeto {
private:
    int id;
    double x; 
    double y; 
    double largura;

public:
    Objeto();

    void inicializar(int id, double x, double y, double largura);

    void atualizarPosicao(double novoX, double novoY);

    int getId() const;
    double getY() const;
    double getInicioX() const;
    double getFimX() const;
};

#endif 