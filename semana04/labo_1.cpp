#include <iostream>
#include <iomanip>

using namespace std;

int cantidadFrase(char *nombre){
    int contador=0; 
    for(char*p=nombre; *p!= '\0'; p++){
        contador++;
    }
    return contador; // conteo toda la frase
}

void copiar(char *recibe, char *entrega, int n){
    for(int i=0; i<n; i++){
        *(recibe +i)=*(entrega+i);  // *recibe tiene que ser igual o mas grande que *entrega
    }
}

void normalizar(char * nombre){
    char *p=nombre;
    int indice=0;
    while(*p!='\0'){ //recorrer el arreglo
        if(*p < 92 && *p > 64){  // pone en miyusculas todas las letras antes de los cambios
            *p = *p +32;
        }
        if(*p == ' '){ 
            
            while(*(p+indice) == ' '){
                indice++;
                
            }
            // *(p + indice) apunta a una letra o a '\0'
            swap(*p , *(p+indice));

            if(*p < 92 && *p > 64){ //pone en miyusculas todos los nombres cuando se dan los cambios 
            *p = *p +32;
            }
        }
        if(*p !='\0'){
            p++;
        }
        
    }
}

int conteoPalabras(char *nombre){
    char *p=nombre;
    int conteo=0;
    while(*p != '\0'){
        if( *p != ' ' && (p == nombre || *(p-1) == ' ')){
            // p apunta a la primera letra de cada palabra
            conteo++;
        }
        p++;
    }
    return conteo;
}

void copiarYPegar(char **lista, char *frase, int *cantidad){
    char *p=frase;
    int indice=0;
    while(*p != '\0'){ // p recorre toda la frase
        if( *p != ' ' && (p == frase || *(p-1) == ' ')){
            // p apunta a la primera letra de cada palabra

            //procedemos a contar cada palabra
            int conteo=0;
            for(char *p_temp = p; *p_temp != ' ' && *p_temp != '\0'; p_temp++){ 
                // contea las palabras 
                conteo++;
            }
            lista[indice] = new char[conteo+1]; //reservo la palabra y un '\0'
            cantidad[indice]=conteo;
            //procedo a copiar caracter a caracter
            int i=0;
            for(char *p_temp=p; *p_temp != '\0' && *p_temp != ' '; p_temp++){
                //copia hasta el primer ' ' o '\0'
                lista[indice][i]=*p_temp;
                i++;
                //copias la palabra sin '\0'
            }
            // lista[indice][i] apunta a la nada
            lista[indice][i]='\0';
            
            while(*p != ' ' && *p != '\0'){  //p avanza hasta ' '
                p++;
            }
            indice++;
            continue;   // para que no haga el p++ del final

            // tengo dudas sobre el if general y el p++
            
        }
        p++;
    }
}

void imprimirMatriz(char **lista, int n, int *cantidad){
    int indice=0;
    for(char **i= lista; i<lista +n; i++){
        for(char *j=*i; *j!= '\0'; j++){
            cout<< *j;
            
        }
        cout<< setw(30 - cantidad[indice]) << "cantidad : "<< cantidad[indice] << endl;
        indice++;
    }
}

void imprimir(char *nombre){
    for(char *p=nombre; *p !='\0'; p++){
        cout << *p;
    }
    cout << endl;
}

int main(){
    char *nombre= new char[100]; //palabra de prueba
    cout << "ingrese la frase que usted desee : ";
    cin.getline(nombre, 100);

    int cantidad= cantidadFrase(nombre);

    char *nombre_2= new char[cantidad]; //palabra exacta
 
    copiar(nombre_2, nombre, cantidad);
    

    int conteo= conteoPalabras(nombre_2);
    imprimir(nombre_2);
    cout<< conteo << endl;

    char **lista_palabra = new char*[conteo]; //reservo un puntero para cada palabra

    int cantidad_palabras[conteo];

    copiarYPegar(lista_palabra, nombre_2, cantidad_palabras);
    imprimirMatriz(lista_palabra, conteo, cantidad_palabras); 


    normalizar(nombre_2);  //si funciona, pero deja todos los ' ' al ultimo del arreglo char
    imprimir(nombre_2);

    for(int i=0; i< conteo; i++){
        delete[] lista_palabra[i];
    }
    delete[] lista_palabra;
    delete[] nombre_2;
    delete[] nombre;
    return 0;
}