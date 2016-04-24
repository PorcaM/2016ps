#include <iostream>
using namespace std;

static unsigned int T, M, h[1000], l[1000], r[1000], m, p;
static int i, N;

inline unsigned int cmp_b(unsigned int a, unsigned int b) {
	if (a > b) return a;
	else return b;
}
inline unsigned int cmp_s(unsigned int a, unsigned int b) {
	if (a > b) return b;
	else return a;
}

inline void mark(unsigned int *a) {
	if (h[i] < p)			a[i] = h[i];
	else if (h[i] >= p + 1)	a[i] = p + 1;
	else					a[i] = p;
	p = a[i];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		for (i = 0; i < N; i++)
			cin >> h[i];
		p = 0;
		for (i = 0; i < N; i++) 
			mark(l);
		p = 0;
		for (i = N - 1; i > -1; i--) 
			mark(r);
		m = 0;
		for (i = 0; i < N; i++) {
			m = cmp_b(m, cmp_s(l[i], r[i]));
		}
		cout << m << "\n";
	}
}