#include <iostream>
#include <cstring>

using namespace std;

struct estudiante{
    char nombre[30];
    float nota;
};

//_____________________________________--

void leerDatos(struct estudiante *lista, int *n){
    for (int i=0; i<*n; i++){
        cout << "Ingrese el nombre "<<i+1<< " : ";
        cin.getline(lista[i].nombre, 30);

        cout << "Ingrese la nota "<< i+1 << " : ";
        cin >> lista[i].nota;
        cin.ignore();
    }
}

void imprimeMaximo(struct estudiante *lista, int *n){
    int indice=0;
    float nota_maxima=lista[indice].nota;
    for(int i=0; i< *n ; i++){
        if (lista[i].nota > nota_maxima ){
            indice =i;
            nota_maxima=lista[indice].nota;
        }
    }

    //ya tenemos el maximo
    cout <<"La nota maxima es de : "<<lista[indice].nombre<<endl;
    cout << "Nota: " <<lista[indice].nota<< endl;
}

int main(){

    int n_inicial;
    cout << "Ingrese el numero de estudiantes : ";
    cin >> n_inicial;
    cin.ignore();

    int *p_n=&n_inicial; //puntero para facilidad

    struct estudiante *lista = new struct estudiante[*p_n]; //reservo p_n estudiantes

    leerDatos(lista, p_n);

    imprimeMaximo(lista, p_n);

    delete[] lista;
    return 0;
}