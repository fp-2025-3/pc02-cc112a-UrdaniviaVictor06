#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int N=4;

struct producto { // 56 bytes ejemplo
    int id;                  // Identificador único 4 bytes
    char nombre[30];         // Nombre del producto 
    double precio;           // Precio unitario 8 bytes
    int stock;               // Cantidad disponible 4 bytes
    bool activo;             // true = activo, false = eliminado lógicamente
};


// ______________________________________________

void registrarProducto(const char* nombreArchivo){

    // esta funcion especificamente no se que hace
    // pero yo la usare para rellenar por completo mi inventario.dat
    ofstream p_escribir; // creamos un objeto para escribir

    p_escribir.open(nombreArchivo, ios::out | ios::binary); 
    // iniciamos el objeto con nombreArchivo en modo binario 

    struct producto nuevo[N]; // usaremos n archivos no dinamico

    for(int i=0; i< N; i++){
        nuevo[i].id = 100 +i;
        nuevo[i].stock = rand()&21; // del 0 a al 20 
        nuevo[i].activo =  rand()%2; // del 0(false) al 1(true)
        int tem_1= rand()%100; // del 0 al 99
        int tem_2 = rand()%50; // del 0 al 49

        nuevo[i].precio = ( double(tem_1) +double(tem_2) *100 )/100 ;
    }

    char manolo[30]="Maria";
    strcpy(nuevo[0].nombre , manolo);
    strcpy(nuevo[1].nombre , "Perla");
    strcpy(nuevo[2].nombre , "Fernandez");
    strcpy(nuevo[3].nombre , "Jose");

    for(int i=0; i<N; i++){
        // para este punto ya tenemos 4 estructuras creadas, ahora las pasaremos en binario al archivo
        p_escribir.write((char*)&nuevo[i] , sizeof(struct producto)); // variable tipo de dato
        //p_escribir.read( (char*)&nuevo[i], sizeof(struct producto)); // numero, int
    }
    p_escribir.close(); // desvinculamos

   // esta funcion solo escribe
}

void mostrarProductos(const char* nombreArchivo){
    ifstream p_leer; // creamos objeto de lectura
    p_leer.open(nombreArchivo, ios::binary); 
    // inicializamos el objeto con nombreArchivo en modo binario


    struct producto prueba; // creamos un tipo de dato donde almacenar los tipos de datos escritos
    while(p_leer.read((char*)&prueba, sizeof(struct producto))){
        cout << "ID: " << prueba.id<< endl; 
        cout << "Nombre: "<< prueba.nombre << endl;        
        cout << "Precio: "<< prueba.precio << endl;         
        cout << "Stock: "<< prueba.stock << endl;             
        if(prueba.activo){
            cout << "Modo: activo\n";
        } else {
            cout << "Modo: inactivo\n";
        }

        // probemos la funcion tellg();
        int posicion = p_leer.tellg(); // dime la posicion siguiente a la actual
        posicion = posicion - sizeof(struct producto);
        cout << "Posicion: "<< posicion << " bytes" << endl;

        cout << "----------------\n";
    }

    p_leer.close();
    //esta funcion solo lee
}

int buscarProductoPorID(const char* nombreArchivo, int idBuscado){
    // empezaremos a usar fstream
    fstream archivo;  // creamos un objeto de lectura y escritura

    archivo.open(nombreArchivo, ios::binary | ios::in); 
    //inicializamos en modo binario con lectura  en ese orden

    struct producto prueba; // creamos un tipo de dato igual al que usamos en el archivo 
    
    //                                      56  
    while(archivo.read((char*)&prueba, sizeof(struct producto))){  
        // esto recorre el archivo (tome en cuenta que el archivo esta lleno de structs del mismo
        // tipo)

        // el struct prueba pasa de struct en struct en todo  el archivo
        if(prueba.id == idBuscado){
            int posicion = archivo.tellg();
            posicion = posicion - sizeof(struct producto);
            return posicion;
        }
    }

    archivo.close(); // desvinculamos
    return -1;
}

