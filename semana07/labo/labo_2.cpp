#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;

struct Persona{ //72 bytes aprox
    string apellido;
    string nombre; 
    float nota1;
    float nota2;
};


//_______________________________________

int contarLineas(string nombre){
    int n=0;

    fstream archivo; // objeto para leer y escribir

    // por lo que se ve, siempre se lee en modo char[ ]
    archivo.open(nombre.c_str(), ios::in); // objeto solo para leer

    string linea;
    while(getline(archivo, linea)){ // lee cada linea que contenga al menos un caracter != ' '
        n++; // suma linea a linea
    }

    archivo.close();  // desvinculamos

    return n;
}

float transformar(string linea){
    float n=0; // numero a retornar
    float signo=1; // por si el numero es negativo

    int indice =-1; 
    int n_temp = strlen(linea.c_str()); // la cantidad de letras
    for(int i=0; i < n_temp; i++){ // leemos todas las letras hasta encontrar el primer numero
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
    //cout << "|" << linea[indice_max] << "|" << endl; // el indice_max apunta al ultimo digito

    string copia = linea.substr(indice, indice_max - indice +1); // subcadena para mejorar la cosa
    int n_copia=strlen(copia.c_str()); // cantidad de letras para la copia
    
    //cout << "|"<<copia << "|"<< endl; // si funciona
    //cout << n_copia << endl;

    int coma_pos = copia.find('.'); // para saber si es entero o flotante

    if(coma_pos == -1){
        // significa que es entero
        for(int i= 0; i< n_copia ; i++){ // recorre todos los caracteres de numeros '1230'
            float temp=1;
            for(int j = 0; j< n_copia -i -1; j++ ){ 
                temp = temp *10; // esto para llegar a la cantidad requerida 
            }
            n = n+ float((copia[i] - '0' ))*temp; // esta bien esto segun yo
            // n = 0 + 1* 1000 
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
            for(int j=0; j < n_copia -i -2 +salto; j++){ // cuantas veces?
                temp = temp *10; //
            }
            n = n + float((copia[i] - '0' )) *temp; // acumulando la suma '12234'
        }        
        float temp =1;
        for(int i=0; i< n_copia - coma_pos -1; i++){ // repite ' ' veces
            temp = temp *10;
        }
        n = n/temp;

    }

    
    n = n*signo;

    return n;
}


void almacenarInformacion(string nombre_archivo, struct Persona *&lista){
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo.c_str(), ios::in | ios::out); // objeto para leer y escribir

    int i=0;
    string linea;
    while(getline(archivo, linea)){
        // esto almacena la informacion de cada linea del archivo en un string linea
        // ahora vamos a desmenusar cada linea y agregarlo a un struct

        int n_linea=strlen(linea.c_str()); // cantidad de caracteres en una linea

        int indice_1=linea.find(','); //  indice que separa apellidos de nombres

        string apellido = linea.substr(0, (indice_1-1) -0 +1); // este string es el apellido con 

        lista[i].apellido = apellido; // como son string, los copio sin problemas

        
        
        int indice_2 =linea.find('-', indice_1+1) ; // indice que separa nombres de nota 1;

        string nombre = linea.substr(indice_1+1, (indice_2 -1 ) - (indice_1 +1) +1); 
        // este string es el nombre con

        lista[i].nombre = nombre; // como son string, los copio sin problemas

        

        int indice_3 = linea.find('-', indice_2+1); // indice que separa nota1 de nota2

        string nota1=linea.substr(indice_2+1, (indice_3-1) - (indice_2+1) +1 ); // este string es nota1
        
        float nota1_1 = transformar(nota1); // transformar a float

        lista[i].nota1=nota1_1; 


        string nota2=linea.substr(indice_3+1, (n_linea-1) - (indice_3+1) +1 );
        // el ultimo string es nota2

        float nota2_2 = transformar(nota2); // transformar a float

        lista[i].nota2=nota2_2;

        i++;
    }



    archivo.close();

}

void mostrarInformacion(struct Persona *lista, int n){
    cout << "Num ";
    cout << setw(20 -3) << "Apellido";
    cout << setw(20) << "Nombre";
    cout << setw(12) << "Nota1";
    cout << setw(12) << "Nota2";
    cout << setw(14) << "Promedio \n";
    for(int i=0; i <n ; i++){
        cout << i +1;
        cout << setw(20) <<lista[i].apellido ; 
        cout << setw(20) << lista[i].nombre;
        cout << setw(12)<< lista[i].nota1;
        cout << setw(12) << lista[i].nota2;
        cout << setw(14) << (lista[i].nota1 + lista[i].nota2) / 2 ;
        cout << endl;
    }
}

int main(){

    fstream archivo; // objeto para leer y escribir

    string nombre_archivo="baseUNI.txt";
    archivo.open("baseUNI.txt", ios::out | ios::in); // inicio para leer y escribir

    int n_archivo = contarLineas(nombre_archivo);
    string linea;

    struct Persona *lista = new struct Persona[n_archivo]; 
    // arreglo dinamico para las personas en el archivo

    almacenarInformacion(nombre_archivo, lista);

    mostrarInformacion(lista, n_archivo);





    archivo.close(); // desvinculo

    delete[] lista;
    
    return 0;
}