#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int>predecesores;
};
bool compara(Proyecto a,Proyecto b) {
    return (a.beneficio*a.ganancia)/a.costo > (b.beneficio*b.ganancia)/b.costo;
}

bool verifica(Proyecto proy,vector<int>solu) {
    int cont=0;
    if (proy.predecesores.size()==0)return true;

    for (int i=0;i<proy.predecesores.size();i++) {
        for (int j=0;j<solu.size();j++)
            if (proy.predecesores[i]==solu[j])
                cont++;
    }
    if (cont==proy.predecesores.size())
        return true;
    return false;
}

int seleccionaProyectos(Proyecto *proy,int presu,int n) {
    int i=0;
    int parcial=0;
    int ganancia=0;
    sort(proy,proy+n,compara);
    vector<int>solu;
    vector<Proyecto>cart;
    for (int j=0;j<n;j++)
        cout <<proy[j].id << " ";
    cout << endl;
    cart.insert(cart.begin(),proy,proy+n);
    while (i<n and parcial<presu and cart.size()>0) {
        if (presu>=parcial+cart[i].costo and verifica(cart[i],solu)) {
            parcial+=cart[i].costo;
            ganancia+=cart[i].ganancia;
            solu.push_back(cart[i].id);
            cart.erase(cart.begin()+i);
            i=0;
        }
        else
            i++;
    }
    for (int i=0;i<solu.size();i++)
        cout << solu[i] << " ";
    cout << endl;
    return ganancia;
}

int main() {
    Proyecto cartera[]={
        {1,80,150,2,{}},
        {2,20,80,5,{4}},
        {3,100,300,1,{1,2}},
        {4,100,150,4,{}},
        {5,50,80,2,{}},
        {6,10,50,1,{2}},
        {7,50,120,2,{6}},
        {8,50,150,4,{6}},
    };
    int presu=250;
    int n=sizeof(cartera)/sizeof(cartera[0]);

    cout << seleccionaProyectos(cartera,presu,n);

    return 0;
}