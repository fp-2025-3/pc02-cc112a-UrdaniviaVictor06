#include <iostream>
#include <iomanip>

using namespace std;

const int N = 8; // 5 esta bien  

bool esFilaDominanteEstricta(int (*M)[N], int f){  //f es la fila no el indice

    //recorremos el arreglo por filas
    for( int (*i)[N]=M; i<M +N; i++){ // i recorre todos los punteros
        int indice=0;
        if( i == M +f -1){  //cuando i toma el indice de la fila, se salta un for
            continue;
        }
        for(int *j = *i; j< *i + N; j++){ // j recorre todos los numeros de cada puntero i
            if( *j > *(*(M +f -1)+indice) ){
                return false;
            }
            indice++;
        }
    }
    //si la funcion llega hasta aqui, significa que ya tenemos la mitad del arreglo

    //recorremos la fila
    int minimo=*(*(M+f-1) +0); //agarramos el primer elemento de la fila f como minimo
    for(int *j = *(M+f-1) ; j< *(M +f -1) +N; j++){
        if(*j < minimo){
            minimo=*j;
        }
    }
    //ya tengo al minimo (no conozco su posicion)

    //recorremos el arreglo por columnas, esceptuando la fila f
    for(int i=0; i<N; i++){ //columnas
        int contador=0;

        for(int j=0; j<N; j++){ //filas

            if(j == f-1) continue;

            if( *(*(M + j) +i) >= minimo ){
                break;
            }
            contador++;
        }
        if(contador==N-1) return true;  //todos los numeros de una columan son menores que el minimo
    }
    return false;
}  //SI FUNCIONA


bool esFilaFuertementeDominante(int (*M)[N], int f){
    if(esFilaDominanteEstricta(M, f) == false){
        return false;
    }

    int sumaFinal[N]; //arreglo de ceros
    for(int i=0; i<N; i++){
        sumaFinal[i] =0;
    }

    //recorremos matriz
    int indice=0;
    for( int (*i)[N]=M; i<M +N; i++){ 
        for(int *j = *i; j< *i + N; j++){ 
            sumaFinal[indice] += *j;
        }
        indice++;
    } //el arreglo tiene la suma de cada fila

    int contador=0;
    for(int i=0; i<N; i++){
        if(i == f-1) continue;

        if(sumaFinal[i] < sumaFinal[f-1]) contador++;
        
    }
    if(contador ==N-1){
        return true;
    } else {
        return false;
    }
}

void imprimirSalida(int (*M)[N], int n){
    cout << "Fila"<< setw(20) << "Dominante Estricta"<< setw(25)<< "Fuertemente Dominante\n";
    for(int i=0; i<45; i++){
        cout << "-";
    }
    cout << endl;
    
    //el setw no separa lineas, sino que imprime la siguiente linea en un cierto espacio

    for(int i=0; i<N; i++){
        bool D_E = esFilaDominanteEstricta(M, i+1);
        bool F_D_E= esFilaFuertementeDominante(M, i+1);
        if(D_E && F_D_E){
            cout << i << setw(6) << "Si"<< setw(20)<< "Si"<< endl;
        } else if(D_E){
            cout << i << setw(6) << "Si"<< setw(20)<< "No"<< endl;
        } else if(F_D_E){
            cout << i << setw(6) << "No"<< setw(20)<< "Si"<< endl;
        } else {
            cout << i << setw(6) << "No"<< setw(20)<< "No"<< endl;
        }
    
    }
}

void llenado(int (*M)[N], int n){
    for( int (*i)[N] = M; i<M+N; i++){
        for(int *j= *i; j<*i +n; j++){
            *j=rand()%10 ; //del 0 al 9
        }
    }
}

void imprimir(int (*M)[N], int n){
     for( int (*i)[N] = M; i<M+N; i++){
        for(int *j= *i; j<*i +n; j++){
            cout << *j<<" ";
        }
        cout << endl;
    }
}


int main(){

    int matriz[N][N];
    int (*M)[N]=matriz; // N=5
    int n=N;
    cout << "Matriz:\n";
    
    llenado(M, n);
    imprimir(M, n);

    imprimirSalida(M, n);



    return 0;
}
