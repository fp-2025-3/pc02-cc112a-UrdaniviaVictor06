#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

struct producto{
    int codigo;
    char *nombre;
    double precio;
    int stock;
};



//__________________________________________________-_

struct producto crearProducto(int codigo, const char *nombre, double precio, int stock){ 
    // lo const char *, es por que definimos la funcion
    // si deseas ingresar nombres, usamos  char *
    struct producto nuevo;

    nuevo.codigo = codigo;
    nuevo.precio = precio;
    nuevo.stock =  stock;

    // lo siguiente parece funcionar con char , char []
    nuevo.nombre = new char; //reservo 30 espacios
    strcpy(nuevo.nombre, nombre);

    return nuevo;
}

struct producto *crearInventario(int n){
    struct producto *nuevo = new struct producto[n]; // reservo n espacios, es un arreglo 
    
    // definamos el entero n = 5
    nuevo[0] = crearProducto(100, "Teclado", 10.5, 5);
    nuevo[1] = crearProducto(101, "Mouse", 21, 10);
    nuevo[2] = crearProducto(102, "Monitor" , 31.5, 15);
    nuevo[3] = crearProducto(103, "Laptop", 42, 20);
    nuevo[4] = crearProducto(104, "Impresora", 52.5, 25);
    
    return nuevo;

}

struct producto *buscarProducto(struct producto *lista, int n, int codigoBuscado){
    struct producto *nuevo = new struct producto;

    for (int i=0; i<n ; i++){
        if(lista[i].codigo == codigoBuscado){
            nuevo = &lista[i];
            return nuevo;
        }
    } 
    nuevo=nullptr;

    return nuevo;
}


void imprimir(struct producto *lista, int n){
    cout << endl;
    for(int i=0; i<n; i++){

        cout << "Codigo: "<<lista[i].codigo<< " |";
        cout << "Nombre: "<< lista[i].nombre<< " |";
        cout << "Precio: "<< lista[i].precio << " |";
        cout << "Stock: "<< lista[i].stock << " |";
        cout << endl;
    }
    
}

void liberarInventario(struct producto *lista, int n){
    for(int i=0; i<n ; i++){
        delete[] lista[i].nombre;
    }
    delete[] lista;
}

int main(){

    int n=5;
    struct producto *lista = crearInventario(n);

    imprimir(lista, n);

    int codigo=102;
    cout <<"\nBuscando producto con codigo "<< codigo<<" ...\n";

    struct producto *buscado = buscarProducto(lista, n, codigo);
    
    cout << "Producto encontrado: "<<buscado->nombre << " | Precio: "<<buscado->precio<< endl;



    delete buscado;
    return 0;
}