#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;


struct proyecto{ // 64 bytes
    int id;
    char titulo[40];
    double presupuesto;
    int duracionMeses;
};


//_____________________


void crear_archivo(string nombre_archivo){
    fstream archivo; // objeto lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::out); 
    archivo.close(); // creamos un archivo binario
    
}

struct proyecto *agregar_proyectos(string nombre_archivo, int &n_final){
    int n=-1;
    while(n<=0){
        cout << "\nIngrese la cantidad de proyectos que desea ingresar: ";
        cin >>n;
    }

    n_final =n; // actualizamos la cantidad

    struct proyecto *lista = new struct proyecto[n](); // crea una lista de n proyectos todos en 0
    for(int i=0; i< n;i++){
        lista[i].presupuesto = -1;
        while(lista[i].presupuesto <=0){
            cout << "\nIngrese el presupuesto de su proyecto "<< i+1 << ": ";
            cin >>lista[i].presupuesto;
        } 
        //aseguramos que el dinero sea positivo

        int cantidad=i+1; // cantidad = cantidad temporal
        bool bandera1 = true;
        lista[i].id =-1;
        while(lista[i].id <= 0 || bandera1){
            bandera1 =false; // con esta linea, puedes salir del while si no se repite el id
            cout << "\nIngrese el id de su proyecto (no repetir): ";
            cin >>lista[i].id;

            for(int j=0; j <cantidad; j++){
                if(lista[j].id == lista[i].id){
                    if(i==j) continue; // no se cuenta el mismo

                    // si entras aqui se supone y se repite
                    cout << "\nse repite el id \n";
                    bandera1 = true;
                }
            }

        }
        // con esto aseguro que sea positivo y que no se repita el id

        cin.ignore();
        cout << " \nIngrese el titulo de su proyecto: ";
        cin.getline(lista[i].titulo, 40);
    
        lista[i].duracionMeses =-1;
        while(lista[i].duracionMeses <=0){
            cout << "\ningrese la duracion en meses de su proyecto: ";
            cin >> lista[i].duracionMeses;
        }

    }

    // llenamos el archivo en binario y descendiente con presupuesto

    fstream archivo; // objeto lectur ay escritura

    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in);
    // modo binario lectura y escritura

    for(int i=0; i< n; i++){
        int indice_max=i; // supongamos que es el mayor

        for(int j=i; j<n; j++){
            if(lista[j].presupuesto > lista[indice_max].presupuesto){
                // significa que hay uno mayor
                indice_max = j;
            }
        }

        //ya tenemos al mayor, ahora swap
        if(i == indice_max){
            ;
        } else {
            swap(lista[i].presupuesto, lista[indice_max].presupuesto);
            swap(lista[i].id, lista[indice_max].id);
            swap(lista[i].duracionMeses, lista[indice_max].duracionMeses);

            // swap con char
            char temp[40];
            strcpy(temp, lista[i].titulo);
            strcpy(lista[i].titulo, lista[indice_max].titulo);
            strcpy(lista[indice_max].titulo, temp);
        }
    }

    // ya tenemos la lista ordenada
    for(int i=0; i< n; i++){
        // la lista a ingresar es 
        archivo.write((char*)&lista[i], sizeof(struct proyecto));
        // copia la lista en bytes y mueve el puntero 
    }


    archivo.close();
    return lista;
}

struct proyecto *expandir(struct proyecto *lista, int &n, int k){
    struct proyecto *copia = new struct proyecto[n+k]; // memoria dinamica

    // vamos a copiar
    for(int i=0; i< n; i++){
        copia[i].presupuesto = lista[i].presupuesto;
        copia[i].id = lista[i].id;
        copia[i].duracionMeses = lista[i].duracionMeses;

        // ahora con el titulo
        strcpy(copia[i].titulo, lista[i].titulo);
    }
    n=n+k;

    delete[] lista;
    return copia;
}

void insertarProyecto(string nombre_archivo, int &n, struct proyecto *lista){
    struct proyecto prueba;

    cout << "\n Vamos a ingresar un proyecto nuevo\n";

    prueba.id = -1;
    bool bandera =true;
    while(prueba.id <=0 || bandera){
        bandera = false; // ya puedes salir

        cout << "Ingrese un id para su proyecto (sin repetir): ";
        cin >> prueba.id;

        for(int i=0; i<n; i++){
            if(lista[i].id == prueba.id){
                // significa que se repite el id
                cout << "se repite el id\n";
                bandera = true;
            }
        }
    }

    prueba.presupuesto = -1;
    while(prueba.presupuesto <=0){
        cout << "\nIngrese el presupuesto de su proyecto: ";
        cin >> prueba.presupuesto;
    }

    cin.ignore();
    cout << "\nIngrese el titulo de su proyecto : ";
    cin.getline(prueba.titulo, 40); 

    prueba.duracionMeses = -1;
    while(prueba.duracionMeses <=0){
        cout << "\nIngrese la duracion en meses de su proyecto: ";
        cin >>prueba.duracionMeses;
    }


    // ahora tenemos que insertar el proyecto
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::app);
    // modo bianrio y agregar algo
    archivo.write((char*)&prueba, sizeof(struct proyecto));
    // insertamos un espacio en el binario para poder ordenarlo


    archivo.close(); 

    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in); 
    // modo binario

    struct proyecto copia;
    while( archivo.read((char*)&copia, sizeof(struct proyecto)) ){
        //copia tiene toda la infor ahora

        if(copia.presupuesto < prueba.presupuesto){
            //significa que prueba entra donde copia y mueve todo un espacio a la derecha
            
            int posicion = archivo.tellg();
            posicion = posicion - sizeof(struct proyecto);
            
            archivo.seekp(posicion);
            archivo.seekg(posicion); 

            archivo.write((char*)&prueba, sizeof(struct proyecto));

            // ahora pasamos copia a prueba
            prueba.id = copia.id;
            prueba.duracionMeses = copia.duracionMeses;
            prueba.presupuesto = copia.presupuesto;

            strcpy(prueba.titulo, copia.titulo); 
            // con esto prueba tiene toda la info de copia
        }

        // si sales de este bucle la posicion de los punteros no se modifica para nada
    }





    archivo.close();

}

void mostrar_proyectos(string nombre_archivo){
    fstream archivo; // objeto lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in); 
    // modo binario lectura y escritura

    struct proyecto prueba;
    while(archivo.read((char*)&prueba, sizeof(struct proyecto))){
        // prueba tiene toda la info

        cout << "\nID: "<<prueba.id << " | Titulo: "<<prueba.titulo<< endl;
        cout << "Presupuesto: "<<prueba.presupuesto << " | Duracion (meses) : ";
        cout << prueba.duracionMeses << endl;
        cout << "------------------------------------\n";

    }

    archivo.close(); 
}

int main(){

    string nombre_archivo = "proyectos.dat";

    crear_archivo(nombre_archivo);

    int n;
    struct proyecto *lista = agregar_proyectos(nombre_archivo, n);

    mostrar_proyectos(nombre_archivo);

    insertarProyecto(nombre_archivo,n,lista);

    mostrar_proyectos(nombre_archivo); // vamos a probar mi caso hipotetico


    delete[] lista;
    return 0;
}