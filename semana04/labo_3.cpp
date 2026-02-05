#include <iostream>

const int N=5;
using namespace std;


int conteo(int numero){
    int res=0;
    while(numero/10 >=1){ //ahora si cuenta digitos
        res++;
        numero= numero/10;
    }
    return res+1;
}


void leerDatos3(int *codigo, float *notas, int *faltas){

    for(int i=0; i<N; i++){
        codigo[i]=0;
        while(conteo(codigo[i]) != 8){ //no cuenta 01234567
        cout<<"Ingrese el codigo del alumno (8 digitos): "<<i+1<<" \n";
        cin>> codigo[i];
        }

        notas[i] =-1;
        while(notas[i] <0 || notas[i] > 20){
            cout<<"Ingrese la nota (0 al 20) del alumno : "<<i+1<<" \n";
            cin>>notas[i];
        }

        faltas[i]= -1;
        while(faltas[i] <0 || faltas[i] > 10){
            cout<<"Ingrese la cantidad de faltas (0 al 10) del alumno : "<<i+1<<" \n";
            cin>> faltas[i];
        }
    }
}

int main(){


    int codigo[N];
    float nota[N];
    int faltas[N];

    int n_prueba=conteo(1234);
    cout<<n_prueba<<endl;

    //leer datos completos
    leerDatos3(codigo, nota, faltas);
    return 0;
}