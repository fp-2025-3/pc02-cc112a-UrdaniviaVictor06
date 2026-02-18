#include <iostream>
#include <iomanip>
#include <set>
using namespace std;


int separarPalabras(char *texto, char *palabras[30], int *indices){
    char*p_texto=texto;
    int x_indice=0;
    while(*p_texto != '\0'){
        if(*p_texto!= ' ' && (p_texto==texto || *(p_texto-1) ==' ')){ //p apunta al primer elemento de cada char
            while(*p_texto!= ' ' && *p_texto != '\0'){
                *(palabras + x_indice)=p_texto; //la primera palabra se pasa al array
                *(indices+x_indice)= p_texto - texto;
                x_indice++;
                p_texto++;
                while(*p_texto!= ' ' && *p_texto!= '\0'){
                    p_texto++; //esto recorre toda la palabra hasta ' '
                }
                
            }   
            //p_texto apunta a ' ' o a '\0'
            p_texto++;
        } else {
            p_texto++;
        }
    }
    return x_indice;
}

void ordenarAlfabeto(char *palabras[30], int n, int *indices){
    //primero ponemos todo a minusculas
    for(int i=0; i<n; i++){
        if( *(*(palabras +i)+0) < 'a'){
            *(*(palabras+i)+0) = *(*(palabras+i)+0) + 32;
        }
    }

    //metodo burbuja
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1; j++){
            if(*(*(palabras+j)+0) > *(*(palabras +j+1)+0)){
                //intercambio punteros e indices

                char *temp=*(palabras+j);
                *(palabras+j)=*(palabras+j+1);
                *(palabras +j+1)=temp;

                int x_temp=*(indices+j);
                *(indices+j)=*(indices +j+1);
                *(indices +j+1)=x_temp;
            }
        }
    }
}


int main(){
    char texto[]={"los punteros no se copian se referencian y se ordenan"};
    char *p_texto=texto; //ya ta xd

    char *palabras[30];
    int indices[30];
    int *p_indices=indices;

    int n_palabras=separarPalabras(p_texto, palabras, p_indices);
    //funciona correctemente hasta aqui

    ordenarAlfabeto(palabras, n_palabras, p_indices);


    for(int i=0; i<n_palabras; i++){
        int temp=0;
        for(char *p=*(palabras+i); *p != ' ' && *p!= '\0'; p++){
            cout<<*p;
            temp++;
        }
        cout<< setw(25-temp)<<" (posicion "<<*(indices+i)<<")";
        cout << endl; 
    }

    return 0;
}
