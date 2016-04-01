#include <iostream>
#include <string.h>
#include <algorithm>
#include <functional>
#include <list>
using namespace std;

int T, N, M;
typedef list<int> IntList;
IntList *nakama[100000];

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			nakama[i] = new IntList;
			nakama[i]->push_back(i);
		}
		for (int i = 0; i < M; i++) {
			int x, y;
			cin >> x >> y;
			x--; y--;
			IntList *temp = new IntList;
			temp->merge(*nakama[x]);
			temp->merge(*nakama[y]);
			for (IntList::const_iterator li = temp->begin();
			li != temp->end(); li++) {
				nakama[*li] = temp;
			}
		}
		int max = 0;
		for (int i = 0; i < N; i++) {
			if (max < nakama[i]->size())
				max = nakama[i]->size();
		}
		cout << max << "\n";
	}
}