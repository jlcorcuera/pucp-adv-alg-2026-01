#include <iostream>
using namespace std;

long long fibonacci(long long N) {
    if (N <= 1) return N;
    return fibonacci(N - 1) + fibonacci(N - 2);
}

int main() {
    long long N = 40;
    long long dp[N + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= N ; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << "Fibonacci N DP: "<< dp[N] << endl;
    cout << "Fibonacci N RECURSIVE: "<< fibonacci(N) << endl;
    return 0;
}