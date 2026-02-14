#include <iostream>
using namespace std;

int cuenta_vocales(char *texto){
    char*p_texto=texto;
    int indice=0;
    while(*p_texto != '\0'){
        if(*p_texto!= ' ' && (p_texto==texto || *(p_texto-1) ==' ')){ //p apunta al primer elemento de cada numero char
            
            if(*p_texto =='a' || *p_texto == 'e' || *p_texto== 'i' || *p_texto =='o' || *p_texto == 'u'){
                indice++;
            } else if(*p_texto =='A' || *p_texto == 'E' || *p_texto== 'I' || *p_texto =='O' || *p_texto == 'U' ){
                indice++;
            }
            //muy largo mi codigo xd
            p_texto++;
        } else {
            p_texto++;
        }
    }
    return indice;
}


int main(){
    char texto[100]={"Esto es un ejemplo en C++ END "};
    char *p_texto=texto;

    int n= cuenta_vocales(p_texto);
    cout <<"texto: "<< p_texto <<endl;
    cout<<"Numero de palabras que comienza con vocal: "<< n <<endl;

    return 0;
}
