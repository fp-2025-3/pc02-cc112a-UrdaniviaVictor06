#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

struct item{
    char *descripcion; // memoria dinamica
    int cantidad;
    double precioUnitario;
};

struct pedido{
    int numeroPedido;
    char *nombreCliente; //memoria dinamica
    struct item *item; //arreglo dinamico de items
    int cantidadItems;
};


//_____________________________________________________________-

struct item crearItem(const char *descripcion, int cantidad, double precio){
    struct item nuevo;

    // rellenando el item
    nuevo.descripcion = new char[30]; //reserva memoria
    strcpy(nuevo.descripcion, descripcion); // copiar 

    nuevo.cantidad = cantidad;
    nuevo.precioUnitario = precio;

    return nuevo;
}

struct pedido *crearPedido(int numero, const char *cliente, int cantidadItems){
    struct pedido *cliente1 =new struct pedido; // reservo pedido

    //rellenando el pedido
    cliente1->numeroPedido = numero;

    cliente1->nombreCliente = new char [30]; 
    strcpy(cliente1->nombreCliente, cliente); //nombre copiado

    cliente1->cantidadItems = cantidadItems;

    // aqui usaria un bucle for para ir llamndo a la funcion crearItem, pero lo hare de forma mecanica
    //suponga la cantidad = 3
    cliente1->item = new struct item[cantidadItems]; // reservo para n items

    //forma mecanica
    cliente1->item[0] = crearItem("Laptop", 5, 200); 
    cliente1->item[1] = crearItem("Mouse", 4, 180);
    cliente1->item[2] = crearItem("Teclado", 2 , 150);



    return cliente1;
}

double calcularTotal(const struct pedido *p){
    double total=0;
    for(int i=0; i< p->cantidadItems; i++){
        total = (p->item[i].cantidad *p->item[i].precioUnitario ) + total; 
    }
    return total;
}

struct item *itemMasCaro(struct pedido *lista){
    struct item *nuevo = new struct item; // reservo memoria

    nuevo = &lista->item[0];
    // diremos que el precio mas alto es el prinmero, nuevo apunta al primer elemento

    for(int i=0; i< lista->cantidadItems; i++){
        if(lista->item[i].precioUnitario > nuevo->precioUnitario){
            nuevo = &lista->item[i]; // nuevo apunta al elemento i
        }
    }

    return nuevo;
}

void liberarPedido(struct pedido *lista){
    for(int i=0; i< lista->cantidadItems; i++){
        delete lista->item[i].descripcion; // 
    }
    delete[] lista->nombreCliente;
    delete lista;
}

void imprimirCliente(struct pedido *cliente){
    cout << "\nPedido N°: "<<cliente->numeroPedido;
    cout << "\nCliente: "<<cliente->nombreCliente;
    cout << "\n \nItems : ";

    for(int i=0; i< cliente->cantidadItems; i++){
        cout << "\n- "<< cliente->item[i].descripcion ; // el item es un array y usa punto
        cout << " | Cantidad: "<< cliente->item[i].cantidad; // el cliente es un puntero a variable
        cout << " | Precio: "<< cliente->item[i].precioUnitario;
    }
    cout << endl;

}

int main(){

    struct pedido *cliente1 = crearPedido(101, "Carlos Perez", 3);
    
    imprimirCliente(cliente1);
    
    cout << "\nTotal : "<< calcularTotal(cliente1)<< endl;

    struct item *caro = itemMasCaro(cliente1);
    cout <<"\nItem mas caro: "<<caro->descripcion << " | Precio: "<< caro->precioUnitario << endl; 


    liberarPedido(cliente1);
    return 0;
}

