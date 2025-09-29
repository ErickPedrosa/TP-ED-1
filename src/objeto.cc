#include "../include/objeto.h"

Objeto::Objeto() : id(0), x(0.0), y(0.0), largura(0.0) {}

void Objeto::inicializar(int id, double x, double y, double largura) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->largura = largura;
}

void Objeto::atualizarPosicao(double novoX, double novoY) {
    this->x = novoX;
    this->y = novoY;
}

int Objeto::getId() const {
    return id;
}

double Objeto::getY() const {
    return y;
}

double Objeto::getInicioX() const {
    return x - largura / 2.0;
}

double Objeto::getFimX() const {
    return x + largura / 2.0;
}