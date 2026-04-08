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
    /*
     * FIX: The code for determining the max sum was removed since
     * dp[i] contains/refers to the max sum of coins at position i so
     * at the end, position N will contain that max sum value
    */
    cout << dp[N];
    return 0;
}