#include"Punto.h"
#include "Poligono.h"
Poligono::Poligono(){
    nVertices = 0;
    vertices=nullptr;
}
Poligono::Poligono(int n){
    nVertices = n;
    vertices = new Punto[n];
}
void Poligono::liberar(){

}
int Poligono::getNumeroVertices() const{
    return nVertices;
}
Punto Poligono::getVertice(int index) const{
    if(index > 0 && index < nVertices){
        return vertices[index];
    }
}
void Poligono::addVertice(const Punto& v){
    Punto *aux;
    aux = new Punto[nVertices+1];
    for(int i = 0 ; i<nVertices; i++){
        aux[i] = vertices[i];
    }
    aux[nVertices] = v;
    vertices = aux;
    nVertices++;
}
double Poligono::getPerimetro() const{
    for(int i =0; i < nVertices; i++)
}