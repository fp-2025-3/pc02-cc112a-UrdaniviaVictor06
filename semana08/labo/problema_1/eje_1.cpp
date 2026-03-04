#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>


using namespace std;

struct termino{
    double coef;
    int expo; // los exponentes empiezan desde 0
};

struct polinomio{
    struct termino *terminos; // puntero dinamico al struct termino
    int cantidadTerminos; // esto cuenta desde 0 hasta el n
};

//________________________________________

void crearPolinomio(struct polinomio &p, int n){
    //esta funcion recibe la direccion de un polinomio y lo modifica
    
    p.terminos = new struct termino[n]; // reserva memoria para n terminos en polinomio
    // solo por si acaso, n-1 = grado maximo
    p.cantidadTerminos = n;
}

void leerPolinomio(struct polinomio &p){
    // la funcion recibe la direccion del polinomio, es decir lo modifica
    int cantidad=1; // cantidad limite para evitar dobles exponentes en dos terminos distintos

    cout << "Vamos a completar los terminos que ha creado \n";
    
    for(int i=0; i<p.cantidadTerminos; i++){
        bool bandera =true; // bandera como comprobante para evitar repeticion de exponentes

        p.terminos[i].expo =-1;
        while(p.terminos[i].expo <0 || bandera){ // verdadero y verdadero
            bandera = false;
            // el primer exponente puede ser 0 u otro numero positivo
            cout << "Ingrese el exponente a buscar (mayor igual que 0 y diferente al exponente anterior): ";
            cin >>p.terminos[i].expo; // si es menor que 0 => verdadero

            for(int j=0; j<cantidad; j++){
                if(i == j) continue;
                if(p.terminos[i].expo == p.terminos[j].expo){
                    // si entras aqui, significa que se repite el expo
                    bandera = true;
                }
            } 
        }
        // si sales de aqui significa que no se repite exponentes
        cantidad++;



        /* ningun exponente se debe repetir, osea expo[1]= 4; y expo[4] = 4; esto es incorrecto */
        cout << "Ingrese el coeficiente del exponente "<<p.terminos[i].expo << ": ";
        cin >> p.terminos[i].coef; // 
    }
}

void mostrarPolinomio(const struct polinomio &p){ // no los ordena
    // creemos temporalmente una lista para ordenar y almacenar estos terminos
    struct polinomio copia;
    copia.terminos = new struct termino[p.cantidadTerminos]; 
    
    // ahora copiemos todos los datos
    copia.cantidadTerminos = p.cantidadTerminos;
    for(int i = 0; i< p.cantidadTerminos; i++){
        copia.terminos[i].expo = p.terminos[i].expo;
        copia.terminos[i].coef = p.terminos[i].coef;
    }

    // ya lo tenemos copiado, ahora lo ordenamos
    for(int i=0; i< copia.cantidadTerminos; i++){ // recorre todo el arreglo
        // encontremos el menor exponente
        int indice_min = i; // supongamos que es el primer indice
        for(int j=i; j<copia.cantidadTerminos; j++){
            if(copia.terminos[indice_min].expo > copia.terminos[j].expo){
                indice_min =j; 
            }
        }
        // ye tenmos el minimo
        swap(copia.terminos[indice_min].expo , copia.terminos[i].expo);
        swap(copia.terminos[indice_min].coef , copia.terminos[i].coef);

    }
    // ya tenemos ordanado todo

    for(int i=0; i< copia.cantidadTerminos ; i++){
        if(copia.terminos[i].coef == 0) continue; 
        // si el coef es 0, no lo tomes

        cout << copia.terminos[i].coef << "x^"<< copia.terminos[i].expo;
        if(i < copia.cantidadTerminos -1){
            cout << " + " ; 
        }
    }
    cout << endl;

    delete[] copia.terminos;
}

void evaluarPolinomio(const polinomio &p, double x){
    double resultado=0;

    for(int i=0; i< p.cantidadTerminos; i++){
        double temporal =1;
        for(int j =0; j< p.terminos[i].expo; j++){ // si el expo es 0, no ingresa 
            // supongamos que el exponente es 1 
            temporal = temporal *x;

            // si el exponente es 5, el for realiza 5 multiplicaciones
        }

        resultado = resultado + p.terminos[i].coef * temporal; 
        // vamos acumulando el resultado
    }
    
    
    
    cout << "P("<<x<< ") = "<< fixed <<setprecision(2) <<resultado<< endl;
}

void derivarPolinomio(const struct polinomio &p, struct polinomio &der){
    
    der.terminos = new struct termino[p.cantidadTerminos]; // polinomio derivado una vez
    der.cantidadTerminos = p.cantidadTerminos; 

    for(int i=0; i< p.cantidadTerminos ; i++){
        // si el exponente es 0, su derivada es 0 con coef 0
        if(p.terminos[i].expo ==0){
            der.terminos[i].expo =0;
            der.terminos[i].coef = 0;
        } else {
            der.terminos[i].expo = p.terminos[i].expo -1; // se le disminuye en una unidad a su derivada
        
            der.terminos[i].coef = p.terminos[i].expo * p.terminos[i].coef;
            // su coef es la multi de coef y su expo
        }

    }

}


void liberarPolinomio(struct polinomio &p, struct polinomio &pa){
    delete[] p.terminos;
    delete[] pa.terminos;
}

int main(){

    int n_pol =-1;
    while(n_pol <=0){
        cout << "INGRESE LA CANTIDAD DE TERMINOS DE SU POLINOMIO: ";
        cin >> n_pol;
    }
    struct polinomio poli; // guarda memoria y direccion
    crearPolinomio(poli, n_pol); 

    leerPolinomio(poli);

    mostrarPolinomio(poli); // no los ordena

    double x_valor;
    cout << "\nIngrese un valor a evaluar en su funcion: ";
    cin >>x_valor;
    evaluarPolinomio(poli,x_valor);

    struct polinomio poli_deri; // ya tiene memoria guardada
    derivarPolinomio(poli, poli_deri);

    mostrarPolinomio(poli_deri);


    liberarPolinomio(poli, poli_deri);
    return 0;
}