#include <iostream>
#include <climits>
using namespace std;

int subset(int *arr,int n) {
    int suma=0;
    for(int i=0;i<n;i++) suma+=arr[i];
    /*
     usando los primeros i elementos del arreglo
     ¿puedo obtener una suma exactamente igual a j?
    */
    int dp[n+1][suma+1];
    // suma de 0: no elijo ningún elemento
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;
    // si hay 0 elementos, no puedo conseguir la suma i
    for (int i=1;i<=suma;i++)
        dp[0][i] = 0;

    for (int i=1;i<=n;i++) {
        for (int j=1;j<=suma;j++) {
            // Calculo de la suma j sin utilizar el elemento actual
            dp[i][j]=dp[i-1][j];
            // En caso no se pueda, consideremos el elemento j
            if (dp[i][j]==0 and (j-arr[i-1]>=0))
                /*
                 * Veamos si sin considerar el elemento actual
                 * el complemento de la suma se puede obtener
                 */
                dp[i][j]=dp[i-1][j-arr[i-1]];
        }
    }
    // imprimimos nuestro dp
    for (int i=0;i<=n;i++) {
        for (int j=0;j<=suma;j++)
            cout<<dp[i][j]<<" ";
        cout << endl;
    }
    int diff=INT_MAX;
    // verificamos si podemos obtener la mitad
    for (int j=suma/2;j>=0;j--)
        if (dp[n][j]==1) {
            cout <<  j << endl;
            diff= suma - j*2;
            break;
        }
    if (diff==0)
        cout <<"Se puede dividir en 2 iguales"<<endl;
    else
        cout <<"No se puede dividir en 2 iguales"<<endl;

    return diff;
}

int main() {
    // el arreglo debe estar ordenado
    int arr[]={ 1,5,5,11};
    int n=sizeof(arr)/sizeof(arr[0]);

    cout <<"La diferencia es:"<< subset(arr,n);

    return 0;
}