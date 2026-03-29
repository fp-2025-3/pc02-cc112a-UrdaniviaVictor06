#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

void crear_archivo(char *nombre){

    string prueba1;
    string prueba2=string(nombre); // las funciones con (.) funcionan solo con su struct string

    int pos = prueba2.find('.');

    prueba1 = prueba2.substr(pos, 4); // se supone y deberia de soltar .dat .txt .md o algo asi
    cout << prueba1 << "|" << endl;

    
    if(prueba1 == string(".dat")) {
        fstream archivo; // vamos a crear un archivo para la bibliotecaVirtual

        archivo.open(nombre, ios::binary | ios::out); // esto creara la biblioteca

        archivo.close(); // desvincula el archivo

    }else {
        fstream archivo; // vamos a crear un archivo para la bibliotecaVirtual

        archivo.open(nombre, ios::out); // esto creara la biblioteca

        archivo.close(); // desvincula el archivo
    }
    

}

int main(){
   
    char nombre[40];
    cout << "Ingrese el nombre del archivo a crear (30 caracteres): ";
    cin.getline(nombre, 40);

    /* Dato importante, si hay espacios implica 
        'debe tener esta forma tu char' 

        si no hay espacios implica
        debe_ser_algo_asi  (o) algoAsi


    */

    crear_archivo(nombre);
    
    
    return 0;
}