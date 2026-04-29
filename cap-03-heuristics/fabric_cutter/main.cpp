/**
 * Implementacion de algoritmo Goloso para resolver el Problema de Programación de Telares: 
 * Se tiene K maquinas idénticas que hacen tela (telares). A cada telar le toma T unidades de
 * tiempo tejer 1 metro de tela. Por otro lado, se tiene n telas por tejer de diferentes
 * tamaños (en metros) denotados por telas={t1,t2,…tn}. Diseñe e implemente un algoritmo
 * goloso para encontrar el tiempo mínimo para terminar de tejer todas las telas con la 
 * restricción de que una tela no puede tejerse o compartirse en más de un telar. Probar su 
 * implementación con T=5, K=4, N=6, telas={10, 7, 8, 12, 6, 8}
 * 
 * Autor: Dr. Edwin Villanueva
 *
 * Modificacion: Igor Siveroni
 * Pregunta: modificar el problema asuminedo ahora que cada telar toma distintos tiempos T
 *   e.g. tiempos[] = {5, 4, 6};
 * Probar otro criterio de optimizacion local
 * Por ejemplo: escoger la asignacion que "acabe" primero
 */

#include <iostream>
#include <algorithm> // Para std::sort
#include <climits> // Para INT_MAX

using namespace std;

void programarTelares(int telas[], int n, int k, int T[]) {
  int workloads[k]; // = {0}; // Carga de trabajo de cada telar
    fill(workloads, workloads+k,0);
    int Asignaciones[k][n]; // Asignaciones de telas a cada telar
    int contadorAsignaciones[k];// = {0}; // Contador de telas asignadas a cada telar
    fill(contadorAsignaciones, contadorAsignaciones+k,0);

    for (int i = 0; i < n; i++) {
        // Encuentra el telar que tiene la menor carga de trabajo actual
        int minIndex = 0;
        int minWorkload = workloads[0];

        /*
        for (int j = 1; j < k; j++) {
            if (workloads[j] < minWorkload) {
                minIndex = j;
                minWorkload = workloads[j];
            }
        }
        //cout << "min work load chosen: " << minIndex << endl;
         */
        
        minIndex=0;
        int minEndTime = workloads[0]+ telas[i] * T[0];
        for (int j = 1; j < k; j++) { // analizar cada telar restante
            if (workloads[j] + telas[i]*T[j]  < minEndTime) {
                minIndex = j;
                minEndTime = workloads[j] + telas[i]*T[j]  ;
            }
        }
        //cout << "min endTime chosen: " << minIndex << endl;
        
        // Asignar la tela actual al telar con la menor carga de trabajo actual
        workloads[minIndex] += telas[i] * T[minIndex]; // Agregar tiempo de tejer la tela actual
        Asignaciones[minIndex][contadorAsignaciones[minIndex]++] = telas[i];
    }

    // Imprimir los resultados
    cout << "Asignaciones de telas a los telares:\n";
    for (int i = 0; i < k; i++) {
        cout << "Telar " << i << ": ";
        for (int j = 0; j < contadorAsignaciones[i]; j++) {
            cout << Asignaciones[i][j] << (j < contadorAsignaciones[i] - 1 ? ", " : "");
        }
        cout << " - Tiempo total de trabajo: " << workloads[i] << " unidades de tiempo\n";
    }

    // Encontrar el tiempo mínimo para terminar de tejer todas las telas
    int maxWorkload = *max_element(workloads, workloads + k);
    cout << "Tiempo mínimo para terminar todas las telas: " << maxWorkload << " unidades de tiempo\n";
}

int main() {
    int T = 5; // Tiempo por metro de tela
    int k = 3; // Número de telares
    int n = 6; // Número de telas

    int telas[] = {10, 7, 8, 12, 6, 9}; // Telas a tejer
    int tiempos[] = {5, 4, 6};

    programarTelares(telas, n, k, tiempos);

    return 0;
}

