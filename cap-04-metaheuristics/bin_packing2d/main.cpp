#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#include <cstring>

#define ITERACIONES 1000
#define ALFA 0.15

using namespace std;

struct Objeto {
    char nombre;
    int ancho;  // w
    int alto;   // h
    int area;   // w * h
};

struct Estante {
    int y;              
    int alturaEstante;  
    int anchoUsado;     
};

struct Contenedor {
    int W;  
    int H;  
    vector<Estante> estantes;          
    vector<char> objetosAlmacenados;  

    bool colocarObjeto(const Objeto &obj) {
        for (int i = 0; i < estantes.size(); i++) {
            if (estantes[i].anchoUsado + obj.ancho <= W &&
                obj.alto <= estantes[i].alturaEstante) {
                estantes[i].anchoUsado += obj.ancho;
                objetosAlmacenados.push_back(obj.nombre);
                return true;
            }
        }

        int alturaUsada = 0;
        for (int i = 0; i < estantes.size(); i++) {
            alturaUsada += estantes[i].alturaEstante;
        }
        if (alturaUsada + obj.alto <= H && obj.ancho <= W) {
            Estante nuevo;
            nuevo.y = alturaUsada;
            nuevo.alturaEstante = obj.alto;
            nuevo.anchoUsado = obj.ancho;
            estantes.push_back(nuevo);
            objetosAlmacenados.push_back(obj.nombre);
            return true;
        }

        return false; 
    }
};

struct Solucion {
    int numContenedores;
    vector<vector<char>> contenido; 
};

bool comparaArea(const Objeto &a, const Objeto &b) {
    return a.area > b.area;
}

int buscaIndRCL(const vector<Objeto> &objetos, double umbral) {
    int cont = 0;
    for (int i = 0; i < objetos.size(); i++) {
        if (objetos[i].area >= umbral) 
            cont++;
    }
    return cont;
}

Solucion graspBinPacking2D(Objeto objetos[], int n, int W, int H) {
    Solucion mejorSolucion;
    mejorSolucion.numContenedores = INT_MAX;

    srand(time(NULL));

    for (int iter = 0; iter < ITERACIONES; iter++) {
        vector<Objeto> pendientes;
        for (int i = 0; i < n; i++) {
            pendientes.push_back(objetos[i]);
        }

        vector<Contenedor> contenedores;

        while (!pendientes.empty()) {
            sort(pendientes.begin(), pendientes.end(), comparaArea);

            int beta = pendientes[0].area;                      
            int tau = pendientes[pendientes.size() - 1].area;   

            double umbral = beta - ALFA * (beta - tau);

            int tamRCL = buscaIndRCL(pendientes, umbral);
            if (tamRCL <= 0) tamRCL = 1; 

            int indice = rand() % tamRCL;

            Objeto seleccionado = pendientes[indice];

            bool colocado = false;
            for (int c = 0; c < contenedores.size(); c++) {
                if (contenedores[c].colocarObjeto(seleccionado)) {
                    colocado = true;
                    break;
                }
            }

            if (!colocado) {
                Contenedor nuevo;
                nuevo.W = W;
                nuevo.H = H;
                nuevo.colocarObjeto(seleccionado);
                contenedores.push_back(nuevo);
            }

            pendientes.erase(pendientes.begin() + indice);
        }

        int numBins = contenedores.size();
        if (numBins < mejorSolucion.numContenedores) {
            mejorSolucion.numContenedores = numBins;
            mejorSolucion.contenido.clear();
            for (int c = 0; c < contenedores.size(); c++) {
                mejorSolucion.contenido.push_back(contenedores[c].objetosAlmacenados);
            }
        }
    }

    return mejorSolucion;
}

int main() {

    Objeto objetos[] = {
        {'A', 6, 5, 30},
        {'B', 4, 5, 20},
        {'C', 3, 3,  9},
        {'D', 5, 5, 25},
        {'E', 2, 1,  2},
        {'F', 7, 3, 21},
        {'G', 3, 7, 21},
        {'H', 2, 6, 12},
        {'I', 4, 4, 16},
        {'J', 5, 2, 10},
        {'K', 1, 7,  7},
        {'L', 7, 1,  7}
    };

    int n = sizeof(objetos) / sizeof(objetos[0]);
    int W = 10;
    int H = 10;

    cout << "=============================================" << endl;
    cout << "  GRASP CONSTRUCCION - BIN PACKING 2D" << endl;
    cout << "=============================================" << endl;
    cout << "Contenedores: " << W << " x " << H << endl;
    cout << "Numero de objetos: " << n << endl;
    cout << "Alfa: " << ALFA << endl;
    cout << "Iteraciones: " << ITERACIONES << endl;
    cout << "=============================================" << endl;
    cout << endl;

    Solucion resultado = graspBinPacking2D(objetos, n, W, H);

    cout << "MEJOR SOLUCION ENCONTRADA:" << endl;
    cout << "Numero de contenedores: " << resultado.numContenedores << endl;
    cout << endl;

    for (int i = 0; i < resultado.contenido.size(); i++) {
        cout << "Contenedor " << (i + 1) << ": ";
        for (int j = 0; j < resultado.contenido[i].size(); j++) {
            cout << resultado.contenido[i][j];
            if (j < resultado.contenido[i].size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
    cout << "=============================================" << endl;

    return 0;
}
