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

void rellenarDatos(struct polinomio *array, int n){

    // supongamos que n=3 
    array[0].coef = new float[array[0].n];
    array[1].coef = new float[array[1].n];
    array[2].coef = new float[array[2].n];

    //rellenando
    array[0].coef[0] =  1;
    array[0].coef[1] = 0;
    array[0].coef[2] = 3;

    array[1].coef[0] = -4;
    array[1].coef[1] = 5;

    array[2].coef[0] = 3;
    array[2].coef[1] = 0;
    array[2].coef[2] = 1;

    /*tomando otros datos 
    array[0].coef[0] = 3;
    array[0].coef[1] = 2;
    array[0].coef[2] = 7;

    array[1].coef[0] = -3;
    array[1].coef[1] = 5;

    array[2].coef[0] = 1;
    array[2].coef[1] = 2;
    array[2].coef[2] = 3;
    */
}


void mostrarPol(struct polinomio *array, int n){
   for(int i=0; i<n; i++){  // recorremos todos los polinomios
    cout << "Polinomio "<<i+1 << " : ";
    for(int j=0; j< array[i].n ; j++){  // esto recorreo el polinomio i
        if(array[i].coef[j] == 0) continue;

        cout << array[i].coef[j];
        if(j!=array[i].n-1) cout <<"x^"<<array[i].n -j-1;

        if(j != array[i].n -1) cout << " + ";
        
    }
    cout << endl;

   }
}

void sumaPol(struct polinomio *array, int n){

    /*                                              Cantidad maxima = 3
        La funcion que deeo crear debera sumar       [1, 0, 3]  diferencia = 0  |
        todos los elementos de una columna, y       [x ,-4 , 5]  diferencia = 1 |
        si se trata de un polinomio con grado in-   [3, 0 ,1]   diferencia = 0  | 
        ferior al polinomio de mayor grado,       ----------------------------  V
        entonces se usara la diferncia para 
        trasladar la suma k_i espacios 
        (k_i =diferencia entre el polinomio i y el de mayor grado)
     */



    // encontremos el polinomio de mayor grado
        int indice=0;
        for(int j=0; j<n; j++){
            if(array[j].n > array[indice].n){
                indice = j;
            }
        }
        // ya tengo al maximo
        int n_max=array[indice].n;
    

    // al ser n polinomios (n=3), debo tener n diferencias
    int *diferencia = new int[n]; // memoria dinamica

    for(int i=0; i <n; i++)    diferencia[i] = array[indice].n - array[i].n ;
    

    //sumando todo en un nuevo array;
    float *coef_1= new float[n_max]; //reservando memoria

    for(int i=0; i< n_max; i++)    coef_1[i] =0; // todos son ceros
    
    for(int i=0; i<3; i++){ //recorremos todas los polinomios
        for(int j=0; j<array[i].n; j++){ // recorres cada polinomio
            coef_1[j + diferencia[i]] += array[i].coef[j];  
        }
    }

    cout <<"\nLa suma de los tres polinomios: ";
     for(int i=0; i< n_max ; i++){
        if(coef_1[i] == 0) continue;

        cout << coef_1[i];
        if(i!=n_max-1) cout <<"x^"<<n_max -i-1;

        if(i != n_max -1) cout << " + ";
        
    }
    cout << endl;
    delete[] coef_1;
    delete[] diferencia;
}


void multiplicacion(struct polinomio *array, int n){

    /* Suponiendo n=3, entonces se requieres dos operaciones de multiplicacion
    A x B x C = array_total
    Esta funcion deberá multiplicar dos polinomios consecutivos (A y B), los guardara en un
    arreglo y volvera a mutiplicar dos polinomios consecutivos (AB y C), nuevamente los 
    almacenara y seguira su proceso n-1 veces
    */

    // vamos a multiplicar n-1 veces,
    
    // primero creamos un array dinamico para empezar con el bucle for
    int n_1= (array[0].n -1 ) + (array[1].n -1) +1;
    float *coef_2 = new float[n_1]; // memoria dinamica

    for(int i=0; i<n_1; i++) coef_2[i] =0; // relleno con puros ceros

    
    for(int i=0; i< n-1; i++){
        if( i == 0){

            for(int i_1=0; i_1 < array[i].n ; i_1++){ //recorres al primer polinomio
                for(int j=0; j< array[i+1].n; j++){ // recorremos el segundo polinomio
                    coef_2[i_1+j] +=  array[i].coef[i_1] * array[i+1].coef[j]; 
                
                }
            }

        } else { // si entras aqui es porque estamos multiplicando y almacenando en dos arrays

            int n_2= (n_1 -1 ) + (array[i+1].n -1) +1;
            float *coef_3 = new float[n_2]; // memoria dinamica

            for(int i=0; i<n_2; i++) coef_3[i] =0; // relleno con puros ceros

            for(int i_1=0; i_1 < n_1 ; i_1++){ //recorres al primer polinomio
                for(int j=0; j< array[i+1].n; j++){ // recorremos el segundo polinomio
                    coef_3[i_1+j] +=  coef_2[i_1] * array[i+1].coef[j]; 
                    // almacenamos todo en el coef_3
                }
            }

            delete[] coef_2; // el puntero coef_2 apunta al vacio (puntero colgante)
                            // osea que delete[] borra la informacion que viene despues del puntero
                            // mas no el puntero, por eso el puntero aun existe pero no esta siendo usado    
            coef_2 = coef_3;
            n_1 = n_2;

            // borras informacion de puntero viejo y puntero viejo apunta a puntero nuevo

        }
        
    }


    //imprimir
     cout <<"\nLa multiplicacion de loss tres polinomios: ";
     for(int i=0; i< n_1 ; i++){
        if(coef_2[i] == 0) continue;

        cout << coef_2[i];
        if(i!=n_1-1) cout <<"x^"<<n_1 -i-1;

        if(i != n_1 -1) cout << " + ";
        
    }
    cout << endl;

    delete[] coef_2;
}

void liberarEspacio(struct polinomio *array, int n){
    for(int i=0; i< n; i++){
        delete[] array[i].coef;
    }
    delete[] array;

}


int main(){
   
    int n_t= 3; //cantidad de elementos
    struct polinomio *arreglo= new struct polinomio[n_t]; // array de n polinomios  

    arreglo[0].n = 3;
    arreglo[1].n = 2;
    arreglo[2].n = 3;

    rellenarDatos(arreglo, n_t); // array de polinomios y entero

    mostrarPol(arreglo, n_t);

    sumaPol(arreglo, n_t);

    multiplicacion(arreglo, n_t);

    liberarEspacio(arreglo, n_t);
 
    return 0;
}