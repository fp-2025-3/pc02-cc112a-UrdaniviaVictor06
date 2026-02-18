#include <iostream>

using namespace std;

struct estudiantes{
    char nombre[30]; //nombre maximo de 29 letras
    int edad;
    float promedio;
};

void leerDatos(struct estudiantes *array, int n){
    for(int i=0; i<n ; i++){
        cout << "Ingrese el nombre de tu alumno "<< i+1 << ": ";
        cin.getline(array[i].nombre, 30);

        cout << "Ingrese la edad de tu alumno "<< i+1 << ": ";
        cin >> array[i].edad;

        cout << "Ingrese el promedio de tu alumno "<< i+1 << ": ";
        cin >> array[i].promedio;
        cin.ignore();
    }
}


void imprimirAprobados(struct estudiantes *array, int n){
    cout << endl;
    for(int i=0; i<n; i++){
        if(array[i].promedio >= 10){
            cout<< "Nombre: "<< array[i].nombre << "  edad: "<<array[i].edad <<endl;
            cout << "Promedio: "<<array[i].promedio <<endl;
        }
    }
}

int main(){

    int n;
    cout << "Ingrese la cantidad de estudiantes : ";
    cin >> n;
    cin.ignore();

    struct estudiantes *array=new struct estudiantes[n]; //reservo n estudiantes

    leerDatos(array, n);

    
    imprimirAprobados(array, n);
    delete[] array;

    return 0;
}