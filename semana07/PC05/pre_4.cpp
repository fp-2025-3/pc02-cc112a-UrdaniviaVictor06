#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>


using namespace std;

struct Venta{ // 24 bytes
    int idVenta;
    int idVendedor;
    int idProducto;
    int cantidad;
    double precioUnitario;
};

struct Producto{
    int id; 
    int cantidad;
};


//________________________


int leerArchivo(string nombre_archivo){
    fstream archivo; // objeto de lectura y escritura

    int n=0;

    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario en modo lectura

    struct Venta prueba;
    while(archivo.read((char*)&prueba, sizeof(struct Venta))){
        // prueba ahora tiene al info
        n++;
    }

    archivo.close(); // desvinculamos
    return n;
}

double montoTotal(string nombre_archivo){
    fstream archivo; // objeto de lectura y escritura


    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario y de lectura

    double monto=0;
    struct Venta prueba;
    while(archivo.read((char*)&prueba, sizeof(struct Venta))){
        // prueba ahora tiene al info
        monto = monto + float(prueba.cantidad) * prueba.precioUnitario; 
    }

    cout << "Monto total: "<< monto << endl;



    archivo.close();
    return monto;
}

struct Venta ventaMaxima(string nombre_archivo, double &montoMax){
    struct Venta max;

    fstream archivo; // objeto de lectura y escritura


    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario y de lectura

    struct Venta prueba;
    while(archivo.read((char*)&prueba, sizeof(struct Venta))){
        // prueba ahora tiene al info
        double monto = float(prueba.cantidad) * prueba.precioUnitario; 
        if(montoMax < monto){
            max.idVenta = prueba.idVenta;
            max.idVendedor = prueba.idVendedor;
            max.idProducto = prueba.idProducto;
            max.cantidad = prueba.cantidad;
            max.precioUnitario = prueba.precioUnitario;
            montoMax = monto;
        }
    }
    archivo.close();

    return max;
}

struct Producto productoMasVendido(string nombre_archivo, int n){

    
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario y de lectura

    
    struct Venta prueba;
    // primero creemos un puntero para almacenar el id de todos los productos maximos por haber
    struct Producto *lista = new struct Producto[n]; // memoria dinamica
    int cantidad=0;

    while(archivo.read((char*)&prueba, sizeof(struct Venta))){
        // prueba tiene toda la info
        bool bandera=false;
        if(cantidad == 0){
            lista[cantidad].id = prueba.idProducto;
            lista[cantidad].cantidad = 1;
            cantidad++;
            continue; // esto termina el primer while
        };

        // llegas a este for si y solo si la cantidad es almenos 1
        for(int i=0; i< cantidad; i++){
            if(lista[i].id == prueba.idProducto){
                lista[i].cantidad++; // si el id de un producto se repite en la lista, aumenta su cantidad
                bandera=true; // si la bandera es true, significa que el while aumenta sin crear un nuevo id
                break;
            }
        }
        if(bandera) continue; 
        // como se agrego una unidad mas al id ya creado, entonces saltamos while
        
        // si llegas a este punto significa que el id del producto es nuevo, y necesita un espacio
        // nuevo en la lista
        lista[cantidad].id = prueba.idProducto;
        lista[cantidad].cantidad = 1;
        cantidad++; // este indice determinar la cantidad final o el indice maximo
        
    }

    // ya tengo todos los id de Productos y sus cantidades
    archivo.close();

    struct Producto masVendido;
    //supongamos que el producto mas vendido es el primero
    int indice=0;

    //vamos a recorrer todo el arreglo que hemos creado para encontrar el maximo
    for(int i=0; i<cantidad ; i++){
        if(lista[i].cantidad > lista[indice].cantidad){
            indice=i; // entonces el mayor es el nuevo i
        }
    }

    //ya tengo el indice de la cantidad maxima, solo falta reemplazar
    masVendido.id = lista[indice].id;
    masVendido.cantidad = lista[indice].cantidad;

    //y ahora ya tenemos el producto con mayor venta


    delete[] lista;
    return masVendido;
}

struct Venta *ventaSospechosa(string nombre_archivo, int n, int &cantidad){
    struct Venta *lista=new struct Venta[n];

    
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario y de lectura

