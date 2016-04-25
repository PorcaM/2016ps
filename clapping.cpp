#include <iostream>
using namespace std;

bool isMultiple(int i, int a) {
	if (i%a == 0) return true;
	else return false;
}

int isInclude(int i, int a) {
	int ret = 1;
	int temp = i;
	for (int tail = i % 10; i != 0; ret *= 10, i /= 10, tail = i % 10) {
		if (tail == a) return ret*(i+1)-temp;
	}
	return 0;
}

int main() {
	::ios::sync_with_stdio(false);
	cout << isInclude(70, 7);
	int t, s, e, n;
	int abc[3] = { 0 };
	cin >> t;
	while (t--) {
		n = 0;
		for (int i = 0; i < 3; i++) cin >> abc[i];
		cin >> s >> e;
		if (abc[0] == 1) {
			cout << e - s + 1 << endl;
			continue;
		}
		for (int i = s; i < e + 1; i++) {
			int clap = 0;
			
			for (int j = 0; j < 3; j++) {
				if (isInclude(i, abc[j]) != 0) {
					clap = isInclude(i, abc[j]);
					i += clap - 1;
					break;
				}
			}
			if (clap == 0) {
				for (int j = 0; j < 3; j++) {
					if (isMultiple(i, abc[j]))
						clap = 1;
				}
			}
			n += clap;
		}
		cout << n << endl;
	}
	return 0;
}