/*
Problem:	alliance - w5_alliance
Submitted:	18:00
Language:	C++
Time used:	3.44 second
Memory used:	104595456 bytes
Writed by PorcaM
*/

#include <iostream>
#include <list>
using namespace std;

int T, N, M;
bool *isGroup;
typedef list<int> IntList;
IntList *partnerOf;
int p[100000][1000];

inline int mark(int num) {
	if (isGroup[num]) return 0;
	else isGroup[num] = true;
	int ret = 1;
	if (partnerOf[num].size() == 0) return ret;
	else {
		for (IntList::iterator pi = partnerOf[num].begin();
		pi != partnerOf[num].end(); pi++) {
			ret += mark(*pi);
		}
		return ret;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		partnerOf = new IntList[N];
		isGroup = new bool[N];
		for (int i = 0; i < N; i++) {
			isGroup[i] = false;
		}
		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			partnerOf[a].push_back(b);
			partnerOf[b].push_back(a);
		}
		int max = 0;
		for (int i = 0; i < N; i++) {
			if (isGroup[i]) continue;
			else {
				int temp = mark(i);
				if (max < temp) max = temp;
			}
		}
		cout << max << "\n";
	}
}