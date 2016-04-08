/*
Problem:	starwars - w6_starwars
Submitted:	21:43
Language:	C++
Time used:	10.04 second
Memory used:	262144 bytes
*/

#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
	int d, a, b;
};

int T, N;
int x[100], y[100];
int g[100], n[100];

Edge e[10000];

inline bool edge_sort(Edge e1, Edge e2) {
	return (e1.d < e2.d);
}

inline void us_union(int a, int b) {
	int last = n[b];
	n[b] = n[a];
	n[a] = last;
	for (int i = last; i != b; i = n[i])
		g[i] = g[a];
	g[b] = g[a];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	cout << 1 << endl;
	while (T--) {
		int ec = 0;
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> x[i] >> y[i];
			n[i] = g[i] = i;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)continue;
				int d = abs(x[i] - x[j]) + abs(y[i] - y[j]);
				e[ec].d = d; e[ec].a = i; e[ec].b = j;
				ec++;
			}
		}
		sort(e, e + ec, edge_sort);
		register int d_max = 0, c = 0;
		for (int i = 0; i < ec; i++) {
			int d = e[i].d, a = e[i].a, b = e[i].b;
			if (g[a] == g[b]) continue;
			else {
				if (g[a] < g[b])	us_union(b, a);
				else				us_union(a, b);
				if (d_max < d) d_max = d;
				c++;
			}
			if (c > N) break;
		}
		//cout << "N: " << N << ", C: " << c << ", EC: " << ec << endl;
		cout << d_max << endl;
	}
}