    struct Venta prueba;
    while(archivo.read((char*)&prueba, sizeof(struct Venta))){
        // prueba ahora tiene al info
        if(prueba.cantidad > 100){

            // copiamos la info en la lista conforme vaya creciendo la cantidad
            lista[cantidad].idVenta = prueba.idVenta;
            lista[cantidad].idVendedor = prueba.idVendedor;
            lista[cantidad].idProducto = prueba.idProducto;
            lista[cantidad].cantidad = prueba.cantidad;
            lista[cantidad].precioUnitario = prueba.precioUnitario;

            // y la cantidad se va sumando
            cantidad++;
            
        }
    }
    archivo.close();

    //ahora que tenmos todas las ventas sospechosa, reducimos la lista hasta la cantidad calculada
    struct Venta *listaTotal = new struct Venta[cantidad]; // memoria dinamica para la cantidad total

    for(int i=0; i< cantidad; i++){
        listaTotal[i].idVenta = lista[i].idVenta;
        listaTotal[i].idVendedor = lista[i].idVendedor;
        listaTotal[i].idProducto = lista[i].idProducto;
        listaTotal[i].cantidad = lista[i].cantidad;
        listaTotal[i].precioUnitario = lista[i].precioUnitario;

    }



    delete[] lista;
    return listaTotal;
} 

void generarReporte(string nombre_reporte, int n, double monto,struct Venta vendedorMax,
                     struct Producto masVendido, struct Venta *lista_sus, int n_sus){

    fstream archivo; // objeto de lectura y escritura
    
    archivo.open(nombre_reporte, ios::out); // creamos el archivo
    archivo.close(); // desvinculamos

    archivo.open(nombre_reporte, ios::out | ios::in);
    // objeto en modo escritura y lectura

    archivo << "---REPORTE GENERAL DE VENTAS---\n";
    archivo << "\nTotal de registros: "<<n<< endl;
    archivo << "\nMONTO TOTAL VENDIDO: \n"<< monto << endl;
    archivo << "\n -------------------------------\n";
    archivo << "VENDEDOR CON MAYOR RECAUDACION: \n";
    archivo << "Id Vendedor: "<<vendedorMax.idVendedor << endl;
    archivo << "Total vendido: "<< double(vendedorMax.cantidad) * vendedorMax.precioUnitario << endl; 
    archivo << "\n -------------------------------\n";
    archivo << "PRODUCTO MAS VENDIDO:\n";
    archivo << "iD Producto: "<<masVendido.id << endl;
    archivo << "Total unidades: "<< masVendido.cantidad << endl;
    archivo << "\n -------------------------------\n";
    archivo << "VENTAS SOSPECHOSAS (cantidad > 100)\n";
    for(int i=0; i< n_sus; i++){
        archivo << "ID venta: "<<lista_sus[i].idVenta;
        archivo << " | Vendedor: "<< lista_sus[i].idVendedor;
        archivo << " | Producto: "<< lista_sus[i].idProducto;
        archivo << " | Cantidad: "<< lista_sus[i].cantidad <<endl;
    }




    archivo.close(); // desvinculamos


}


int main(){

    string nombre_archivo= "ventas.dat";
    int n = leerArchivo(nombre_archivo);

    double monto = montoTotal(nombre_archivo);

    cout << "\nVendedor con mayor recaudadcion:\n";
    double montoMax=0;
    struct Venta vendedorMax= ventaMaxima(nombre_archivo, montoMax);
    cout << "\nId vendedor: "<<vendedorMax.idVendedor << " | Monto recaudado: ";
    cout << montoMax << endl;

    struct Producto masVendido = productoMasVendido(nombre_archivo, n);

    cout << "\nProducto mas vendido:\n";
    cout << "\nID producto "<< masVendido.id;
    cout << " | Cantidad: "<< masVendido.cantidad << endl;

    int n_sus=0;
    struct Venta *lista_sus =  ventaSospechosa(nombre_archivo, n, n_sus);

    string nombre_reporte = "reporte.txt";
    generarReporte(nombre_reporte, n, monto, vendedorMax, masVendido, lista_sus, n_sus);
    



    delete[] lista_sus;
    return 0;
}