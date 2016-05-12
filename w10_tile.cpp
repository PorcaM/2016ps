/*

Problem:	Tile - w10_Tile
Submitted:	01:54
Language:	C++
Time used:	0.07 second
Memory used:	131072 bytes

*/
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define MAX_NUM  500

struct Tile{
	int	a, b;
};

int		T, K;
Tile	tl[MAX_NUM];
int		lis[MAX_NUM];

bool cmp(const Tile a, const Tile b) {
	return a.a < b.a || (a.a == b.a && a.b < b.b);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> K;
		for (int i = 0; i < K; i++) {
			int A, B;
			cin >> A >> B;
			if	(A < B)		swap(A, B);
			tl[i].a = A; tl[i].b = B;
			lis[i] = 1;
		}
		sort(tl, tl + K, cmp);
		/*cout << "=============test==========\n";
		for (int i = 0; i < K; i++) cout << tl[i].a << "\t";
		cout << "\n";
		for (int i = 0; i < K; i++) cout << tl[i].b << "\t";
		cout << "\n";*/
		for (int i = 1; i < K; i++) {
			for (int j = 0; j < i; j++) {
				if (tl[i].b >= tl[j].b && lis[i] < lis[j] + 1) {
					lis[i] = lis[j] + 1;
				}
			}
		}
		/*for (int i = 0; i < K; i++) cout << lis[i] << "\t";
		cout << "\n";*/
		int max_value = 0;
		for (int i = 0; i < K; i++) {
			if (max_value < lis[i]) max_value = lis[i];
		}
		cout << max_value << endl;
	}
	return 0;
}