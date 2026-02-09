#include <iostream>

using namespace std;

const int N=30;

void leerDatos(char *lista[N], int *tiempo, int n){
    for(int i=0; i<n; i++){
        char *nombre = new char[30];
        cout<<"Nombre del corredor "<<i+1<<" : ";
        cin.getline(nombre, 30);
        

        //borrando la palabra hasta el primer ' '

        for(char *p =nombre; *(p) != '\0' ; p++){
            
            if(p == nombre){
                continue;
            }

            if( *p == ' ' && *(p-1) != ' '){ 
                /*p apunta al espacio despues de la ultima letra de 
                la primera palabra */
            
            *p ='\0';                        
            break;
            }
        }

        //traspase de nombre
        lista[i] = nombre;

        tiempo[i] =0;
        while(tiempo[i] <= 0){
            cout<< "Ingresa el tiempo del corredor (en segundos) : ";
            cin >> tiempo[i];
            cin.ignore(); //esto para no tener problemas con mi cin.getline
        }
        
        
    }
}

void ordenarPorTiempo(char *lista[N], int *tiempo, int n){
    //selection sort
    for(int i=0; i<n-1; i++){
        int minimo=tiempo[i];
        int indice=i; //el indice empieza con el for mayor
        for(int j=i; j<n; j++){
            if(tiempo[j] < minimo){
                minimo=tiempo[j];
                indice=j;
            }
        }
        swap(tiempo[i], tiempo[indice]);

        //swap con el nombre
        swap(lista[i], lista[indice]);
        

    }
}
void buscarNombre(char *buscar, char *lista[N], int *tiempo, int n){
    for(int i=0; i<n; i++){
        char *p1 = buscar;
        char *p2 = lista[i];

        // compararamos caracter por caracter
        while(*p1 != '\0' && *p2 != '\0' && *p1 == *p2){
            p1++;
            p2++;
        }

        // verificamos la igualdad
        if(*p1 == '\0' && *p2 == '\0'){
            cout << "\nCorredor encontrado\n";
            cout << "Posicion: " << i+1 << endl;
            cout << "Tiempo: " << tiempo[i] << " segundos"<< endl;
            return;
        }
    }

    cout << "\nCorredor no encontrado\n";
}


void imprimirDatosFinal(char *lista[N], int *tiempo, int n){
    for(int i=0; i<n; i++){
        cout<< i +1<< " "<<lista[i]<<" --- "<<tiempo[i]<<" \n";
    }
}

void imprimirDatos(char *lista[N], int *tiempo, int n){
    for(int i=0; i<n; i++){
        cout<<lista[i]<<" --- "<<tiempo[i]<<" \n";
    }
}

int main(){

    int n_atle;
    cout << "Ingrese la cantidad de corredores: ";
    cin>> n_atle;
    cin.ignore(100, '\n');

    char *lista[n_atle];
    //reservo una lista de n_atle punteros char
    int tiempo[n_atle];

    leerDatos(lista, tiempo, n_atle);
    /*
    imprimirDatos(lista, tiempo, n_atle);

    cout << " --------------------------------\n";
    */
    ordenarPorTiempo(lista, tiempo, n_atle);
    
    cout<< "\n RANKING FINAL\n";
    imprimirDatosFinal(lista, tiempo, n_atle);

    char *buscar= new char[30];
    cout << "Ingrese nombre a buscar: ";
    cin.getline(buscar, 30);

    buscarNombre(buscar, lista, tiempo, n_atle);


    for(int i=0; i<n_atle; i++){
        delete[] lista[i];
    }

    return 0;
}