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
bool isGroup[100000];
typedef pair<int, int> IntPair;
typedef list<IntPair> PairList;
typedef list<int> IntList;
PairList al;
IntList partnerOf[100000];

int mark(int num) {
	if (isGroup[num]) return 0;
	else isGroup[num] = true;
	int ret = 1;
	if (partnerOf[num].size() == 0);
	else {
		for (IntList::iterator pi = partnerOf[num].begin();
		pi != partnerOf[num].end(); pi++) {
			ret += mark(*pi);
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			partnerOf[i].clear();
			isGroup[i] = false;
		}
		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			al.push_back(IntPair(a, b));
			partnerOf[a].push_back(b);
			partnerOf[b].push_back(a);
		}

		IntList marks;
		for (int i = 0; i < N; i++) {
			if (isGroup[i]) continue;
			else marks.push_back(mark(i));
		}
		int max = 0;
		for (IntList::iterator mi = marks.begin();
		mi != marks.end(); mi++) {
			if (max < *mi) max = *mi;
		}		
		cout << max << "\n";
	}
}