#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;




// _____________________________________________________



int main(){

    ofstream ventas; // creamos un puntero(objeto) para escribir archivos 
    ofstream prueba;

    ventas.open("ventas.txt"); // creamos un archivo ventas.txt y lo inicializamos con .open
    
    if(!ventas) cerr <<"Error al abrir el archivo \n"; //analiza si esto esta bien escrito
    // !ventas == ventas.fail() ,  'El flujo esta en buen estado?'

    int arreglo[7];

    for(int i=0; i< 7; i++){
        arreglo[i] = 100 + rand()%1001;  // del 100 al 1100
        ventas << arreglo[i]<< endl;
    }

    ventas << "--------------------------------\n";
    ventas << "Resumen: \n";

    // total de ventas
    int suma=0;
     for(int i=0; i< 7; i++){
      suma += arreglo[i];
    }

    ventas << "Total: "<< suma << endl;

    // promedio de ventas 
    float promedio;
    promedio = float(suma) / 7;
    ventas << "Promedio: "<< promedio << endl;

    //Mayor venta
    int i_max, i_min;
    i_max = 0;
    for(int i=0; i <7 ; i++){
        if(arreglo[i] > arreglo[i_max]) i_max = i;
    }
    ventas << "Mayor venta: "<< arreglo[i_max]<< endl;

    // Menor venta
    i_min=0;
    for(int i=0; i <7 ; i++){
        if(arreglo[i] < arreglo[i_min]) i_min = i;
    }
    ventas << "Menor venta: "<< arreglo[i_min]<<  endl;

    ventas.close();  // cerramos archivo


    // ahora nos toca leer el archivo con ifstream

    string palabra;

    ifstream p_leer; // se crea puntero(objeto) para leer 
    // archivo en modo lectura ios::in , por defecto
    
    p_leer.open("ventas.txt"); // apuntamos al archivo ventas.txt

    if(!p_leer) {
        cerr << "Error al abrir ventas.txt \n";
        return 1; //corta la funcion principal
    }

    while(getline(p_leer, palabra)){ // exactamente que hace esto?
        cout << palabra << endl;
    }

    p_leer.close(); // dejamos de apuntar al archivo ventas.txt
    for(int i=0; i< 20; i++){
        cout << "----";
    }
    cout << endl;
   
    /* vamos a escribir el archivo de una forma mas exacta
    ifstream p_leer1; // otro objeto para leer 

    p_leer1.open("ventas.txt"); // 

    char c;
    while (p_leer1.get(c)){
        cout << c; 
    }

    for(int i=0; i< 20; i++){
        cout << "----";
    }
    cout << endl;

    string palabra_1;
    while(p_leer1 >> palabra_1){
        cout << palabra_1;
    }

//    p_leer1.read((char*)&variable, sizeof(variable)); // esto es para binarios


    p_leer1.close(); // cerrando el objeto*/
    
    
    return 0;
}