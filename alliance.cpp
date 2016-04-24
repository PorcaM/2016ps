/*
Problem:	alliance - w5_alliance
Submitted:	18:49
Language:	C++
Time used:	1.08 second
Memory used:	232914944 bytes
Writed by PorcaM
*/
#include <iostream>
#include <list>
using namespace std;

int T, N, M;
bool *isGroup;
typedef list<int> IntList;
IntList *partnerOf;
int i, a, b, gmax;

inline static int mark(int num) {
	if (isGroup[num]) return 0;
	else isGroup[num] = true;
	int ret = 1;
	for (IntList::const_iterator pi = partnerOf[num].begin();
	pi != partnerOf[num].end(); pi++) {
		ret += mark(*pi);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		partnerOf	= new IntList[N];
		isGroup		= new bool[N];
		for (i = 0; i < N; i++)
			isGroup[i] = false;
		for (i = 0; i < M; i++) {
			cin >> a >> b;
			a--; b--;
			partnerOf[a].push_back(b);
			partnerOf[b].push_back(a);
		}
		gmax = 0;
		for (i = 0; i < N; i++) {
			if (isGroup[i]) continue;
			else {
				int temp = mark(i);
				if (gmax < temp) gmax = temp;
			}
		}
		cout << gmax << "\n";
	}
}