#include <iostream>
#include <fstream>

using namespace std;



// ______________________________________




int main(){

    int n_estudiantes;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> n_estudiantes;

    ofstream p_wri; // creo objeto para escribir

    p_wri.open("notas.txt"); // lo inicializamos con respecto a notas  LO ESTAMOS CREANDO N VECES

    int *notas = new int[n_estudiantes]; // arreglo de 10 numeros dinamico

    for(int i=0; i< n_estudiantes; i++){
        notas[i] = rand()%21; // del 0 al 20
        p_wri << notas[i]<< endl;
    }


    p_wri.close(); // desvinculamos objeto

    // porque puedo utilizar p_wri nuevamente? sin hacer cambio alguno y porque no p_leer funciona igual

    p_wri.open("Reporte.txt"); // inicializamos en Reporte.txt

    p_wri << "REPORTE GENERAL\n";
    for(int i=0; i< 15; i++) p_wri << "---";
    p_wri << endl;

    // total estudiantes
    p_wri << "Total estudiantes: "<< n_estudiantes<< endl;

    //promedio
    int suma=0;
    for(int i=0; i< n_estudiantes; i++) suma+= notas[i]; 

    float promedio = float(suma) / n_estudiantes;

    p_wri << "Promedio: "<< promedio << endl;

    // mayor y menor nota
    int i_max=0, i_min=0;
    for(int i=0; i< n_estudiantes; i++){
        if(notas[i] > notas[i_max]) i_max = i; // nota mas alta

        if(notas[i] < notas[i_min]) i_min = i; // nota mas baja
    }

    p_wri << "Notas mas alta: "<< notas[i_max]<< endl; // nota mayor 

    p_wri << "Nota mas baja: "<< notas[i_min]<< endl; // nota menor

    // vamos a contar aprobados y desaprobados
    int con_aprobados=0, con_desaprobados=0;

    for(int i=0; i< n_estudiantes; i++){
        if(notas[i] < 10){
            con_desaprobados ++;
        } else {
            con_aprobados ++;
        }
        
    }

    p_wri << "Aprobados: "<< con_aprobados << endl;
    p_wri << "Desaprobados: "<< con_desaprobados << endl;


    p_wri.close(); // desvinculamos

    // esto es adicional, leeamos el archivo reporte
    ifstream p_leer; // creamos un objeto para leer

    p_leer.open("Reporte.txt"); // lo inicializamos con reporte.txt

    char letra;

    while(p_leer.get(letra)){ // lee caracter por caracter
        cout << letra;
    }

    p_leer.close(); // desvinculamos



    // tarde o temprano tendre que crear archivos y no sobreescribir en ellos
    // plan, creo un archivo y luego agrego y agrego datos, sin crear de nuevo el archivo
    delete[] notas;
    return 0;
}