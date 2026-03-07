#include <iostream>
#include <cstring>

using namespace std;

struct fecha{
    int dia;
    int mes;
    int year;
};

struct contacto{
    char nombre[30];
    fecha nacimiento;
};

//________________________________________________________________________________

struct contacto * expandir(struct contacto *lista, int* n, int k){
    struct contacto *copia= new struct contacto[*n+k]; //reservo n+k elementos

    //vamos a copiar todo
    for(int i=0; i<*n; i++){
        strcpy(copia[i].nombre, lista[i].nombre); //ojo esto funciona por que son char[]
        // si fueran punteros, seria distinto

        
        copia[i].nacimiento.dia = lista[i].nacimiento.dia;
        copia[i].nacimiento.mes = lista[i].nacimiento.mes;
        copia[i].nacimiento.year = lista[i].nacimiento.year;
        
    }

    delete[] lista;
    return copia;
}

void leerDatos(struct contacto *&lista, int *n, int *indice){
    if(*indice == (*n) -1){
        lista = expandir(lista, n,*n);
        *n = *n *2;
    }

    int res=-1;
    while(res != 0 && res != 1){
        cout << "Desea ingresar un contacto? (1=si, 0=no): ";
        cin >>res;
        cin.ignore();
    }

    if(res == 1){
        cout <<"Ingrese el nombre de la persona: ";
        cin.getline( lista[*indice].nombre, 30);

        cout << "Ingrese su fecha de nacimiento:\n";
        cout << "dia : ";
        cin >> lista[*indice].nacimiento.dia;
        cout << "mes : ";
        cin >> lista[*indice].nacimiento.mes;
        cout << "year : ";
        cin >> lista[*indice].nacimiento.year;

        *indice = (*indice) + 1;
        leerDatos(lista, n, indice);
    }

}

void imprimir(struct contacto *lista, int *n){

    for(int i=0; i<*n; i++){
        cout << lista[i].nombre<< endl;
        
        cout << lista[i].nacimiento.dia;
        cout << "/"<< lista[i].nacimiento.mes;
        cout << "/"<< lista[i].nacimiento.year<< endl;
        
    }
}

void imprimirYear(struct contacto *lista, int *indice, int *year){
    for(int i=0; i<(*indice)+1; i++){
        if(lista[i].nacimiento.year == *year){
            cout << "Nombre: " <<lista[i].nombre<< endl;
            cout << lista[i].nacimiento.dia << "/";
            cout << lista[i].nacimiento.mes << "/";
            cout << lista[i].nacimiento.year << endl;
        }
    }
}
                     

int main(){

    int n_max=3; 
    int *p_n_max=&n_max;
    int n_indice=0, *p_n_indice=&n_indice;
    struct contacto *lista= new struct contacto[*p_n_max]; //reservo un arreglo de n elementos

    //todos son punteros
    leerDatos(lista, p_n_max, p_n_indice);
    cout << "__________________________\n";

    int year;
    cout <<"Ingrese el año a buscar: ";
    cin >> year;

    int *p_year= &year;


    imprimirYear(lista, p_n_indice, p_year);



    return 0;
}