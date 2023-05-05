#include"Punto.h"
#include<cmath>
    Punto::Punto(){x=0; y=0;};
    Punto::Punto(int x, int y){
                this->x = x;
        this->y = y;
    }
    double Punto::getX() const{
        return x;
    }
    double Punto::getY() const{
        return y;
    }
    void Punto::setXY(int x, int y){
        this ->x=x;
        this ->y=y;
    }
    double Punto::getDistance( const Punto  &punto){
        return sqrt((punto.getX() - x)*(punto.getX()-x) + (punto.getY()-y)*(punto.getY()-y));
    }