#include <bits/stdc++.h>
using namespace std;

int main() {
	long n, k, u;
	cin >> n >> k >> u;

	vector<unordered_map<long,bool>> cartelas = vector<unordered_map<long,bool>>(n);
	for (long iCartela=0; iCartela < cartelas.size(); iCartela++) {
		cartelas[iCartela] = unordered_map<long,bool>();
		for (long iInteiro=0; iInteiro < k; iInteiro++) {
			long inteiro;
			cin >> inteiro;
			cartelas[iCartela][inteiro] = true;
		}
	}

	vector<long> ganhadores = vector<long>();
	for (long iSorteio=0; iSorteio < u; iSorteio++) {
		int numeroSorteado;
		cin >> numeroSorteado;

		for (long iCartela=0; iCartela < n; iCartela++) {
			bool has = cartelas[iCartela].find(numeroSorteado) != cartelas[iCartela].end();
			if (has) {
				cartelas[iCartela].erase(numeroSorteado);
				if (cartelas[iCartela].size() == 0)
					ganhadores.push_back(iCartela);
			}
		}

		if (ganhadores.size() > 0)
			break;
	}

	for (long i=0; i < ganhadores.size(); i++)
		cout << (i==0?"":" ") << ganhadores[i] + 1;
	cout << endl;

	return 0;
}
