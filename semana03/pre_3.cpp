#include <iostream>
using namespace std;

void permutacion(int **matriz,int entero[9], int fi, int col){
    for(int i=0; i<fi; i++){
        for(int j=0; j<col; j++){
            int indice=rand()%9; //indice del 0 a 8
            swap(entero[j], entero[indice]); //intercabio de variables
        }
        for(int p=0; p<col ; p++){
            matriz[i][p]=entero[p]; //copio variable por variable
        }
    }
}

void acomodo(int **matriz, int i, int j){
    int valor=matriz[i-1][j-1]; //valor seleccionado
    for(int p=0; p<9; p++){ 
        while(matriz[p][j-1] != valor){ //posicion i,j diferente de valor
            int temp=matriz[p][0]; 
            for(int m=0;m<9-1; m++){
                matriz[p][m]=matriz[p][m+1]; //desplazamiento a la isquierda
            }
            matriz[p][8]=temp;
        }
    }
}

void imprimirMatriz(int **matriz, int fi, int col){
    for(int i=0; i<fi; i++){
        for(int j=0; j<col; j++){
            cout<<matriz[i][j]<<"  ";
        }
        cout<<endl;
    }
}

int main(){
    int filas=9, columnas=9; 

    int **matriz=new int*[filas]; 

    for(int i=0; i<filas; i+=1){
        matriz[i]=new int[columnas];
    }

    int ent[]={1,2,3,4,5,6,7,8,9};
    permutacion(matriz, ent, filas, columnas);

    cout<<"Matriz inicial \n";
    imprimirMatriz(matriz, filas, columnas);

    int i=0;
    while(i<=0 || i>9){
        cout<<"Fila inicial (1-9): ";
        cin>>i;
    }

    int j=0;
    while(j<=0 || j>9){
    cout<<"Columna inicial (1-9): ";
    cin>>j;
    }
    cout<<"Valor seleccionado : "<<matriz[i-1][j-1]<<endl;

    acomodo(matriz, i, j);

    cout<<"Matriz final \n";
    imprimirMatriz(matriz, filas, columnas);
    return 0;
}
