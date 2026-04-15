#include <iostream>

using namespace std;

const int N = 4;

void solve(int W, int weights[N], int values[N]) {
    int dp[N+1][W+1];

    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < W + 1; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= W; j++) {
            int value = values[i - 1];
            int weight = weights[i - 1];
            if (weight <= j) {
                dp[i][j] = max(dp[i -1][j], value + dp[i-1][j - weight]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    cout << dp[N][W] << endl;
}

int main() {
    int weights[N] = {2, 1, 3, 2};
    int values[N] = {12, 10, 20, 15};
    int W = 5;
    solve(W, weights, values);
    return 0;
}