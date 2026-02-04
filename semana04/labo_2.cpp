#include <iostream>
using namespace std;

const int N=5;

bool esFilaDominante(int (*M)[N], int fila){
    //si todos los elementos de las filas son mayores que todos los elementos de las columnas
    // que ocupan dichos elementos en su fila

    for( int (*i)[N]=M; i<M +N && i!= M+fila -1 ; i++){ //la fila es el numero de fila, no el indice de fila
        int indice=0;
        for(int *j = *i; j< *i + N; j++){
            
            if( *j > *(*(M +fila)+indice) ){
                return false;
            }
            indice++;
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

    int k=2;
    M[1][3]=0;
    M[4][3]=0;
    for(int i=0; i<N; i++){
        M[k][i]=9;
    }
    imprimirMatriz(M, filas, columnas);
    
    cout<< "Sea la fila 3 : \n";
    if(esFilaDominante(M, k)){
        cout<< "La fila "<<k<< " si es dominante \n";
    } else {
        cout << "La fila "<<k<< " no es dominante \n";
    }
    return 0;
}