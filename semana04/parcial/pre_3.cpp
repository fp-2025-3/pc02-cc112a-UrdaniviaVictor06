#include <iostream>
using namespace std;

const int N = 3;  

bool esFilaDominanteEstricta(int (*M)[N], int f){

    // Recorremos cada columna j
    int indice=0;
    for( int (*i)[N] = M; i<M+N; i++){
        int fila=M -i; 
        if(fila ==f ){
            continue;
        }
        for(int *j= *i; j<*i +n; j++){
                
        }
    }

    
    return true;
}


bool esFilaFuertementeDominante(int (*M)[N], int f){

    
    return true;
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

    int (*M)[N];
    int n=N;
    cout << "Matriz:\n";
    
    llenado(M, n);
    imprimir(M, n);
    
   

    return 0;
}
