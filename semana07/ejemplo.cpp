#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX = 100;

struct Libro {
    int codigo;
    char titulo[50];
    bool prestado;
};

struct Usuario {
    int codigo;
    string nombres;
    int prestamos;
};

// Funciones a implementar


void registrarUsuario (){
    int codigo=-1;
    int respuesta1=-1;

    while(respuesta1 != 0 && respuesta1 !=1){
        cout << "si = 1, no = 0 \nTiene codigo de usuario?: ";
        cin >>respuesta1;
    }
    while(codigo < 100000 || codigo > 1000000){
        cout <<"Ingrese su codigo de usuario (6 numeros): ";
        cin >> codigo;

    }

}

void registrarLibro(struct Libro libros[MAX], int &n){
    int respuesta=-1;
    while( respuesta != 0 && respuesta != 1){
        cout << "si = 1, no = 0\nDesea agregar un libro? ";
        cin >> respuesta;
    }

    if(respuesta ==0) return ; // acaba la funcion

    n++;

    int codigo=-1;
    while(codigo < 101 || codigo >999){
        cout << "Ingrese el codigo de su libro (3 digitos no negativo): ";
        cin >> codigo;
    }
    libros[n-1].codigo=codigo;

    char titulo[50];
    cout << "Ingrese el titulo de su libro :";
    cin.ignore();
    cin.getline(titulo, 50);

    strcpy(libros[n-1].titulo, titulo);

    libros[n-1].prestado=false;

    registrarLibro(libros, n);

}

int buscarLibro(Libro libros[MAX], int n, int codigo){
    int orden=-1;
    for(int i=0; i<n ; i++){
        if(libros[i].codigo == codigo) orden = i+1;
    }

    if(orden ==-1){
        cout << "El libro con codigo "<< codigo << " no existe \n";
    } else{
        cout <<"Codigo: " << libros[orden-1].codigo << endl;
        cout << "Titulo: " << libros[orden -1].titulo << endl;
        if(libros[orden-1].prestado){
            cout << "Estado: Prestado\n";
        } else {
            cout << "Estado: Libre\n";
        }
        cout << "EL libro esta en el orden: "<< orden << endl;
    }
    return orden;
}

void prestarLibro(Libro libros[MAX],int n){
    int respuesta=-1;
    while(respuesta != 1 && respuesta !=0){
        cout << "si = 1, no = 0 \nDesea prestar un libro? : ";
        cin >> respuesta;
    } 

    if (respuesta ==0) return ;
    int codigo=-1;
    while(codigo < 100 || codigo > 999){
        cout << "Ingrese el codigo del ibro a prestar: ";
        cin >> codigo;
    }
}

void devolverLibro(Libro libros[], int n);

void guardarEnArchivo(Libro libros[], int n);

void cargarDesdeArchivo(Libro libros[], int n);

void mostrarLibros(Libro libros[MAX], int n){
    for(int i=0; i< n; i++){
        cout << "------------------\n";
        cout << "Codigo " << libros[i].codigo<< endl;
        cout << libros[i].titulo << endl;
        if(libros[i].prestado){
            cout << "Estado: prestado"<< endl;
        } else{
            cout << "Estado: libre"<< endl;
        }
    }



}

int inicio(){
    int respuesta=-1;
    while(respuesta !=0 && respuesta != 1){
        cout << "si = 1; no = 0\nTiene codigo de usuario? ";
        cin >> respuesta;
    }
    return respuesta;
    
}

void portada1(){

    char hola[30]="Biblioteca Virtul";
    int n=strlen(hola); // numero de caracteres de hola
    cout << setw(n + (40-n)/2)<<hola;
    cout << endl;
    for(int i=0; i< 20; i++){
        cout << "--";
    }
    cout << endl;
}

void portada(){
    for(int i=0; i< 20; i++){
        cout << "\n\n";
    }
    cout << "Que desea hacer? \n";
    cout << "1. ";
}

int main(){

    // Menú interactivo

    portada1(); // si tengo usuarios antiguos donde guardo estos datos?
    // la respuesta son los archivos xd
    int respuestaInicio = inicio();
    if(respuestaInicio == 1){ // significa que sus documentos ya existen 
        cout << "dejame pensar tantito sobre archivos\n";
    } else { // significa que debo registrar al nuevo usuario
        struct Usuario *usuarioNuevo = new struct Usuario; // memoria dinamica
        registrarUsuario();
    }

    int n=0; // esto tiene memoria guardad

    struct Libro libros[MAX];
    registrarLibro(libros, n);

    portada();
    mostrarLibros(libros, n);

    int codigoBuscar;
    cout << "Ingrese el codigo a buscar de un libro: ";
    cin >> codigoBuscar;

    portada();
    int orden = buscarLibro(libros, n, codigoBuscar);

    int respuesta=-1;
    while(respuesta != 1 && respuesta !=0){
        cout << "si = 1, no = 0 \nDesea prestar un libro? : ";
        cin >> respuesta;
    }    
    prestarLibro(libros, n);

    
    

    delete usuarioNuevo;
    return 0;
}