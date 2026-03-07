#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Alumno{
    string codigo;
    string nombre;
    float nota1;
    float nota2;
    float nota3;
};


// ______________________________________-

int leerArchivo(string nombre_archivo){
    fstream archivo; // objeto de lectura y escritura
    int n=0;
    archivo.open(nombre_archivo, ios::in); // inicio objeto en modo lectura

    string linea;
    while(getline(archivo, linea)){
        // linea tiene todas la info de cada linea del archivo
        cout << linea << endl;
        n++;
    }
    cout << "----------------------------------------------\n";

    archivo.close(); // desvinculamos
    return n;
}

float transformar(string linea){
    float n=0; // numero a retornar
    float signo=1; // por si el numero es negativo

    int indice =-1; 
    int n_temp = strlen(linea.c_str()); // la cantidad de letras
    for(int i=0; i < n_temp; i++){ // leemos todas las letras hasta encontrar el primer numero
        if(linea[i] != ' '){
            indice =i; 
            break;
        }
    }
    if(indice ==-1) return 0; //  el string no tiene numeros '  ' 
    if(linea[indice] == '-'){ 
        signo = -1;
        indice++;
    }  
    //  implica que es negativo

    int indice_max=n_temp-1; 
    for(int i=indice; i< n_temp; i++){ // recorre desde el primer numero hasta el espacio ' ' 
        if(linea[i] == ' '){  
            indice_max = i-1; 
            break;
        }
    }

    string copia = linea.substr(indice, indice_max - indice +1); // subcadena 
    int n_copia=strlen(copia.c_str()); // cantidad de letras para la copia

    int coma_pos = copia.find('.'); // para saber si es entero o flotante

    if(coma_pos == -1){
        // significa que es entero
        for(int i= 0; i< n_copia ; i++){ // recorre todos los caracteres de numeros '3452'
            float temp=1;
            for(int j = 0; j< n_copia -i -1; j++ ){ 
                temp = temp *10; // esto para llegar a la cantidad requerida 
            }
            n = n+ float((copia[i] - '0' ))*temp; 
            
        }
    
    } else {
        // significa que es flotante
        int salto=0;
        for(int i=0; i< n_copia; i++){ // recorre todo el string '12.234'
            if(i == coma_pos){
                salto = 1;
                continue;
            }
            float temp =1;
            for(int j=0; j < n_copia -i -2 +salto; j++){ 
                temp = temp *10; 
            }
            n = n + float((copia[i] - '0' )) *temp; // acumulando la suma '12412'
        }        
        float temp =1;
        for(int i=0; i< n_copia - coma_pos -1; i++){ // repite 
            temp = temp *10;
        }
        n = n/temp;

    }

    
    n = n*signo;

    return n;
}

void almacenarInformacion(string nombre_archivo, struct Alumno *&lista){
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::in); // objeto de lectura

    string linea;
    int i=0;
    while(getline(archivo, linea)){
        // almacena toda la info en linea

        int n_temp = strlen(linea.c_str()); // cantidad de linea => indice_max = n_temp -1

        int pos1=linea.find(' '); // busca el primer espacio
        string codigo = linea.substr(0, pos1 - 0 +1 ); // cadena que almacena el codigo
        lista[i].codigo = codigo;
        

        int pos2 = linea.find(' ', pos1+1); // busca el siguiente espacio despues del primer espacio
        string nombre = linea.substr(pos1 , (pos2 ) - (pos1 +1)  +1 );
        //  esta cadena almacena el nombre de cada alumno
        lista[i].nombre = nombre;

        int pos3 = linea.find(' ', pos2+1); // busca el siguiente espacio
        string nota1=linea.substr(pos2 +1, (pos3) -(pos2+1) +1); // esto tiene la nota1
        float nota1_1 = transformar(nota1);
        lista[i].nota1 = nota1_1; 

        int pos4 = linea.find(' ', pos3+1); // busca el siguiente espacio
        string nota2 = linea.substr(pos3+1, (pos4) -(pos3) -1); // este string es la nota2
        float nota2_2 = transformar(nota2); 
        lista[i].nota2 = nota2_2;

        // la nota final es por descarte
        string nota3 = linea.substr(pos4+1, (n_temp-1) - (pos4+1) +1); // este string es nota3
        float nota3_3 = transformar(nota3);
        lista[i].nota3 = nota3_3;         

        i++;
    }

    archivo.close();
}

void calcularPromedio(struct Alumno *lista, int n){
    // ahora calcularemos todos los promedios
    for(int i=0; i< n; i++){

        float promedio; 
        float suma =lista[i].nota1 + lista[i].nota2 + lista[i].nota3;
        promedio = suma/3;
        

        cout << "Nombre: "<< lista[i].nombre; 
        cout << " | Promedio: "<< fixed << setprecision(2) << promedio <<endl; 
    }
}

void leerAlumno(struct Alumno *lista, int n){
    cout << "--------------------------------\n";
    for(int i=0; i< n; i++){

        cout << lista[i].nombre << "|" << lista[i].codigo;
        cout << "|" << lista[i].nota1 << "|" << lista[i].nota2;
        cout << "|" << lista[i].nota3 << "|" <<endl;
    }
}

void generarReporte(string nombre_archivo, struct Alumno *lista, int n){
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::out); // crear archivo
    archivo.close(); // desvinculamos


    archivo.open(nombre_archivo, ios::out | ios::in); // objeto de lectura y escritura

    float promedioT=0;
    int indice_max=0; // suponemos que la nota maxima es el primero
    int indice_min =0;
    float promedioMin = 20;
    float promedioMax =0;


    for(int i=0; i < n; i++){
        float promedio; 
        float suma =lista[i].nota1 +lista[i].nota2 +lista[i].nota3;
        promedio = suma/3;
        promedioT=promedioT + promedio; // vas acumulando el promedio de la gente

        if(promedio > promedioMax){
            promedioMax = promedio;
            indice_max = i;
        } 

        if(promedio < promedioMin){
            promedioMin = promedio;
            indice_min = i;
        }

        string condicion;
        if(promedio >= 10){
            condicion = "APROBADO";
        } else{
            condicion= "DESAPROBADO";
        } 

        if(lista[i].nota1 < 5 || lista[i].nota2 < 5 || lista[i].nota3 < 5 ){
            condicion = "DESAPROBADO POR REGLA ACADEMICA";
        }


        archivo << lista[i].codigo << setw(10) << lista[i].nombre;
        archivo << setw(8) << fixed << setprecision(2) << promedio;
        archivo << setw(35) << condicion << endl;
    }

    promedioT= promedioT/float(n);

    archivo << "\nTotal de estudiantes : "<< n << endl;
    archivo << "Promedio general del curso: "<< promedioT << endl;
    archivo << "Promedio maxima: "<< lista[indice_max].nombre<< " = "<< promedioMax << endl;
    archivo << "Promedio minimo: " << lista[indice_min].nombre << " = "<< promedioMin << endl;


    archivo.close();
}

int main(){

    string nombre_archivo="notas.txt";
    int n= leerArchivo(nombre_archivo);

    struct Alumno *lista = new struct Alumno[n]; // memoria dinamica
    almacenarInformacion(nombre_archivo, lista);
    //leerAlumno(lista, n); // comprobante de que funciona mi funcion almacenarInformacion

    calcularPromedio(lista, n);

    string nombre_2 = "reporteAlumnos.txt";
    generarReporte(nombre_2, lista, n);


    delete[] lista;
    return 0;
}