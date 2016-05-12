#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

struct Tile
{
	int x, y;
};

int T, K;
Tile tl[500];
int bc[500];
int lis[500];

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		memset(bc, 0, sizeof(bc));
		memset(lis, 0, sizeof(lis));
		cin >> K;
		for (int i = 0; i < K; i++) {
			int A, B;
			cin >> A >> B;
			if (A < B) swap(A, B);
			tl[i].x = A; tl[i].y = B;
		}
		for (int i = 0; i < K; i++) {
			Tile base = tl[i];
			for (int j = 0; j < K; j++) {
				Tile ti = tl[j];
				if (ti.x <= base.x && ti.y <= base.y) bc[i]++;
			}
		}
		sort(bc, bc + K);
		for (int i = 0; i < K; i++) {
			int max_value = 0;
			for (int j = 0; j < i; j++) {
				if (max_value < lis[j] && bc[j] < bc[i]) max_value = lis[j];
			}
			lis[i] = max_value + 1;
		}
		for (int i = 0; i < K; i++)
			cout << bc[i] << " ";
		cout << endl;
		for (int i = 0; i < K; i++)
			cout << lis[i] << " ";
		cout << endl;
		cout << lis[K - 1] << "\n";
	}
	return 0;
}