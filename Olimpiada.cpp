/*
 10^8 operacoes!
 PRINTAR COM COUT << ... << ENDL;
 Tentar diminuir Complexidade (logaritmica, linear, n log,...)

Outros: descobrir divisores: ateh raiz de n (quando for divisivel por um numero adicionar o numero multiplicado tambem), nao alocar vetor dinamicamente
*/

#include <bits/stdc++.h>
using namespace std;

void main()
{
    // cin >> a >> b  *IGUAL A*  cin >> a; cin >> b;
    int n;
    cin >> n;
    for(int i=0; i<n; i++)
    {
       int curr;
       cin >> curr;
    }


    //vetor
    int length = 10;
    vector<int> vet1 (length);
    int vet2[length];

    sort(vet1.begin(), vet1.end());
    sort(vet2, vet2 + length);

    for (int x : vet1) {}
    for (int x : vet2) {}
    //no need: for (vector<int>::iterator it = vet1.begin(); it <= vet1.end(); it++) int valor = *it;

    // busca binaria
    int i = lower_bound(vet1.begin(), vet1.end(), numero) - vet1.begin();
    int i = lower_bound(vet2, vet2 + length, numero) - vet2;

    // lista
    queue<int> lista;
    lista.push(1);
    int x = lista.front();
    lista.pop();
    bool a = lista.empty();

    // hashmap
    unordered_map<string, double> umap;
    umap["PI"] = 3.14;
    bool found = umap.find(key) != umap.end();
}
