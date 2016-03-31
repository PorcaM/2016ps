#include <iostream>
#include <string.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int T, n, count[100], i, s, min, max, min2, max2, s1, s2;
	float temp;
	cout.precision(4);
	cout.setf(ios::showpoint);
	cin >> T;
	while (T--) {
		memset(count, 0, sizeof(count));
		cin >> n;		
		for (i = 0; i < n; i++) {
			cin >> temp;
			count[(int)(temp*10)]++;
		}
		s = 0;
		for (i = 0; i < 100; i++) 
			s += count[i] * i;
		i = 0;
		while (count[i] == 0) i++;
		if (count[i] == 1) {
			min = i++;
			while (count[i] == 0) i++;
			min2 = i;
		}
		else min = min2 = i;
		i = 99;
		while (count[i] == 0) i--;
		if (count[i] == 1) {
			max = i--;
			while (count[i] == 0) i--;
			max2 = i;
		}
		else max = max2 = i;
		s1 = s - max - min;
		s2 = s - max - min + max2 + min2;
		cout << (float)s1 / 10 / (n - 2) << " "
			<< (float)s2 / 10 / n << "\n";
	}
	return 0;
}