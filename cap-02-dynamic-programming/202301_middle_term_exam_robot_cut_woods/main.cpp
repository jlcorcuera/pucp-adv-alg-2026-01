#include <iostream>

using namespace std;

const int N_PRESENTATIONS = 4;
const int ATTRIBUTES = 3;

void print(int data[ATTRIBUTES][N_PRESENTATIONS]) {
    for (int i = 0; i < N_PRESENTATIONS; i++) {
        cout << "Presentation " << (i + 1) << endl;
        for (int j = 0; j < ATTRIBUTES; j++) {
            cout << data[j][i] << endl;
        }
    }
}

void solve(int data[ATTRIBUTES][N_PRESENTATIONS]) {
    for (int i = 0; i < N_PRESENTATIONS; i++) {
        for (int j = 0; j < N_PRESENTATIONS; j++) {
            if (data[1][i] < data[1][j]) {
                for (int k = 0; k < N_PRESENTATIONS; k++) {
                    int temp = data[k][i];
                    data[k][i] = data[k][j];
                    data[k][j] = temp;
                }
            }
        }
    }
    int dp[N_PRESENTATIONS + 1];
    dp[0] = 0;
    for (int i = 1; i <= N_PRESENTATIONS; i++) {
        int current_benefit = data[2][i - 1];
        int previous_benefit = dp[i - 1];

        int new_benefit = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (data[0][i] >= data[1][j]) {
                new_benefit = data[2][j];
                break;
            }
        }

        new_benefit = new_benefit + current_benefit;
        if (new_benefit > previous_benefit) {
            dp[i] = new_benefit;
        } else {
            dp[i] = previous_benefit;
        }
    }

    for (int i = 0; i <= N_PRESENTATIONS; i++) {
        cout << i << "). " << dp[i] << endl;
    }
}


int main() {
    /*
    Inicio (m) 5 2 6 4
Fin (m) 10 4 12 15
Beneficio (S/.) 30 40 80 100
     */
    int data[ATTRIBUTES][N_PRESENTATIONS] = {
        {5, 2, 6, 4},
        {10, 4, 12, 15},
        {30, 40, 80, 100}
    };
    cout << "Initial State " << endl;
    print(data);
    solve(data);
    return 0;
}