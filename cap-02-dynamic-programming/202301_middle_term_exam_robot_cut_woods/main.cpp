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
                for (int k = 0; k < ATTRIBUTES; k++) {
                    int temp = data[k][i];
                    data[k][i] = data[k][j];
                    data[k][j] = temp;
                }
            }
        }
    }

    cout << "Sorted data " << endl;
    print(data);

    int dp[N_PRESENTATIONS + 1];
    dp[0] = data[2][0];
    for (int i = 1; i <= N_PRESENTATIONS; i++) {
        /*
         * take a look here, the benefit of the i wood is located
         * in the data matrix at the location (i - 1)
         */
        int current_benefit = data[2][i - 1];
        int previous_benefit = dp[i - 1];

        int new_benefit = 0;
        for (int j = i - 1; j > 0; j--) {
            /*
             * same here, access to the data of wood i or j requires substract 1
             */
            if (data[0][i - 1] >= data[1][j - 1]) {
                new_benefit = dp[j];
                break;
            }
        }

        new_benefit = new_benefit + current_benefit;
        dp[i] = max(previous_benefit, new_benefit);
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
    solve(data);
    return 0;
}