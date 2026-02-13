#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

struct partidos{
    int ganados; // x3
    int perdidos; // x0
    int empatados;  // x1
};

struct goles{
    int favor;
    int contra;
    int diferencia;
};

struct seleccion{
    int id;
    char *nombre; //memoria dinamica
    struct partidos jugados;
    struct goles totales;
    int puntajeTotal;
    float rendimiento;
};

// _______________________________________________-

void rellenarDatos(struct seleccion *lista, int n){
    for(int i=0; i<n; i++){
        // id para identificar
        lista[i].id= i+1;

        //nombre dinamico
        lista[i].nombre = new char; // memoria reservada
        strcpy(lista[i].nombre, "Pais_");


        // se supone funciona como array
        lista[i].jugados.ganados = rand()%81 ; // del 0 al 80
        int temp= 100 - lista[i].jugados.ganados;  
        lista[i].jugados.perdidos =  rand()%temp; // del 0 al temp-1
        lista[i].jugados.empatados = 100 - ( lista[i].jugados.ganados + lista[i].jugados.perdidos );
        //suman 100

        // arrays temporales de goles
        int golesGanados = 0;
        int golesContra = 0;

        //partidos ganados
        for(int j=0; j< lista[i].jugados.ganados; j++){
            lista[i].totales.favor = rand()%6; // de 0 a 5
            lista[i].totales.contra = rand()%6; // de 0 a 5 

            while(lista[i].totales.favor < lista[i].totales.contra){
                lista[i].totales.favor = rand()%6; // de 0 a 5
                lista[i].totales.contra = rand()%6; // de 0 a 5 
            }

            golesGanados += lista[i].totales.favor;
            golesContra += lista[i].totales.contra;
        }

         //partidos perdidos
        for(int j=0; j< lista[i].jugados.perdidos; j++){
            lista[i].totales.favor = rand()%6; // de 0 a 5
            lista[i].totales.contra = rand()%6; // de 0 a 5 

            while(lista[i].totales.favor > lista[i].totales.contra){
                lista[i].totales.favor = rand()%6; // de 0 a 5
                lista[i].totales.contra = rand()%6; // de 0 a 5 
            }

            golesGanados += lista[i].totales.favor;
            golesContra += lista[i].totales.contra;
        }

        //partidos empatados
        for(int j=0; j< lista[i].jugados.empatados; j++){
            lista[i].totales.favor = rand()%6; // de 0 a 5
            lista[i].totales.contra = rand()%6; // de 0 a 5 

            while(lista[i].totales.favor != lista[i].totales.contra){
                lista[i].totales.favor = rand()%6; // de 0 a 5
                lista[i].totales.contra = rand()%6; // de 0 a 5 
            }

            golesGanados += lista[i].totales.favor;
            golesContra += lista[i].totales.contra;
        }

        // goles totales
        lista[i].totales.favor = golesGanados;
        lista[i].totales.contra = golesContra;
        lista[i].totales.diferencia = golesGanados - golesContra;

        //puntaje total

        lista[i].puntajeTotal= 3 * lista[i].jugados.ganados + lista[i].jugados.empatados; 

        //rendimiento total

        lista[i].rendimiento = float ( lista[i].puntajeTotal )/3;
    }
}
 /*
void ordenarLista(struct seleccion *lista, int n){
    struct seleccion maximo=lista[0];
    for(int i=0; i<n; i++){
        if(lista[i].puntajeTotal > maximo.puntajeTotal){
            maximo = lista[i];
        }
    }
}
*/


void imprimirLista(struct seleccion *lista, int n){
    
    cout << "Seleccion ";
    cout << setw(4)<< "PG";
    cout << setw(6)<< "PE";
    cout << setw(6)<< "PP";
    cout << setw(6)<< "GF";
    cout << setw(6)<< "GC";
    cout << setw(6)<< "DG";
    cout << setw(6)<< "Pts";
    cout << setw(12)<< "Rend(%)\n";
    for(int i=0; i<60; i++){
        cout << "-";
    }
    cout << endl;
    for(int i=0; i<n; i++){
        cout << lista[i].nombre<< lista[i].id;
        cout << setw(8) << lista[i].jugados.ganados;
        cout << setw(6) << lista[i].jugados.empatados;
        cout << setw(6) << lista[i].jugados.perdidos;
        cout << setw(6) << lista[i].totales.favor;
        cout << setw(6) << lista[i].totales.contra;
        cout << setw(6) << lista[i].totales.diferencia;
        cout << setw(6) << lista[i].puntajeTotal;
        cout << setw(11) <<fixed << setprecision(2)<<  lista[i].rendimiento;
        cout << endl;
    }
}


int main(){

    // sean 5 selecciones n=5
    int n=5;

    struct seleccion *lista = new struct seleccion[n]; // array de 5 partidos
    rellenarDatos(lista, n);

    //    ordenarLista(lista, n);

    imprimirLista(lista, n);

    return 0;
}
