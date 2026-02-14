#include <iostream>
using namespace std;

void imprimir(char *p){
    for(char *m=p; *m!= '\0'; m++){
        cout<<*m;
    }
    cout << endl;
}

int separarNumeros(char *texto, char *puntero[10]){
    char*p_texto=texto;
    int indice=0;
    while(*p_texto != '\0'){
        if(*p_texto!= ' ' && (p_texto==texto || *(p_texto-1) ==' ')){ //p apunta al primer elemento de cada numero char
            while(*p_texto!= ',' && *p_texto != '\0'){
                puntero[indice]=p_texto; //el primero numero char se guarda en puntero[0]
                indice++;
                p_texto++;
                while(*p_texto!= ',' && *p_texto!= '\0'){
                    p_texto++; //esto para los elementos como 11, 123, 12345 y los ultimos elementos ".., 2"
                }
                
            }   
            //p_texto apunta a ',' o a '\0'
            *p_texto='\0';
            p_texto++;
        } else {
            p_texto++;
        }
    }
    return indice;
}

void conversion(char *letra[10], int num[10], int n){
    for(int i=0; i<n; i++){
        char* p=letra[i]; //dudo si esta bien xd
        int numero=0;
        while(*p!= '\0'){
            numero++;
            p++;
        }
        
        if(numero ==1){
            num[i]= int(letra[i][0]) - 48;
        } else{
            int suma=0;
            for(int j=0; j<numero; j++){
                int elemento=int(letra[i][j]) -48;
                for(int m=j; m< numero-1; m++){
                    elemento=elemento *10; //cada digito segun su orden se multiplica por 10 n veces    
                }

                suma=suma+elemento; //elemento final
            }
            num[i]=suma; // traspase de elemento i

        }

    }
}

bool seEncuentra(int p_num[10],int n, int k){
    for(int i=0; i<n; i++){
        for(int j=0; j<n ; j++){
            if(i!=j){
                if(p_num[i]+p_num[j]==k){
                    return true;
                } 
            }
        }
    }
    return false;
}

int main(){
    char texto[15]={"1, 2, 4, 7, 11"}; //el primer elemento != ' ' y los demas elementos ', '
    char *p_texto=texto;

    char *p_numero[10]; //para separar el char
    int p_int[10]; //para convertir el char en int

    cout<<"Texto :   ";
    imprimir(p_texto);

    int k_1;
    cout<<"Ingrese un valor k: ";
    cin>>k_1;

    int n_numeros;
    n_numeros=separarNumeros(p_texto, p_numero); //p_texto se destruye y p_numero almacena los numeros char

    conversion(p_numero, p_int, n_numeros);

    bool respuesta=seEncuentra(p_int,n_numeros , k_1);

    if(respuesta){
        cout<<"SI existen dos numeros con suma : "<<k_1<<endl;
    } else{
        cout<<"NO existen dos nuneros con suma : "<<k_1<<endl;
    }
   
    return 0;
}
