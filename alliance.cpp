#include <iostream>
#include <list>
using namespace std;

int T, N, M;
typedef pair<int, int> IntPair;
typedef list<IntPair> PairList;
typedef list<int> IntList;
PairList al;

int getSize() {
	int ret = 2;
	IntList member;
	member.push_back(al.begin()->first);
	member.push_back(al.begin()->second);
	for (IntList::iterator mi = member.begin();
	mi != member.end(); mi++) {
		int me = *mi;
		for (PairList::iterator li = al.begin();
		li != al.end();) {
			if (li->first == me || li->second == me) {
				li = al.erase(li);
				ret++;
			}
			else li++;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;

		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			al.push_back(IntPair(a, b));
		}

		int max = 0;
		while (al.size() != 0) {
			int size = getSize();
			if (max < size)
				max = size;
		}
		cout << max << "\n";
	}
}