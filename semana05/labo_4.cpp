#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

struct polinomio{
    int n; //cantidad de elementos
    float *coef;
};

//______________________________________________

void leerDatos(struct polinomio A, int n){
    for(int i=0; i< n; i++){
        cout<< "Ingrese el coeficiente de x^"<< n-i -1<< " : ";
        cin >> A.coef[i]; 
    }


}


void mostrarPoli(struct polinomio A, int n){
    for(int i=0; i< n;i++){
        cout << A.coef[i]<< "x^"<< n-i-1;

        if(i != n-1){
            cout << " + ";
        }
    }
    cout << endl;
}

void sumaPol(struct polinomio A, int n_a, struct polinomio B, int n_b){
    int n_suma;
    int n_min;
    bool bandera;
    if(n_a >= n_b){
        n_suma = n_a;
        n_min=n_b;
        bandera=true;
    } else{
        n_suma = n_b;
        n_min=n_a;
        bandera = false;
    }
    float *suma= new float[n_suma]; //reservo 

    int conteo=0;
    if(bandera){
        for(int i=0; i<n_suma; i++){
            if(n_min +i >= n_suma){
                suma[i] = A.coef[i] + B.coef[i-conteo];
            } else{
                suma[i] = A.coef[i];
                conteo++;
            }
        }
    } else {
        for(int i=0; i<n_suma; i++){
            if(n_min +i >= n_suma){
                suma[i] = B.coef[i] + A.coef[i-conteo];
            } else{
                suma[i] = B.coef[i];
                conteo++;
            }
        }

    }

    //imprimir 
    cout <<"\nLa suma de los polinomios : ";
    for(int i=0; i<n_suma; i++){
        cout << suma[i]<< "x^"<< n_suma-i-1;

        if(i != n_suma-1){
            cout << " + ";
        }
    }
    cout <<endl;
    delete[] suma;
}

void evaluarPol(struct polinomio A, int n, float valor){
    float resultado=0;

    for(int i=0; i<n; i++){
        resultado=resultado + A.coef[i] * pow(valor, n-i-1); //coef x^i
    }
    cout << "El primer polinomio evaluado en x="<<valor << " es : "<< resultado << endl;
}

void multiplicacion(struct polinomio A, int n_a, struct polinomio B, int n_b){
    int n_total= (n_a - 1) + (n_b - 1);
    n_total++;
    
    float *suma= new float[n_total]; //reservo 
    for(int i=0; i<n_total; i++){
        suma[i]=0; //todos ceros
    }

    int indice=0;
    for(int i=0; i< n_a ; i++){
        
        for(int j=0; j<n_b; j++){
            suma[j+indice] = suma[j+indice] +A.coef[i]*B.coef[j]; //suma escalonada
        }
        indice++;
    }

    //imprimir
    cout << "\nLa multiplicacion de los polinomios es : ";
    for(int i=0; i<n_total; i++){
        cout << suma[i]<< "x^"<< n_total-i-1;

        if(i != n_total-1){
            cout << " + ";
        }
    }
    cout <<endl;
    delete[] suma;
}

int main(){
    struct polinomio A;
    struct polinomio B;

    cout << "\nIngrese el grado del primer polinomio :";
    cin >> A.n;
    A.n++;

    A.coef = new float[A.n]; //reservo la cantidad necesaria 
    leerDatos(A, A.n);

    // otro polinomio
    cout << "\nIngrese el grado del segundo polinomio :";
    cin >> B.n;
    B.n++;

    B.coef = new float[B.n]; //reservo la cantidad necesaria 
    leerDatos(B, B.n);

    cout << "\nPrimer polinomio : ";
    mostrarPoli(A, A.n);

    cout << "\nSegundo polinomio : ";
    mostrarPoli(B, B.n);

    sumaPol(A, A.n, B, B.n);

    multiplicacion(A, A.n, B, B.n);

    float valor;
    cout <<"\nIngrese el valor de x para el primer polinomio : \n";
    cin >> valor;

    evaluarPol(A, A.n ,valor);

    delete[] A.coef;
    delete[] B.coef;
    return 0;
}