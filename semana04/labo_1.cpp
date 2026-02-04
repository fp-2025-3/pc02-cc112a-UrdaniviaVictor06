#include <iostream>
using namespace std;

int cantidadFrase(char *nombre){
    int contador=1;  //considerando el ultimo elemento '\0' 
    for(char*p=nombre; *p!= '\0'; p++){
        contador++;
    }
    return contador;
}

void copiar(char *recibe, char *entrega, int n){
    for(int i=0; i<n; i++){
        *(recibe +i)=*(entrega+i);
    }
}

void normalizar(char * nombre){
    char *p=nombre;
    int indice=0;
    while(*p!='\0'){
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

void copiarYPegar(char **lista, char *frase){
    char *p=frase;
    int indice=0;
    while(*p != '\0'){
        if( *p != ' ' && (p == frase || *(p-1) == ' ')){
            // p apunta a la primera letra de cada palabra

            //procedemos a contar cada palabra
            int conteo=0;
            for(char *p_temp = p; *p_temp != ' ' ; p_temp++){
                conteo++;
            }
            lista[indice] = new char[conteo+1]; //reservo una cierta cantidad de chars

            //procedo a copiar caracter a caracter
            int i=0;
            for(char *p_temp=p; *p_temp != '\0'; p_temp++){  //copia hasta el primer ' '
                lista[indice][i]=*p_temp;
                i++;
            }
            // lista[indice][i] apunta a la nada
            lista[indice][i]='\0';
            indice ++;
            // tengo dudas sobre el if general y el p++
            
        }
        p++;
    }
}

void imprimirMatriz(char **lista, int n){
    for(char **i= lista; i<lista +n; i++){
        for(char *j=*i; *j!= '\0'; j++){
            cout<< *j;
        }
        cout<< endl;
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

    copiarYPegar(lista_palabra, nombre_2);
    imprimirMatriz(lista_palabra, conteo); 


    normalizar(nombre_2);  //si funciona, pero deja todos los ' ' al ultimo del arreglo char
    imprimir(nombre_2);

    for(int i=0; i< conteo; i++){
        delete[] lista[i];
    }
    delete[] lista;
    delete[] nombre_2;
    delete[] nombre;
    return 0;
}