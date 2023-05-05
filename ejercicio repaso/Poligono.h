#include "Punto.h"
class Poligono
{
    int nVertices;   // N´umero de puntos en el array din´amico
    Punto *vertices; // Array din´amico de objetos Punto
public:
    Poligono();
    Poligono(int n);
    void liberar();
    int getNumeroVertices() const;
    Punto getVertice(int index) const;
    void addVertice(const Punto &v);
    double getPerimetro() const;
};