/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 29 de abril de 2025, 02:24 PM
 */

#include <iostream>
#include <algorithm>

using namespace std;

bool compara(int a,int b){
    return a<b;
}
void muestra(int *paq,int n){
    for(int i=0;i<n;i++)
        cout << paq[i] << " ";
    cout << endl;
}


int cargamochila(int *paq,int peso,int n){
    int residual=peso;
    
    sort(paq,paq+n,compara);
    muestra(paq,n);
    
    for(int i=0;i<n;i++){
        if(residual-paq[i]>=0)
            residual-=paq[i];
    }
    return residual;
}

int main(int argc, char** argv) {
    int paq[]={3,2,2,10,4};
    int peso=15;
    int n=sizeof(paq)/sizeof(paq[0]);
    
    cout<<"Espacio sobrante:" << cargamochila(paq,peso,n);
    
    return 0;
}

