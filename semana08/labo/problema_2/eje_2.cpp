#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct CuentaBancaria { // 64 bytes
    int numeroCuenta;
    char titular[40];
    double saldo;
    bool activo;
};

//____________________________

void crear_archivo(string nombre_archivo){
    fstream archivo; // objeto para leer y escribir

    // creamos un archivo binario
    archivo.open(nombre_archivo, ios::binary | ios::out ); 
    archivo.close(); 

}

void agregarCuentas(string nombre_archivo, int &n){
    fstream archivo; // objeto de lectura y escritura
    int n_total=-1;
    while(n_total <=0){
        cout << "\nIngrese la cantidad de elementos de su archivo: ";
        cin >> n_total;
    }

    //vamos a almacenar todo en una lista, luego la ordenamos y colocamos en el archivo
    struct CuentaBancaria *lista = new struct CuentaBancaria[n_total]; 
    // guardamos memoria
   
    int cantidad=1;
    for(int i=0; i<n_total; i++){
        lista[i].numeroCuenta=-1;

        bool bandera = true;

        while(lista[i].numeroCuenta <= 0 || bandera){ // verdadero y verdadero
            bandera = false;

            cout << "\nIngrese un numero de cuenta (mayor que 0 y diferente al anterior): ";
            cin >>lista[i].numeroCuenta;
            
            //como sé si se repite?
            for(int j=0; j< cantidad; j++){
                if(i == j) continue; // si i = j , entonces si o si son iguales, no cuenta

                if(lista[i].numeroCuenta == lista[j].numeroCuenta){
                    // si entras aqui es por que se repite el numero de cuenta
                    bandera = true;
                }
            }

            // V y V / V y F / F y V / F y F , si se cumple la ultima condicion, entonces se avanza
        }
        // con esto aseguro que mi numero de cuenta sea positivo

        cantidad++;
            char nombre[40];
            cout << "\nIngrese el titular de su cuenta: ";
            cin.ignore();
            cin.getline(nombre, 40);
            // copiamos la info
            strcpy(lista[i].titular, nombre); // copiamos

            double saldo_new=-1;
            while(saldo_new <= 0){
                cout << "\nIngrese su saldo: ";
                cin >> saldo_new;
            }
            // aseguro que sea positivo
            lista[i].saldo = saldo_new; //copiamos

            lista[i].activo = true; // todos estan activos
    }
    n = n_total;
    // ingresamos cada info en un orden especifico
    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in);// modo binario, lectura y escritura 
    
    for(int i=0; i< n_total; i++){
        int posicion = sizeof(struct CuentaBancaria) * ( lista[i].numeroCuenta-1);
        archivo.seekg(posicion);
        archivo.seekp(posicion); 
        /* con esto hacemos que la posicion de cada cuenta bancaria este relacionado con su 
        id, es decir
        si tu id = 4, tu posicion es (4-1)* 64bytes */

        
        archivo.write((char*)&lista[i], sizeof(struct CuentaBancaria)); 
        //copiamos la info con su orden respectivo
    }
    archivo.close(); // desvinculamos 
    delete[] lista;
}

void mostrarArchivo(string nombre_archivo){
    cout << "\n\n";
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario y de lectura

    struct CuentaBancaria prueba;
    while(archivo.read((char*)&prueba, sizeof(struct CuentaBancaria))){
        // pruebta tiene la info
        cout << "---------\n";
        cout << prueba.numeroCuenta<< " | ";
        cout << prueba.saldo << " | ";
        cout << prueba.titular;
        if(prueba.activo){
            cout << " | Activo\n";
        } else {
            cout << " | Inactivo\n";
        }
    }

    archivo.close(); 
}

int buscarPorId(string nombre_archivo){ // retorna la posicion
    cout << "\n\n";

    int id=-1;
    while(id <=0){
        cout << "\nIngrese el numero de cuenta que desea buscar ";
        cin >> id;
    }

    int posicion = (id -1) * sizeof(struct CuentaBancaria);
    // buscamos la posicion del archivo usando su id

    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in);
    // modo bianrio de lectura y escritura

    archivo.seekp(posicion);
    archivo.seekg(posicion);
    // los punteros se mueven a la posicion buscada

    //leemos la estructura
    struct CuentaBancaria prueba;

    archivo.read((char*)&prueba, sizeof(struct CuentaBancaria));
    // ahora la info la tiene prueba
    cout << "\nID: "<<prueba.numeroCuenta;
    cout << " | Titular: "<< prueba.titular;
    cout << " | Saldo: " << prueba.saldo;
    if(prueba.activo){
        cout << " | Estado: activado \n";
    } else {
        cout << " | Estado: desactivado \n";
    }


    archivo.close(); // desvinculamos
    return posicion;
}

