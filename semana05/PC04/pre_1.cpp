#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

struct polinomio{
    int n; 
    float *coef; //memoria dinamica 
};

//______________________________________________

void rellenarDatos(struct polinomio *A, int n_a, struct polinomio *B, int n_b, struct polinomio *C,
    int n_c){

    // array dinamico
    A->coef = new float[n_a];
    B->coef = new float[n_b];
    C->coef = new float[n_c];

    //rellenando
    A->coef[0] =  1;
    A->coef[1] = 0;
    A->coef[2] = 3;

    B->coef[0] = -4;
    B->coef[1] = 5;

    C->coef[0] = 3;
    C->coef[1] = 0;
    C->coef[2] = 1;


}


void mostrarPol(struct polinomio *A, int n){
    for(int i=0; i< n;i++){
        if(A->coef[i] == 0) continue;

        cout << A->coef[i];
        if(i!=n-1) cout <<"x^"<<n-i-1;

        if(i != n-1) cout << " + ";
        
    }
    cout << endl;
}

void sumaPol(struct polinomio *A, struct polinomio *B, struct polinomio *C){
    struct polinomio orden[3] = {*A, *B, *C}; // vamos a ordenarlos

    for(int i=0; i<3; i++){
        // tomamos como maximo al mayor
        int maximo = orden[i].n;
        int indice=i;
        for(int j=i; j<3; j++){
            if(orden[j].n > orden[indice].n){
                indice = j;
                maximo = orden[indice].n;
            }
        }
        // ya tengo al maximo
        swap(orden[i], orden[indice]); // ordenando de mayor a menor
    }

    // al ser n polinomios (n=3), debo tener n-1 diferencias
    int diferencia[3];

    for(int i=0; i <3; i++){
        diferencia[i] = orden[0].n - orden[i].n ;
    }

    //sumando todo en un nuevo array;
    float coef[orden[0].n];
    int n_max = orden[0].n;

    for(int i=0; i< n_max; i++){
        coef[i] =0; // todos son ceros
    }

    for(int i=0; i<n_max; i++){ //recorres todas los polinomios
        for(int j=0; j<orden[i].n; j++){ // recorres cada polinomio
            coef[j + diferencia[i]] += orden[i].coef[j];
        }
    }

    cout <<"\nLa suma de los tres polinomios: ";
     for(int i=0; i< n_max ; i++){
        if(coef[i] == 0) continue;

        cout << coef[i];
        if(i!=n_max-1) cout <<"x^"<<n_max -i-1;

        if(i != n_max -1) cout << " + ";
        
    }
    cout << endl;

}


void multiplicacion(struct polinomio *A, struct polinomio *B, struct polinomio *C){

    // suponiendo n=3; y 2 multiplicaciones

    int n_1= (A->n -1) + (B->n -1) +1; // A x B
    float *suma_1 = new float[n_1]; // reservo
    for(int i=0; i < A->n ; i++){ //recorres al A
        for(int j=0; j< B->n; j++){
            suma_1[i+j] +=  A->coef[i] * B->coef[j];
        }
    }

    int n_2= (n_1 -1) + (C->n -1) +1; // AB x C
    float *suma_2 = new float[n_2]; // reservo
    for(int i=0; i < n_1 ; i++){ //recorres al AB
        for(int j=0; j< C->n; j++){
            suma_2[i+j] +=  suma_1[i] * C->coef[j]; //joder que sencillo
        }
    }

    //imprimir
     cout <<"\nLa multiplicacion de loss tres polinomios: ";
     for(int i=0; i< n_2 ; i++){
        if(suma_2[i] == 0) continue;

        cout << suma_2[i];
        if(i!=n_2-1) cout <<"x^"<<n_2 -i-1;

        if(i != n_2 -1) cout << " + ";
        
    }
    cout << endl;
   

    delete[] suma_2;
    delete[] suma_1;
}

void liberarEspacio(struct polinomio *A, struct polinomio *B, struct polinomio *C){
    delete[] A->coef;
    delete[] B->coef;
    delete[] C->coef;

    delete A;
    delete B;
    delete C;
}


int main(){
   
    struct polinomio *A = new struct polinomio;
    struct polinomio *B = new struct polinomio;
    struct polinomio *C = new struct polinomio;

    A->n = 3;
    B->n = 2;
    C->n = 3;

    rellenarDatos(A, A->n, B, B->n, C, C->n);

    cout << "Polinomio 1: ";
    mostrarPol(A, A->n);
    cout << "Polinomio 2: ";
    mostrarPol(B, B->n);
    cout << "Polinomio 3: ";
    mostrarPol(C, C->n);
 
    sumaPol(A, B, C);

    multiplicacion(A, B, C);

    liberarEspacio(A, B, C);
 
    return 0;
}