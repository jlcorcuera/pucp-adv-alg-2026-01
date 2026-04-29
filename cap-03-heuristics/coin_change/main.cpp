
/* 
 * File:   coin_change.cpp
 * Author: Igor Siveroni
 * Tenemos m tipos d emonedas con las siguientes denominaciones
 * d: d1,d2,...,dm
 * Dado un valor total de cambio n, queremos calular el numero minodo de monesdas a utilizar.
 * Es decir, dados x:x1,...,xm, con  xi>=0
 *    Minimizar:  Sum x_i, 1<=i<=m
 *    Sujeto a: Sum xi*di = n, 1<=i<=m
 */

#include <iostream>
#include <vector>
#include <stack>
// #include <limits>
#include <climits>

using namespace std;

bool lt(int a, int b) {
    return a < b;
}

bool gt(int a, int b) {
    return a > b;
}

/*
*
* Usando programacion dinamica, definimos
* F(n): Numero minimo de monedas que suma n.
* F(0) = 0
* F(n) = min F(n-dj), j: dj <= n
F[0] <- 0
for i<- 1...n // calcular F[i]
  aux <- inf
  j <- 1
  while j <= m and dj <= i
    aux = min(aux,F[i-dj]
    j <- j+1
  F[i] = 1+aux
*/

int min_coin_change_pd(vector<int> denom, int n) {
  int m = denom.size(); // numero de denominaciones  
  vector<int> F(n+1, 0); // soluciones PD
  vector<int> eleccion(n+1, -1); // moneda 

  if (!is_sorted(denom.begin(), denom.end(), lt))  // ascendente
    sort(denom.begin(), denom.end(), lt);
  // F[0] <- 0 - por inicializacion
  for (int i=1; i <= n; i++) { // Calcular F[i]
    int minimo = INT_MAX; // infinito
    int chosen_coin=-1;
    int j = 0; // probar todas las monedas empezando por denom[j=0]
    while (j < m && denom[j] <= i) {
      if (F[i-denom[j]]  < minimo) {
	minimo = F[i-denom[j]];
	chosen_coin = j;
      }
      j++;
    }
    if (minimo == INT_MAX) {
      F[i] = INT_MAX;
    } else {
      F[i] = 1 + minimo;
    }
    eleccion[i] = chosen_coin;
  }

  // ----------- imprimir resultados ---------
  cout << "Solucion PD. Cambio para: " << n << endl;  
  if (F[n]==INT_MAX) {
    cout << "No se puedo encontrar cambio exacto" << endl;
    return 0;
  }
  int por_cambiar = n;
  while (por_cambiar > 0) { 
    int moneda = eleccion[por_cambiar];
    cout << "Moneda: " << denom[moneda] << endl;
    por_cambiar -= denom[moneda];    
  }
  cout << "Numero de monedas en el cambio: " << F[n] << endl;
  cout << "Cambio restante: " << por_cambiar << endl;
  return F[n];
}

/*
 * Greedy / Goloso: Escoger  siempre la mayor denominacion
 * Reordenar d de tal modo que
 * d: d1,d2,...,dm, d1 > d(i+1)
 * n <- n
 * j <- 1
 * count <- 0
 * C = {}
 * while (n>0) and (j<=m)
 * if (n<dj)
 *   j <- j+1
 * else
 *  count <- count+1
 *  n <- n - dj
 *  C = C U {dj}
 */

int min_coin_change_greedy(vector<int> denom, int n) {
  int cambio_restante = n;
  int num_monedas=0;
  int m = denom.size(); // numero de denominaciones
  if (!is_sorted(denom.begin(), denom.end(), gt))  // descendente
    sort(denom.begin(), denom.end(), gt);
  int i = 0;
  cout << "Solucion Greedy. Cambio para: " << n << endl; 
  while (i < m && cambio_restante>0) {
    if (cambio_restante >= denom[i]) {
      cout << "Moneda: " << denom[i] << endl;
      cambio_restante -= denom[i];
      num_monedas++;
    } else
      i++;
  }
  cout << "Numero de monedas en el cambio: " << num_monedas << endl;
  cout << "Cambio restante: " << cambio_restante << endl;
  return (cambio_restante>0) ? 0 : num_monedas; 
}


// g++ -std=c++11 coin_change.cpp

int main(int argc, char** argv) {

  // denominaciones
  vector<int> denom = {1, 5, 10, 25, 50};
  // vector<int> denom = {2, 5, 10, 25, 50};  // 22, 23
  //vector<int> denom = {5,10,20,25};  // 40

  int c = 27;
  cout << min_coin_change_pd(denom, c);
  cout << "---------------" << endl;
  min_coin_change_greedy(denom, c);

  return 0;
}

