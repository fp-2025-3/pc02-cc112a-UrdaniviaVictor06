#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Empleado{ // 48 bytes
    int id;
    char nombre[30];
    double salario;
};




//____________________________________

int leerArchivo(string nombre_archivo){
    fstream archivo; // objeto de lectura y escritura
    int n=0; // cantidad de datos


    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario con lectura

    struct Empleado prueba;

    while(archivo.read((char*)&prueba, sizeof(struct Empleado))){
        // ahora prueba tiene toda la informacion de cada estructura del archivo
        //cout << prueba.id << "|"<< prueba.nombre << "|" << prueba.salario << endl;
        n++;
    }


    archivo.close(); // desvinculamos
    return n;
}

int buscarPorID(string nombre_archivo, int idBuscado, int n){
    int bytes = sizeof(struct Empleado);  
    /* como el archivo es binario y esta lleno de struct iguales, entonces
    // cada dato se encuentra separado por bytes| bytes |bytes ...
    // tambien, como cada id es un numero consecutivo del 1 al 20 , entocnes podemos buscar
    cualquiera dato de un empleado sabiendo solo su id
    siendo su posicion en el archivo calculado como (id-1)*bytes */

    int posicion = (idBuscado -1) * bytes; // posicion exacta del id buscado (en bytes)

    fstream archivo; // objeto de lectura y escritura

    if(idBuscado <1 || idBuscado >20){
        cout << "\n--- DATOS DEL EMPLEADO --- \n";
        cout << "Empleado no encontrado \n";
        return -1;
    }

    archivo.open(nombre_archivo, ios::binary |  ios::in); // modo binario y de lectura

    archivo.seekg(posicion); // puntero leer apunta a nuestra direccion

    struct Empleado prueba;
    archivo.read((char*)&prueba, sizeof(struct Empleado)); // prueba ahora tiene la info 

    cout << "\n--- DATOS DEL EMPLEADO ---\n";
    cout << "ID: "  <<prueba.id  << endl;
    cout <<  "Nombre: " << prueba.nombre << endl;
    cout << "Salario: "  << prueba.salario << endl;


    archivo.close(); // desvincualmos
    return posicion;
}


void modificarSalario(string nombre_archivo, double salarioNuevo, int pos){
    fstream archivo; // archivo de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::in | ios::out); 
    // modo binario, de lectura y de escritura

    archivo.seekg(pos);
    archivo.seekp(pos); // mueve el p_leer y p_escribir a la posicion querida

    struct Empleado prueba;
    archivo.read((char*)&prueba, sizeof(struct Empleado)); // prueba tiene la info

    prueba.salario = salarioNuevo;

    cout << "\nSalario actualizado correctamente\n";

    archivo.seekg(pos);
    archivo.seekp(pos); // mueve el p_leer y p_escribir a la posicion querida

    archivo.write((char*)&prueba, sizeof(struct Empleado)); // modifica el archivo 


    archivo.close(); // desvinculamos
}

int main(){

    string nombre_archivo = "empleados.dat";

    int n = leerArchivo(nombre_archivo);

    int idBuscado=-1;
    cout << "Ingrese el id del empleado: ";
    cin >> idBuscado;

    int pos = buscarPorID(nombre_archivo, idBuscado, n);

    if(pos ==-1) return 0;


    double nuevoSalario =-1;
    while(nuevoSalario <=0){
        cout << "Ingrese nuevo salario: ";
        cin >> nuevoSalario;
    }

    modificarSalario(nombre_archivo, nuevoSalario, pos);




    return 0;
}