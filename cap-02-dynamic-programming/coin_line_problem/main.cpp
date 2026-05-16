#include <iostream>

using namespace std;

const int MAX_N = 50;

long long count_ways(long long dp[MAX_N][MAX_N][MAX_N][4], int p, int q, int r, int last_idx) {
    // CASO BASE: si ya no quedan monedas, encontramos 1 forma válida
    if (p == 0 && q == 0 && r == 0) {
        return 1;
    }

    // Si este estado ya fue calculado, lo devolvemos
    if (dp[p][q][r][last_idx] != -1) {
        return dp[p][q][r][last_idx];
    }

    long long ways = 0;

    // Probamos colocar una moneda de 1 sol (mapeada al índice 1), si y solo si la ultima moneda no fue 1
    if (p > 0 && last_idx != 1) {
        ways += count_ways(dp, p - 1, q, r, 1);
    }

    // Intentar colocar una moneda de 2 soles (mapeada al índice 2), si y solo si la ultima moneda no fue 2
    if (q > 0 && last_idx != 2) {
        ways += count_ways(dp, p, q - 1, r, 2);
    }

    // Intentar colocar una moneda de 5 soles (mapeada al índice 3), si y solo si la ultima moneda no fue 5
    if (r > 0 && last_idx != 3) {
        ways += count_ways(dp, p, q, r - 1, 3);
    }

    // Guardar el resultado en la memoria y retornar
    dp[p][q][r][last_idx] = ways;
    return ways;
}

int main() {
    int p = 2; // Monedas de 1 sol
    int q = 2; // Monedas de 2 soles
    int r = 1; // Monedas de 5 soles

    long long dp[MAX_N][MAX_N][MAX_N][4];
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            for (int k = 0; k < MAX_N; k++) {
                for (int l = 0; l < 4; l++) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }

    long long result = count_ways(dp, p, q, r, 0);

    cout << "Para p=" << p << ", q=" << q << ", r=" << r << endl;
    cout << "El numero de formas validas es: " << result << endl;

    return 0;
}