void modificarPrecio(const char* nombreArchivo, int id, double nuevoPrecio){
    fstream archivo; // creo objeto para escribir y leer

    // ahora que lo pienso, porque al entrar con ios::out el archivo no se reescribe?
    // osea si el archivo existe, solo lo abre?
    archivo.open(nombreArchivo, ios::binary | ios::in | ios::out ); 
    // inicio archivo en modo binario con lectura y escritura

    // como mi archivo esta lleno de structs del mismo tipo, puedo recorrerlo de la siguiente forma
    struct producto prueba;
    int posicion; 
//    archivo.tellp(-sizeof(struct producto), ios::cur);
    while(archivo.read((char*)&prueba, sizeof(struct producto))){
        // este while pasa de struct en struct igualando prueba a cada struct
        /* prueba == producto[0]        posicion -> 0
        prueba == producto[1]           posicion -> 1
        prueba == producto[2]           posicion -> 2
        ...
        */
        
        if(prueba.id == id){ 
            posicion = archivo.tellg(); 
            /* como read pone a ambos punteros( de fstream) en la misma posicion, da un poco igual
            si uso tellp() o tellg() */ 
            posicion -= sizeof(struct producto); 
            break;
        }
    }

    // despues de esta funcion, prueba apunta a 102 y archivo apunta a 103 



    // prueba apunta al producto buscado por su id, y posicion(en bytes) apunta a su posicion xd
    prueba.precio = nuevoPrecio; // modificamos prueba

    // ya tengo la posicion, ahora a modificarlo
    archivo.seekp(posicion); // dirijo el puntero escribir a la posicion del cambio
    archivo.write((char*)&prueba, sizeof(struct producto));
    // que pasa si ingreso una struct diferente  

    archivo.close(); // desvinculamos, ahorita explico lo que hace lo anterior

}

void eliminarProducto(const char* nombreArchivo, int id){
    // voy a ir al id especifico y desactivare su producto (false)

    int posicion = buscarProductoPorID(nombreArchivo, id); // posicion en bytes
    // no olvidar que tengo mi archivo entero de struct iguales

    fstream archivo; // creo objeto de lectura y escritura

    archivo.open(nombreArchivo, ios::binary | ios::in | ios::out); 
    // inicio el objeto en modo binario , modo lectura y modo escritura en ese orden

    archivo.seekp(posicion); // puntero escritura apunta a direccion
    archivo.seekg(posicion);  // puntero lectura apunta a direccion

    struct producto prueba;

    archivo.read((char*)&prueba, sizeof(struct producto)); 
    /* Se supone y esto lee la estructura (struct producto) de la posicion .seekg() y la 
    "copia" en prueba (que tambien es struct producto) 
    Tambien */

    prueba.activo = false; // hago el cambio y ahora reemplazo

    // no olvides que despues de usar read o write, el puntero leer y escribir, aumentan su 
    // posicion en una estructura

    /* Es necesario entonces volver a apuntar los puntero en la posicion */
    archivo.seekp(posicion); // puntero escritura apunta a direccion
    archivo.seekg(posicion);  // puntero lectura apunta a direccion

    archivo.write((char*)&prueba, sizeof(struct producto)); 
    /* Esto reemplaza la estructura de la posicion .seekp() por la variable prueba de un tamaño
    en bytes de sizeof(struct producto) */

    archivo.close(); // cerrando el archivo 

}

double calcularValorInventario(const char* nombreArchivo){
    // solo suma los activos

    double total=0;
    fstream archivo; // creo objeto de lectura y escritura

    archivo.open(nombreArchivo, ios::binary | ios::in | ios:: out); 
    // me olvide inicializar, modo binario, lectura y escritura

    // el puntero leer y escribir estan en 0
    struct producto prueba;
    while(archivo.read((char*)&prueba, sizeof(struct producto)) ){
        // ahora prueba tiene la info de la struct que apunta el puntero
        if(prueba.activo){
            total += double(prueba.stock) * prueba.precio;
        }
    }

    archivo.close(); // cerando ciclos xd
    return total;
}


int main(){
    const char *nombre = {"inventario.dat"};

    registrarProducto(nombre); 
    /* como tu eres el primer binary | out , entonces tu funcion es crear y escribir el archivo
    los demas binary | out se encargan de escribir no mas */

    //mostrarProductos(nombre);

    int posicion = buscarProductoPorID(nombre, 102);
    cout <<  "Posicion prueba: " << posicion << " bytes" << endl;
    // vamos a editar en dicha posicion (en bytes)

    double precioNuevo=34;

    // modificar y busqueda por id (no por posicion)
    modificarPrecio(nombre, 102, precioNuevo);

    eliminarProducto(nombre, 102);

    double total = calcularValorInventario(nombre);
    cout << "Precio total: " << total << endl;

    mostrarProductos(nombre);


    return 0;
}