#include <iostream>
using namespace std;

const int N=5;

bool esFilaDominante(int (*M)[N], int fila){
    //si todos los elementos de las filas son mayores que todos los elementos de las columnas
    // que ocupan dichos elementos en su fila

    for( int (*i)[N]=M; i<M +N; i++){ // i recorre todos los punteros
        int indice=0;
        if( i == M +fila -1){  //cuando i toma el indice de la fila, se salta un for
            continue;
        }
        for(int *j = *i; j< *i + N; j++){ // j recorre todos los numeros de cada puntero i
            if( *j > *(*(M +fila -1)+indice) ){
                return false;
            }
            indice++;
        }
    }
    return true;
}

int contarColumnasCriticas(int (*M)[N]){
    /*Una columna se considera crítica si la suma de sus elementos es mayor que la suma
     de cualquier fila de la matriz.
    La función debe retornar la cantidad total de columnas críticas.  
    */

    int sumaColumna[N];

    //inicializo N con puros ceros
    for(int i=0; i<N; i++){
        sumaColumna[i]=0;
    }

    //suma cada columna y lo almaceno en el arreglo
    for(int i=0; i<N; i++){
        for(int (*j)[N] = M; j<M+N; j++){
            sumaColumna[i]= sumaColumna[i] + *(*(j + 0) + i);
        }
    }
    //ya tengo la suma de cada columna

    int resultado=0;
    
    for(int m=0; m<N; m++){ //m recorre las sumas de todas las columnas
        int conteo=0;
        for(int (*i)[N] = M; i< M +N; i++){ // recorremos la matriz
            int suma=0;
            for(int *j =*i; j<*i +N; j++){
                suma = suma + *j;
            }
            //ya tengo la suma de la i_esima fila
            if(sumaColumna[m] > suma ){ //si columna mayor que toda fila => conteo=N
                conteo++;
            }
        }
        if(conteo == N){
            resultado++;
        }

    }
    return resultado;
}

bool esMatrizEscalonada(int (*M)[N]){
    /* Una matriz es escalonada si, para cada fila, la posición del primer elemento
    no nulo aparece en una columna estrictamente mayor que la del primer elemento no nulo
    de la fila anterior.*/
    int posicion[N];
    for(int (*i)[N] = M+N; i>M; i--){
        for(int *j=*i; j<*i + N; j++){
            if(*j == 0 *(j+1) != 0){
                posicion[]
            }
        }
    }
    return true;
}

void llenado(int (*M)[N], int filas, int columnas){
    for(int (*i)[N]= M ; i<M +filas; i++){
        for(int *j=*i; j<*i+ columnas; j++){
            *j= rand()%10; // del 0 al 9
        }
    }
}

void imprimirMatriz(int (*M)[N], int filas, int columnas){
    for(int (*i)[N]= M ; i<M +filas; i++){
        for(int *j=*i; j<*i+ columnas; j++){
            cout << *j <<" ";
        }
        cout << endl;
    }
}

int main(){
    
    int M[N][N];
    int filas=5, columnas=5;

    llenado(M, filas, columnas);
    imprimirMatriz(M, filas, columnas);
    cout << "_____________________"<< endl;

    int k=3; //tercera fila indice 2
    
    /*
    esto es una prueba de que si funciona si es dominante o no

    M[1][3]=0;  //segunda fila, indice 1 con columna 4, indice 3 =0
    M[4][3]=0;  //quinta fila, indice 4 con columna 4, indice 3 =0;
    for(int i=0; i<N; i++){
        M[k-1][i]=9; //tercera fila, indice 2 , todos son 9
    }
    */
    imprimirMatriz(M, filas, columnas);
    
    cout<< "Sea la fila : " <<k<< " \n";
    if(esFilaDominante(M, k)){
        cout<< "La fila "<<k<< " si es dominante \n";
    } else {
        cout << "La fila "<<k<< " no es dominante \n";
    }

    int n_col_criticas=contarColumnasCriticas(M);
    cout<<"La cantidad de columnas criticas: "<<n_col_criticas<< endl;

    if(esMatrizEscalonada(M)){
        cout<<"Si es una matriz escalonada \n";
    } else {
        cout<< "No es una matriz escalonada \n";
    }
    return 0;
}