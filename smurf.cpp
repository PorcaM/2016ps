#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int T, S, W[1000], i, aver, sum, time, l, m;
	cin >> T;
	while (T--) {
		cin >> S;
		l = m = time = sum = 0;
		for (i = 0; i < S; i++) {
			cin >> W[i];
			sum += W[i];
		}
		sort(W, W + S);
		aver = sum / S;
		for (i = 0; i < S; i++) {
			if (W[i] == aver + 1 || W[i] == aver)
				continue;
			else if (W[i] > aver + 1)
				m += W[i] - (aver + 1);
			else
				l += aver - W[i];
		}
		m > l ? time = m : time = l;
		cout << time << endl;
	}
}