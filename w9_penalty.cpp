/*
Problem:	w9_penalty - w9_penalty
Submitted:	23:56
Language:	C++
Time used:	1.41 second
Memory used:	131072 bytes
*/

#include <iostream>
using namespace std;

int T, K, C, A, B;

void print(int);
bool able(int, int, int);

int main(){
	ios::sync_with_stdio(false);
	print(4);
	cin >> T;
	while(T--){
		cin >> K >> C;
		for(int i = 0; i < C; i++){
			int diff = 0;
			bool home = false;
			cin >> A >> B;
			cout << able(A, B, K) << endl;
		}
	}
}

void print(int size) {
	for (int i = 0; i < size+1; i++) {
		for (int j = 0; j < size+1; j++) {
			cout << able(i, j, size) << " ";
		}
		cout << endl;
	}
}

bool lose(int my, int op, int left) {
	if (my+left<op) return true;
	else return false;
}

bool able(int A, int H, int N) {
	int ta, tb, tw, tl;
	bool ret = false;
	ta = tb = 0;
	for (int i = 0; i < N+1; i++) {
		if (i < A) ta++;
		if (lose(ta, tb, N - i-1)) break;
		if (i < H) tb++;
		if (lose(tb, ta, N - i-1)) break;
	}
	if (ta == A&&tb == H) ret = true;
	return ret;
}
