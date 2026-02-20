#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int N=4;

struct producto { // 56 bytes ejemplo
    int id;                  // Identificador único
    char nombre[30];         // Nombre del producto
    double precio;           // Precio unitario
    int stock;               // Cantidad disponible
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
        cout << "Posicion: "<<p_leer.tellg() << " bytes" << endl;

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
        if(prueba.id == idBuscado){
            return archivo.tellg();
        }
    }

    archivo.close(); // desvinculamos
    return -1;
}

int main(){
    const char *nombre = {"inventario.dat"};

    registrarProducto(nombre);

    mostrarProductos(nombre);

    int posicion = buscarProductoPorID(nombre, 102);
    cout << posicion << endl;


    
    return 0;
}