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
        //nombre dinamico
        lista[i].nombre = new char[10]; // memoria reservada
        string temporal = "Pais_" + to_string(i+1);
        strcpy(lista[i].nombre, temporal.c_str());



        // partidos ganados random
        lista[i].jugados.ganados = 40 +rand()%41 ; // del 0 al 80, minimo 40
        int temp= 100 - lista[i].jugados.ganados;  
        // partidos perdidos ramdom
        lista[i].jugados.perdidos =  rand()%temp; // del 0 al temp-1
        // perdidos + ganados = 99, como maximo => queda al menos 1 partido empatado
        lista[i].jugados.empatados = 100 - ( lista[i].jugados.ganados + lista[i].jugados.perdidos );
        

        // valores para acumular los goles a favor y en contra
        int golesGanados = 0;
        int golesContra = 0;

        //partidos ganados, GF > GC
        for(int j=0; j< lista[i].jugados.ganados; j++){
            lista[i].totales.favor = rand()%6; // de 0 a 5
            lista[i].totales.contra = rand()%6; // de 0 a 5 

            while(lista[i].totales.favor < lista[i].totales.contra){ 
                // si GF < GC => repite el proceso
                lista[i].totales.favor = rand()%6; // de 0 a 5
                lista[i].totales.contra = rand()%6; // de 0 a 5 
            }

            // acumulando los puntos
            golesGanados += lista[i].totales.favor;
            golesContra += lista[i].totales.contra;
        }

         //partidos perdidos, GF < GC
        for(int j=0; j< lista[i].jugados.perdidos; j++){
            lista[i].totales.favor = rand()%6; // de 0 a 5
            lista[i].totales.contra = rand()%6; // de 0 a 5 

            while(lista[i].totales.favor > lista[i].totales.contra){
                // si GF > GC => repite proceso
                lista[i].totales.favor = rand()%6; // de 0 a 5
                lista[i].totales.contra = rand()%6; // de 0 a 5 
            }

            // acumulando los puntos
            golesGanados += lista[i].totales.favor;
            golesContra += lista[i].totales.contra;
        }

        //partidos empatados, GF = GC
        for(int j=0; j< lista[i].jugados.empatados; j++){
            lista[i].totales.favor = rand()%6; // de 0 a 5
            lista[i].totales.contra = rand()%6; // de 0 a 5 

            while(lista[i].totales.favor != lista[i].totales.contra){
                // si GF != GC => repite proceso
                lista[i].totales.favor = rand()%6; // de 0 a 5
                lista[i].totales.contra = rand()%6; // de 0 a 5 
            }

            // acumulando los puntos
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

void ordenarLista(struct seleccion *lista, int n){
    
    // ordenamiento por selection sort
    for(int i=0; i<n-1; i++){ //recorre toda la lista
        int indice_max = i; // tomemos como maximo al primer elemento de cada for
        for(int j=i; j<n; j++){
            if(lista[j].puntajeTotal > lista[indice_max].puntajeTotal){
                indice_max = j;
            }

        }
        //ya tengo el maximo
        swap(lista[i], lista[indice_max]);
    }

    //ahora ordenar por diferencia de goles, burble sort
    for(int j=0; j<n-1; j++){
        for(int i=0; i<n-1; i++){
            if(lista[i].puntajeTotal == lista[i+1].puntajeTotal){ 
                // si mismo puntaje => entra
                if(lista[i].totales.diferencia < lista[i+1].totales.diferencia){
                    // si mismo puntaje y diferencia de goles 
                    swap(lista[i], lista[i+1]);
                }
            
            }
        }
    }


    //ahora ordenar por goles a favor, burble sort
    for(int j=0; j<n-1; j++){
        for(int i=0; i<n-1; i++){
            if(lista[i].puntajeTotal == lista[i+1].puntajeTotal){
                if(lista[i].totales.diferencia == lista[i+1].totales.diferencia){
                    if(lista[i].totales.favor < lista[i+1].totales.favor){
                        swap(lista[i], lista[i+1]);
                    }
                }
            }
        }
    }


}

void imprimirCampeon(struct seleccion *lista, int n){
    struct seleccion maximo=lista[0]; // definimos como maximo al primer elemento
    for(int i=0; i<n; i++){ 
        if(lista[i].puntajeTotal > maximo.puntajeTotal){
            maximo =lista[i];
        }
    }

    //ya tenemos al maximo
    cout <<"\nCampeon : "<<maximo.nombre;
    cout << " | Puntaje : " << maximo.puntajeTotal;
    cout << " | DG : "<<maximo.totales.diferencia; 
    cout << " | Rendimiento : "<< maximo.rendimiento;
    cout << "%\n";
}


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
        cout << lista[i].nombre;
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

void liberarMemoria(struct seleccion *lista, int n){
    for(int i=0; i< n; i++){
        delete[] lista[i].nombre; 
    }
    delete[] lista;
}


int main(){

    // sean 5 selecciones n=5
    int n=5;

    struct seleccion *lista = new struct seleccion[n]; // array de 5 partidos
    rellenarDatos(lista, n);

    ordenarLista(lista, n);

    imprimirLista(lista, n);

    imprimirCampeon(lista, n);

    liberarMemoria(lista, n);

    return 0;
}
    
