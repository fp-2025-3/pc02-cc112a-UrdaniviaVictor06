#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;
int transformar(string linea){
    int n=0; // numero a retornar
    int signo=1; // por si el numero es negativo

    int indice =-1; 
    int n_temp = strlen(linea.c_str()); // la cantidad de letras
    for(int i=0; i < n_temp; i++){ // leemos todas las letras hasta encontrar '  1'
        if(linea[i] != ' '){
            indice =i; // guardamos la posicion
            break;
        }
    }
    if(indice ==-1) return 0; // si la posicion no existe, implica  que el string no tiene numeros '  ' 
    if(linea[indice] == '-'){
        signo = -1;
        indice++;
    }  
    // si el caracter que le sigue es un '-' implica que es negativo

    int indice_max=n_temp-1; //el indice maximo es una unidad menos que la cantida de letras 
    for(int i=indice; i< n_temp; i++){ // recorre desde el primer numero hasta el espacio ' ' 
        if(linea[i] == ' '){  
            indice_max = i-1; // indice es el inicio e indice_max es el final de los caracteres 
            break;
        }
    }


    for(int i= indice; i<= indice_max ; i++){ // recorre todos los caracteres de numeros '1230'
        int temp=1;
        for(int j = 0; j< indice_max -i ; j++ ){ 
            temp = temp *10; // esto para llegar a la cantidad requerida 
        }
        n = n+ (linea[i] - '0' )*temp; // esta bien esto segun yo
        // n = 0 + 1* 1000 
    }
    n = n*signo;

    return n;
}
int main(){

    fstream archivo1; // archivo leer y escribir para el texto 1
    fstream archivo2; // archivo leer y escribir para el texto 2
    fstream archivofinal; // archivo para leer y escribir el archivo final

    /* creamos el archivo final
    archivofinal.open("nombreM", ios::out); // crear archivo
    archivofinal.close(); */


    // inicializando archivos
    archivo1.open("archivo1.txt", ios::in | ios::out); // iniciado en lectura
    archivo2.open("archivo2.txt", ios::in | ios::out); // iniciado en lectura
    archivofinal.open("nombreM", ios::out | ios::in); // iniciado en escritura
   
    string linea;

    // bueno lo haremos con cadenas dinamicas de string
    // primero contamos las lineas

    int n_lineas1=0;
    while(getline(archivo1, linea)){
        n_lineas1++;
    }

    int n_lineas2=0;
    while(getline(archivo2, linea)){
        n_lineas2++;
    }

    archivo1.clear();
    archivo1.seekg(0);
    archivo2.clear();
    archivo2.seekg(0);
    

    // como ambos terminan en -1, no hacemos nada

    int *conjunto1 = new int[n_lineas1]; // memoria dinamica
    int *conjunto2 = new int[n_lineas2];
    
    string linea1;
    int indice1=0;
    while(getline(archivo1, linea1)){
        int temp = transformar(linea1); 
        if(temp == -1) break;
        conjunto1[indice1] = temp; // si temp ==-1, el elemento que le corresponde en conjunto es 0
        indice1++;
    }

    // ya tenemos la lista de enteros que estaba guardada en archivo1
    
    string linea2;
    indice1=0;
    while(getline(archivo2, linea2)){
        int temp = transformar(linea2);
        if(temp == -1) break;
        conjunto2[indice1] = temp;
        indice1++;
    }

    // y ahora tenemos la lista de enteros de archivo2

    indice1=0; 
    int indice2=0;
    while(indice1 != n_lineas1 -1 && indice2!= n_lineas2 -1){ 
        // escribo el (-1) porque el ultimo elemento de cada conjunto es un 0
        if(conjunto1[indice1] > conjunto2[indice2]){
            archivofinal << conjunto2[indice2]<< endl;
            indice2++; 
        } else {
            archivofinal << conjunto1[indice1] << endl;
            indice1++;
        }
        
    }

    // si sales de este while significa que un archivo ya fue copiado, solo nos queda el otro
    if(indice1 == n_lineas1-1){ // significa que archivo1 ya fue copiado
        while(indice2 != n_lineas2-1){
            archivofinal << conjunto2[indice2] << endl;
            indice2 ++;
        }
    } else { // si entras aca, significa que archivo1 aun tiene datos que ingresar
        while(indice1 != n_lineas1-1){
            archivofinal << conjunto1[indice1] << endl;
            indice1++;
        }
    }


    archivo1.close();
    archivo2.close();
    archivofinal.close();

    delete[] conjunto1;
    delete[] conjunto2;
    return 0;
}