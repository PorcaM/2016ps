#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int T, M, N;
int info[100001];

inline bool isAlone(int a) {
	return info[a] == 0;
}

inline bool isAlliance(int a, int b) {
	if (info[a] == 0) return false;
	else return info[a] == info[b];
}

void newAlliance(int a, int b, int gid) {
	info[a] = gid;
	info[b] = gid;
}

void mergeAlliance(int a, int b) {
	int gid		= info[a];
	int target	= info[b];
	for (int i = 0; i < N; i++) {
		if (info[i] == target)
			info[i] = gid;
	}
}

void newMember(int newb, int oldb) {
	int gid = info[oldb];
	info[newb] = gid;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		memset(info, 0, sizeof(info));
		cin >> N >> M;
		int gid = 0;
		for (int i = 0; i < M; i++) {
			int x, y;
			cin >> x >> y;
			if (isAlone(x) && isAlone(y)) {
				newAlliance(x, y, ++gid);
			}
			else if (isAlone(x) && !isAlone(y)) {
				newMember(x, y);
			}
			else if (isAlone(y) && !isAlone(x)) {
				newMember(y, x);
			}
			else {
				mergeAlliance(x, y);
			}
		}
		int *m = new int[gid + 1];
		memset(m, 0, 4 * (gid + 1));
		for (int i = 0; i < N; i++) {
			m[info[i]]++;
		}
		sort(m, m + gid + 1);
		cout << m[gid] << "\n";
	}
}