void modificarSaldo(string nombre_archivo){
    cout << "\n\n";
    fstream archivo; // obbjeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in);
    // modo bianrio, lectura y escritura

    int posicion = buscarPorId(nombre_archivo);

    archivo.seekp(posicion);
    archivo.seekg(posicion);
    // ya tenemos la posicion para leer la cuenta

    struct CuentaBancaria prueba;
    archivo.read((char*)&prueba, sizeof(struct CuentaBancaria));
    // prueba tiene toda la info

    int respuesta=-1; // respuesta por si la cuenta esta activa

    if(prueba.activo){
        
        while(respuesta != 1 && respuesta != 0){
            cout << "\ndepositar = 1, retirar = 0\nDesea retirar o depositar dinero en su cuenta?: ";
            cin >> respuesta;
        }

    } else{
        cout << "\nSu cuenta no esta activa, no se puede operar\n";
        return ; // termina la funcion
    }


    double saldo_mod=-1;
    if(respuesta == 1){
        // significa que vas a depositar
        while(saldo_mod <0){
            cout << "\nIngrese el saldo a depositar: ";
            cin >> saldo_mod;
        }
    } else {
        //significa que vas a retirar un saldo menor al que tienes
        while(saldo_mod < 0 || saldo_mod > prueba.saldo){
            cout << "\nIngrese el saldo a retirar: ";
            cin >>saldo_mod;
        }
        saldo_mod = saldo_mod *(-1);
    }

    // modificamos el saldo
    prueba.saldo = prueba.saldo + saldo_mod;

    archivo.seekp(posicion);
    archivo.seekg(posicion);
    // ya tenemos la posicion para escribir la cuenta

    archivo.write((char*)&prueba, sizeof(struct CuentaBancaria));

    archivo.close(); // desvinculamos
}

void desactivarCuenta(string nombre_archivo){
    cout << "\n\n";
    fstream archivo; // objeto de lectura y escritura


    archivo.open(nombre_archivo, ios::binary | ios::out | ios::in);
    //modo binario de elctura y escritura

    int posicion = buscarPorId(nombre_archivo);
    
    archivo.seekp(posicion);
    archivo.seekg(posicion);
    // ya tenemos la posicion para escribir la cuenta

    struct CuentaBancaria prueba;
    archivo.read((char*)&prueba, sizeof(struct CuentaBancaria));

    int respuesta =-1;
    while(respuesta != 1 && respuesta != 0){
        cout << "\nActivar = 1, Desactivar = 0\nDesea activar o desactivar su cuenta?: ";
        cin >> respuesta;
    }

    if(respuesta ==1){
        // vamos a activar
        prueba.activo = true;
    } else {
        // vamos a desactivar
        prueba.activo =false;
    }

    
    archivo.seekp(posicion);
    archivo.seekg(posicion);
    // ya tenemos la posicion para escribir la cuenta

    archivo.write((char*)&prueba, sizeof(struct CuentaBancaria));


    archivo.close(); //desvincular
}

void mostrarActivos(string nombre_archivo){
    cout << "\n\n";
    fstream archivo; // objeto de lectura y escritura

    archivo.open(nombre_archivo, ios::binary | ios::in); // modo binario y de lectura

    struct CuentaBancaria prueba;
    while(archivo.read((char*)&prueba, sizeof(struct CuentaBancaria))){
        // pruebta tiene la info
        if(prueba.activo){
            cout << "---------\n";
            cout << prueba.numeroCuenta<< " | ";
            cout << prueba.saldo << " | ";
            cout << prueba.titular;
            cout << " | Activo\n";
        }
        
    }

    archivo.close(); 
}

int main(){

    string nombre_archivo = "cuentas.dat"; 
    //crear_archivo(nombre_archivo); // en modo binario
    
    int n_archivo;
    //agregarCuentas(nombre_archivo, n_archivo);

    mostrarArchivo(nombre_archivo);

    //int posicion = buscarPorId(nombre_archivo);

    //modificarSaldo(nombre_archivo);
    
    desactivarCuenta(nombre_archivo);

    mostrarActivos(nombre_archivo);

    
    return 0;
}