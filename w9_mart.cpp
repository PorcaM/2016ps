#include <iostream>
#include <string.h>
using namespace std;

int T, N, a[100], m[100], K;
bool valid[100001]; 

void validate(int it) {
	for (int i = 0; i < N; i++) {
		int ti = it - a[i];
		if (ti >= 0 && valid[ti]) {
			valid[it] = true;
		}
	}
}

void print_yesno(bool f) {
	if (f) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		// Init
		memset(valid, 0, sizeof(valid));
		// Input
		cin >> N;
		for (int i = 0; i < N; i++) cin >> a[i];
		for (int i = 0; i < N; i++) cin >> m[i];
		cin >> K;
		// Fill valid
		valid[0] = true;
		for (int i = 0; i < K; i++) {
			validate(i + 1);
		}
		print_yesno(valid[K]);
	}
}