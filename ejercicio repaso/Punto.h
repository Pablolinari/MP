class Punto{
    double x;
    double y;
public:
    Punto();
    Punto(int x, int y);
    double getX()const;
    double getY()const;
    void setXY(int x, int y);
    double getDistance(const Punto & p);
};