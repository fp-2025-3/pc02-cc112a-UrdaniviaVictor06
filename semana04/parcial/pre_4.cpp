#include <iostream>
using namespace std;
 
int * expandirCod( int *array, int n, int k){ //xpande k espacios a mi arreglo de n elementos
    int *copia = new int[n+k]; //arreglo de n+k elementos

    for(int i=0; i<n; i++){ //copia los primeros n elementos
        copia[i]= array[i];
    }

    delete[] array;
    return copia;
}

float * expandirPro( float *promedio, int n, int k){ //xpande k espacios a mi arreglo de n elementos
    float *copia = new float[n+k]; //arreglo de n+k elementos

    for(int i=0; i<n; i++){ //copia los primeros n elementos
        copia[i]= promedio[i];
    }

    delete[] promedio;
    return copia;
}

int * contraerCod( int *array, int n, int k){ //contrae k espacios a mi arreglo de n elementos
    int *copia = new int[n-k]; //arreglo de n-k elementos

    for(int i=0; i<n-k; i++){ //copia los primeros n-k elementos
        copia[i]= array[i];
    }

    delete[] array;
    return copia;
}

float * contraerPro( float *array, int n, int k){ //contrae k espacios a mi arreglo de n elementos
    float *copia = new float[n-k]; //arreglo de n-k elementos

    for(int i=0; i<n-k; i++){ //copia los primeros n-k elementos
        copia[i]= array[i];
    }

    delete[] array;
    return copia;
}

void AgregarEstudiante(int *&codigo, float *&promedio, int *n, int *indice){
    
    int res=2;
    while(res != 0 && res != 1){
        cout<< "Desea agregar un estudiante? (1=si, 0=no): ";
        cin >>res;
    }

   
    if( res ==1){
        if(*indice==  *n ){
            codigo = expandirCod(codigo, *n, *n);
            promedio= expandirPro(promedio, *n, *n);
            *n = *n *2;
        }

        codigo[*indice] = 100;
        while(codigo[*indice] <101 || codigo[*indice] > 199){
            cout << "Ingrese el codigo (101 a 199) :";
            cin >> codigo[*indice];
        }

        promedio[*indice] =-1;
        while(promedio[*indice] <0 || promedio[*indice] > 20){
            cout<<"Ingrese el promedio (0 a 20) : ";
            cin >> promedio[*indice];
        }
        (*indice)++;
        AgregarEstudiante(codigo, promedio, n, indice);

    } else {
        cout<<"okey\n";
    }
}

void EliminarDesaprobados(int *&codigo, float *&promedio, int *indice){
    //muevo todos los promedios menores que 10 al final
    for(int i=0; i<(*indice) +1; i++ ){
        
        for(int j=i; j< (*indice) +1-1; j++){
            if(promedio[j]  < 10){
                
                swap(promedio[j], promedio[j+1]);
                swap(codigo[j], codigo[j+1]);
            }
        }
    }

    //cuento todos los desaprobados
    int conteo=0;
    for(int i=0; i<(*indice)+1; i++ ){
        if(promedio[i] <10) conteo++;
    }

    int n= (*indice) +1;
    codigo=contraerCod(codigo, n, conteo);
    promedio= contraerPro(promedio, n, conteo);
    *indice = n - conteo; 
}

void imprimirEstudiantes(int *codigo, float *promedio, int *n){
    
    cout << "Estudiantes registrados \n";
    for(int i=0; i< *n; i++){
        cout << "Codigo : "<<codigo[i]<<"  Promedio: "<<promedio[i]<<endl;
    }
}

void imprimirDesaprobados(int *codigo, float *promedio, int *n){
    
    cout << "Estudiantes aprobados \n";
    for(int i=0; i< *n; i++){
        cout << "Codigo : "<<codigo[i]<<"  Promedio: "<<promedio[i]<<endl;
    }
}


int main(){
    
    int n=3;
    int *p_n=&n;
    int *codigo=new int[*p_n]; //reservo n espacios principales
    float *promedio = new float[*p_n]; 
    int indice=0;
    int *p_indice=&indice;

    AgregarEstudiante(codigo, promedio, p_n, p_indice);
    imprimirEstudiantes(codigo, promedio, p_indice);

    cout<< "--------------------------------------------\n";

    EliminarDesaprobados(codigo, promedio, p_indice);
    imprimirDesaprobados(codigo, promedio, p_indice);
    

    
    return 0;
}