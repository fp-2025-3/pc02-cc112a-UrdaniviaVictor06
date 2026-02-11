#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

struct punto{
    float x;
    float y;
    float z;
};

// _____________________________-

float hallarDistancia(struct punto p1, struct punto p2){
    float resultado=0;
    resultado = pow( (p1.x -p2.x), 2 ) + pow ( (p1.y - p2.y), 2 ) + pow ( (p1.z - p2.z), 2 );
    resultado = sqrt(resultado);
    return resultado;
}

int main(){

    struct punto p1;
    struct punto p2;
    cout <<"Ingrese la ubicacion del primer punto: \n";
    cout << "x: ";
    cin >>p1.x;
    
    cout << "y: ";
    cin >> p1.y;

    cout << "z: ";
    cin >> p1.z;

    cout << "Ingrese la ubicacion del segundo punto: \n";
    cout << "x: ";
    cin >>p2.x;
    
    cout << "y: ";
    cin >> p2.y;

    cout << "z: ";
    cin >> p2.z;

    float distancia = hallarDistancia(p1, p2);
    cout << "La distancia entre los dos puntos es: " << distancia << endl;
    

    return 0;
}