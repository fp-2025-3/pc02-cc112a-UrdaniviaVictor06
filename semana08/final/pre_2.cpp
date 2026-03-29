#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>


using namespace std;

struct punto{
    double x;
    double y;
};

//_______________________

void leerPunto(struct punto *p){
    cout << "\nIngrese la coordenada x: ";
    cin >> p->x;

    cout << "\nIngrese la coordenada y: ";
    cin >>p->y;

}

double distanciaOrigen(const struct punto *p){
    double resultado=0;

    resultado = (p->x) * (p->x) + (p->y) * (p->y);
    resultado = sqrt(resultado); 

    return resultado;
}

struct punto *masLejano(struct punto *p1, struct punto *p2){
    double dis_1 = distanciaOrigen(p1);

    double dis_2 = distanciaOrigen(p2); 

    if(dis_1 > dis_2){
        return p1;
    } else {
        return p2;
    }
}

int main(){
    struct punto *p1 = new struct punto; // memoria dinamica

    cout << "\nSea el primer punto: ";
    leerPunto(p1);

    double d_p1 = distanciaOrigen(p1);

    struct punto *p2 = new struct punto; // memoria dinamica

    cout << "\nSea el segundo punto:";
    leerPunto(p2);

    double d_p2 = distanciaOrigen(p2); 

    cout << "\nEl punto mas lejano es: ";
    struct punto *p3 = masLejano(p1, p2); // aqui p3 va a apuntar a p1 o p2, osea solo me basta con
    // dos delete 

    cout << "("<< p3->x << ", "<< p3->y << ") : con distancia ";
    cout << distanciaOrigen(p3) << endl;
    

    delete p2;
    delete p1;
    return 0;
}