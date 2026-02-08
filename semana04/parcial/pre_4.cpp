#include <iostream>
using namespace std;
 
int * expandir( int *array, int n, int k){ //xpande k espacios a mi arreglo de n elementos
    int *copia = new int[n+k]; //arreglo de n+k elementos

    for(int i=0; i<n; i++){ //copia los primeros n elementos
        copia[i]= array[i];
    }

    delete[] array;
    return copia;
}

int * contraer( int *array, int n, int k){ //contrae k espacios a mi arreglo de n elementos
    int *copia = new int[n-k]; //arreglo de n-k elementos

    for(int i=0; i<n-k; i++){ //copia los primeros n-k elementos
        copia[i]= array[i];
    }

    delete[] array;
    return copia;
}


int main(){
    
    int n=3;
    int *array=new int[n]; //reservo n espacios principales
    

    
    return 0;
}