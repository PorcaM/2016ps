/*
Problem:	cardgame - w6_cardgame
Submitted:	19:22
Language:	C++
Time used:	1.16 second
Memory used:	262144 bytes
*/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int T, N;
int pos[10000], neg[10000], posN, negN;

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		posN = negN = 0;
		memset(pos, 0, sizeof(pos));
		memset(neg, 0, sizeof(neg));
		cin >> N;
		for (int i = 0; i < N; i++) {
			int temp;
			cin >> temp;
			if (temp > 0)	pos[posN++] = temp;
			else			neg[negN++] = -temp;
		}
		sort(pos, pos + posN); sort(neg, neg + negN);
		register unsigned int sum_min;
		if		(posN == 0)		sum_min = neg[0] + neg[1];
		else if (negN == 0)		sum_min = pos[0] + pos[1];
		else {
			sum_min = abs(pos[0] - neg[0]);
			for (int i = 0; i < posN; i++) {
				int temp = abs(pos[i] - *lower_bound(neg, neg + negN, pos[i]));
				if (sum_min > temp) sum_min = temp;
			}
			for (int i = 0; i < negN; i++) {
				int temp = abs(-neg[i] + *lower_bound(pos, pos + posN, neg[i]));
				if (sum_min > temp) sum_min = temp;
			}
		}
		cout << sum_min << endl;
	}
}