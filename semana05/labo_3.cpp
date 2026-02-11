#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct partido{
    int Ganados; // x3 =puntos
    int Perdidos; // x0 = puntos 
    int Empatados; // x1 = puntos
};

struct seleccion{
    int Punto_t;
    struct partido jugado;
    float rendimiento;
};

//______________________________________________-


void rellenarDatos(struct seleccion *lista, int *n){
    for(int i=0; i<*n; i++){
        // tiene nombre, pero lo pondre despues
        lista[i].jugado.Ganados = rand()%101 ; // del 0 al 100
        int temp= 100 -lista[i].jugado.Ganados;
        lista[i].jugado.Perdidos = rand()%temp; // del 0 al temp-1
        lista[i].jugado.Empatados = 100 - (lista[i].jugado.Ganados + lista[i].jugado.Perdidos);

        lista[i].Punto_t = 3* (lista[i].jugado.Ganados) + (lista[i].jugado.Empatados);

        lista[i].rendimiento = ( float(lista[i].Punto_t) )/3;
    }
}

void imprimirDatos(struct seleccion *lista, int *n){
    cout << "Seleccion ";
    cout << setw(15) << "PG";
    cout << setw(10) << "PP";
    cout << setw(10) << "PE";
    cout << setw(18) <<"Puntaje";
    cout << setw(20) << "Rendimiento\n";
    
    
    for(int i=0; i<*n; i++){
       cout << "Pais_seleccion " << i;
       cout << setw(10) <<lista[i].jugado.Ganados;
       cout << setw(10) <<lista[i].jugado.Perdidos;
       cout << setw(10) <<lista[i].jugado.Empatados;
       cout << setw(18)<< lista[i].Punto_t;
       cout << setw(20) << fixed << setprecision(2) << lista[i].rendimiento << endl;    
    }

    
}

void muestraElMejor(struct seleccion *lista, int *n){
    int indice=0;
    float rendi_max=lista[indice].rendimiento;
    for(int i=0; i<*n; i++){
      if(lista[i].rendimiento >rendi_max){
        indice=i;
        rendi_max=lista[indice].rendimiento;
      }
    }

    //ya lo tengo xd
    cout <<"\nLa seleccion con mejor rendimiento es Pais_seleccion "<<indice<< " : ";
    cout << lista[indice].rendimiento<< endl;
}


int main(){

    int n=5;
    int *p_n = &n;

    struct seleccion *lista = new struct seleccion[*p_n]; // reservo 5 elementos

    rellenarDatos(lista, p_n);

    imprimirDatos(lista, p_n);

    muestraElMejor(lista, p_n);

    delete[] lista;
    return 0;
}