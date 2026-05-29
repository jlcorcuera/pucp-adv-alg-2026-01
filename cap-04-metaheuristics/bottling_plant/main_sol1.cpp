#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Orden {
    int id;
    int cantidad;
    double tiempo; // cantidad * 6
};

struct Linea {
    vector<Orden> ordenes;
    double carga = 0.0;
};

const int M = 5;
const int N = 20;
int cantidades[N] = {103, 58, 88, 126, 195, 90, 54, 195, 124, 113,
                    193, 55, 97, 97, 169, 50, 167, 74, 79, 109};
const int MAX_ITER = 100000;
const double ALFA = 0.3;

double calcularMakespan(const vector<Linea> &lineas) {
    double maxCarga = 0.0;
    for (const auto &l : lineas) {
        if (l.carga > maxCarga) maxCarga = l.carga;
    }
    return maxCarga;
}

int main() {
    srand(time(NULL));

    vector<Orden> ordenes(N);
    for (int i = 0; i < N; i++) {
        ordenes[i].id = i + 1;
        ordenes[i].cantidad = cantidades[i];
        ordenes[i].tiempo = cantidades[i] * 6.0;
    }

    double mejorMakespan = 1e9;
    vector<Linea> mejorSolucion;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        vector<Linea> lineas(M);
        vector<Orden> noAsignadas = ordenes;

        while (!noAsignadas.empty()) {
            // RCL - mayor tiempo
            sort(noAsignadas.begin(), noAsignadas.end(),
                [](const Orden &a, const Orden &b) { return a.tiempo > b.tiempo; });
            double t_max2 = noAsignadas.front().tiempo;
            double t_min2 = noAsignadas.back().tiempo;
            double umbral2 = t_max2 - ALFA * (t_max2 - t_min2);
            vector<Orden> RCL;
            for (const auto& o : noAsignadas) {
                if (o.tiempo >= umbral2) RCL.push_back(o);
                else break;
            }

            int idx = rand() % RCL.size();
            Orden sel = RCL[idx];

            int lineaMenor = 0;
            double cargaMin = lineas[0].carga;
            for (int i = 1; i < M; i++) {
                if (lineas[i].carga < cargaMin) {
                    cargaMin = lineas[i].carga;
                    lineaMenor = i;
                }
            }

            lineas[lineaMenor].ordenes.push_back(sel);
            lineas[lineaMenor].carga += sel.tiempo;

            noAsignadas.erase(remove_if(noAsignadas.begin(), noAsignadas.end(),
                [sel](const Orden &o) { return o.id == sel.id; }), noAsignadas.end());
        }

        double makespan = calcularMakespan(lineas);
        if (makespan < mejorMakespan) {
            mejorMakespan = makespan;
            mejorSolucion = lineas;
        }
    }

    cout << "Mejor Makespan: " << mejorMakespan << " minutos\n";
    for (int i = 0; i < M; i++) {
        cout << "Linea " << i + 1 << ": ";
        for (auto &o : mejorSolucion[i].ordenes)
            cout << o.id << " ";
        cout << endl;
    }

    return 0;
}
