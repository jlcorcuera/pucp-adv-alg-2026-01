#include <iostream>

using namespace std;

const int N = 8;

int main() {
    int X[] = {-7, 10, 9, 2, 3, 8, 8, 1};
    int dp[N] = {1};
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (X[i] > X[j]) {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
    }
    int max_value = 0;
    for (int i = 0; i < N; i++) {
        max_value = max(max_value, dp[i]);
    }
    cout << max_value << endl;
    return 0;
}