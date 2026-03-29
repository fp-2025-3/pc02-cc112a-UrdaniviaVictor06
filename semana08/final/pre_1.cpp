#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;




//____________________________--


int **crearMatriz(int n, int m){
    int **copia = new int*[n]; // crea n columnas 

    for(int i=0; i< n; i++){
        copia[i] = new int[m]; // para cada columna crea m filas
    }


    return copia;
}

void llenarMatriz(int **matriz, int n, int m){
    for(int i=0; i< n; i++){
        // recorre las columnas
        for(int j=0; j< m; j++){
            // recorre las filas por columna
            matriz[i][j] = (i+1)*(j+1);
        }
    }
}

void mostrarMatriz(int **matriz, int n, int m){
    cout << "\nMATRIZ CREADA :\n";
    for(int i=0; i< n; i++){
        // recorre las columnas
        for(int j=0; j< m; j++){
            // recorre las filas por columna
            cout << matriz[i][j]<< " ";
        }
        cout << endl;
    }
}

int *sumaFilas(int **matriz, int n, int m){
    int *copia = new int[n]; // reserva n espacios (|)
    for(int i=0; i <n; i++){ // recorre columnas
        int suma = 0;
        for(int j=0; j< m; j++){ // recorre filas
            suma = suma+matriz[i][j]; // esto suma cada fila 
        }
        copia[i] = suma;
    }

    return copia;
}

void liberarMatriz(int **matriz, int n){
    for(int i=0; i<n ; i++){
        delete[] matriz[i]; // borramos cada fila
    }
    delete[] matriz;
}


int main(){

    int m =-1;
    while(m<=0 ){
        cout << "\nIngrese la cantidad de columnas (m): ";
        cin >>m;
    }
    // aseguramos que n sea positivo

    int n =-1;
    while(n<=0 ){
        cout << "\nIngrese la cantidad de filas (n): ";
        cin >>n;
    }
    // m es positivo


    int **matriz = crearMatriz(n, m); // columnas y filas

    llenarMatriz(matriz, n, m); // n filas y m columnas

    mostrarMatriz(matriz, n, m);

    int *vector = sumaFilas(matriz, n, m);
    
    cout << "\nVECTOR SUMA DE FILAS: \n";
    for(int i=0; i< n; i++){
        cout << vector[i] <<endl;
    }
    cout << endl;
    

    liberarMatriz(matriz, n); 
    delete[] vector; // liberar memoria dinamica
    return 0;
}