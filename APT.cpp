#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int T, M, N, E[1000];
	int i, j, n, d, u;
	int hp, hc, vp, vc;
	cin >> T;
	while (T--) {
		u = 0;
		cin >> M >> N;
		for (n = 0; n < N; n++) {		// day by day
			d = 0;
			for (i = 0; i < 2 * M - 1; i++) {
				cin >> E[i];
				d += E[i];
			}
			for (i = 1; i < M; i++) {
				hp = M + i - 2;
				hc = M + i - 1;
				vp = M - i;
				vc = M - i - 1;
				E[hc] = E[hc] < E[hp] ? E[hc] : E[hp];
				E[vc] = E[vc] < E[vp] ? E[vc] : E[vp];
			}
			int c[2][4] = { 0 };
			j = 0;
			for (i = 0; i < 2 * M - 1; i++) {
				if (i == M - 1) continue;
				if (i > M - 1) {
					j = 1;
				}
				c[j][E[i]]++;
			}
			for (i = 1; i < 4; i++) {
				for (j = 1; j < 4; j++) {
					d += c[0][i] * c[1][j] * (i < j ? i : j);
				}
			}
			u += d;
		}
		cout << u << endl;
	}
}