#include <iostream>

using namespace std;

const int N = 6;

int main() {
    int coins[] = {0, 5, 1, 2, 10, 6, 2};
    int dp[N + 1];
    dp[0] = coins[0];
    dp[1] = coins[1];
    for (int idx = 2; idx <= N; idx++) {
        dp[idx] = max(dp[idx - 1], dp[idx - 2] + coins[idx]);
    }
    int max_value = 0;
    for (int i = 0; i <= N; i++) {
        max_value = max(max_value, dp[i]);
    }
    cout << max_value;
    return 0;
}