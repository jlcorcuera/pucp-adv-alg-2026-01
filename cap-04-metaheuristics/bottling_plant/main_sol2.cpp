#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>

using namespace std;

struct Orden {
    int id;
    int cantidad;
    int prioridad;   // 1=alta, 2=media, 3=baja
    double tiempo;   // cantidad * 6 min
};

struct Linea {
    vector<Orden> ordenes;
    double carga = 0.0;
};

const int M = 5;
const int N = 20;
const double ALFA = 0.3;
const int MAX_ITER = 10000;

// Datos dados
int cantidades[N] = {103,58,88,126,195,90,54,195,124,113,193,55,97,97,169,50,167,74,79,109};
int prioridades[N] = {2,1,3,1,2,2,3,1,2,3,2,1,1,2,2,2,3,1,2,1};

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
        ordenes[i].id = i+1;
        ordenes[i].cantidad = cantidades[i];
        ordenes[i].prioridad = prioridades[i];
        ordenes[i].tiempo = cantidades[i]*6.0;
    }

    double mejorMakespan = INT_MAX;
    vector<Linea> mejorSolucion;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        vector<Linea> lineas(M);
        vector<Orden> noAsignadas = ordenes;

        while (!noAsignadas.empty()) {
            // Encontrar mínima prioridad de no asignadas
            int minPrioridad = 3;
            for (const auto &o : noAsignadas)
                if (o.prioridad < minPrioridad)
                    minPrioridad = o.prioridad;

            // Filtrar órdenes con prioridad mínima
            vector<Orden> prioridadMin;
            for (const auto &o : noAsignadas)
                if (o.prioridad == minPrioridad)
                    prioridadMin.push_back(o);

            // Construir RCL1: órdenes de prioridad mínima con tiempo dentro de ALFA
            sort(prioridadMin.begin(), prioridadMin.end(),
                [](const Orden &a, const Orden &b) { return a.tiempo < b.tiempo; });
            double t_min1 = prioridadMin.front().tiempo;
            double t_max1 = prioridadMin.back().tiempo;
            double umbral1 = t_min1 + ALFA * (t_max1 - t_min1);
            vector<Orden> RCL1;
            for (const auto &o : prioridadMin) {
                if (o.tiempo <= umbral1) RCL1.push_back(o);
                else break;
            }

            // Construir RCL2: ordenes con tiempo cercano al minimo (entre todas no asignadas)
            sort(noAsignadas.begin(), noAsignadas.end(),
                [](const Orden &a, const Orden &b) { return a.tiempo < b.tiempo; });
            double t_min2 = noAsignadas.front().tiempo;
            double t_max2 = noAsignadas.back().tiempo;
            double umbral2 = t_min2 + ALFA * (t_max2 - t_min2);
            vector<Orden> RCL2;
            for (const auto &o : noAsignadas) {
                if (o.tiempo <= umbral2) RCL2.push_back(o);
                else break;
            }

            // Selección aleatoria entre RCL1 y RCL2 (50%-50%)
            Orden sel;
            if ((rand() % 100) < 50 && !RCL1.empty()) {
                int idx = rand() % RCL1.size();
                sel = RCL1[idx];
            } else if (!RCL2.empty()) {
                int idx = rand() % RCL2.size();
                sel = RCL2[idx];
            } else {
                // En caso extremo, seleccionar cualquier orden no asignada
                sel = noAsignadas[rand() % noAsignadas.size()];
            }

            // Asignar orden a línea con menor carga
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

            // Eliminar orden asignada
            noAsignadas.erase(remove_if(noAsignadas.begin(), noAsignadas.end(),
                [sel](const Orden &o) { return o.id == sel.id; }), noAsignadas.end());
        }

        double makespan = calcularMakespan(lineas);
        if (makespan < mejorMakespan) {
            mejorMakespan = makespan;
            mejorSolucion = lineas;
        }
    }

    cout << "Mejor Makespan encontrado: " << mejorMakespan << " minutos\n";
    for (int i = 0; i < M; i++) {
        cout << "Linea " << i+1 << ": ";
        for (auto &o : mejorSolucion[i].ordenes)
            cout << o.id << "(P" << o.prioridad << ") ";
        cout << "\n";
    }

    return 0;
}

