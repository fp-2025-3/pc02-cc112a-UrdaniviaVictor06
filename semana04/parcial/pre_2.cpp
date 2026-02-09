#include <iostream>

using namespace std;

const int N=30;


void traspaseDePalabras(char *A, char *B){
    char *temp= new char[30]; //reservo un puntero de 30 caracteres

    int indice1=0;
    for(char *p = A; *p!= '\0'; p++){
        *(temp+indice1) = *p;
        indice1++;
    }
    *(temp+indice1) = '\0';

    int indice2=0;
    for(char *p = B; *p!= '\0'; p++){
        *(A+indice2) = *p;
        indice2++;
    }
    *(A+indice2) = '\0';

    int indice3=0;
    for(char *p = temp; *p!= '\0'; p++){
        *(B+indice3) = *p;
        indice3++;
    }
    *(B+indice3) = '\0';



    delete[] temp;
}

void leerDatos(char *lista[N], int *tiempo, int n){
    for(int i=0; i<n; i++){
        char *nombre = new char[30];
        cout<<"Nombre del corredor "<<i+1<<" : ";
        cin>> nombre;
        cin.ignore(100, '\n');

        //traspase de nombre
        lista[i] = nombre;

        tiempo[i] =0;
        while(tiempo[i] <= 0){
            cout<< "Ingresa el tiempo del corredor \n";
            cin >> tiempo[i];
        }
        
    }
}

void ordenarPorTiempo(char *lista[N], int *tiempo, int n){
    //selection sort
    for(int i=0; i<n; i++){
        int minimo=tiempo[i];
        int indice=i; //el indice empieza con el for mayor
        for(int j=i; j<n; j++){
            if(tiempo[j] < minimo){
                minimo=tiempo[j];
                indice=j;
            }
        }
        swap(tiempo[i], tiempo[indice]);

        //swap con el nombre
        swap(lista[i], lista[indice]);
        

    }
}

void imprimirDatos(char *lista[N], int *tiempo, int n){
    for(int i=0; i<n; i++){
        cout<<lista[i]<<" --- "<<tiempo[i]<<" \n";
    }
}

int main(){

    int n_atle;
    cout << "Ingrese la cantidad de corredores: ";
    cin>> n_atle;

    char *lista[n_atle];
    //reservo una lista de n_atle punteros char
    int tiempo[n_atle];

    leerDatos(lista, tiempo, n_atle);
    imprimirDatos(lista, tiempo, n_atle);

    cout << " --------------------------------\n";
    ordenarPorTiempo(lista, tiempo, n_atle);
    imprimirDatos(lista, tiempo, n_atle);
    return 0;
}