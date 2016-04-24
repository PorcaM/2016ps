/*
Problem:	w8_dice1 - w8_dice1
Submitted:	12:37
Language:	C++
Time used:	0 second
Memory used:	131072 bytes
*/

#include <iostream>
#include <string.h>
using namespace std;

struct Dice {
	int x, y, top;
	int left, down, num;
};

int T, W, H, N, M;
Dice dl[10];
Dice *dp[5][5];

void set_dDown(int, int, int);
void set_dLeft(int, int, int);
char get_type(Dice);

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		memset(dp, 0, sizeof(dp));
		memset(dl, 0, sizeof(dl));
		cin >> W >> H;
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> dl[i].x >> dl[i].y >> dl[i].top;
			dl[i].left = dl[i].down = 0;
			dl[i].num = i;
			dp[--dl[i].y][--dl[i].x] = &dl[i];
		}
		cin >> M;
		for (int i = 0; i < M; i++) {
			int it, v;
			char dir;
			int x, y;
			cin >> it >> dir >> v;
			x = dl[it - 1].x;
			y = dl[it - 1].y;
			if		(dir == 'U') set_dDown(x, y, 7 - v);
			else if (dir == 'D') set_dDown(x, y, v);
			else if (dir == 'L') set_dLeft(x, y, v);
			else				 set_dLeft(x, y, 7 - v);
		}
		for (int i = 0; i < N; i++)
			cout << get_type(dl[i]) << " ";
		cout << "\n";
	}
}

char get_type(Dice d) {
	int v[3], flag = 0;
	v[0] = d.top;
	v[1] = d.left;
	v[2] = d.down;
	for (int i = 0; i < 3; i++) {
		if (v[i] > 3) {
			v[i] = 7 - v[i];
			flag++;
		}
	}
	if (v[0] < v[1] && v[1] < v[2]);
	else if (v[1] < v[2] && v[2] < v[0]);
	else if (v[2] < v[0] && v[0] < v[1]);
	else flag++;
	if (flag % 2 == 0) return 'A';
	else return 'B';
}

void set_dDown(int x, int y, int v) {
	dp[y][x]->down = v;
	if (y <= 0) return;
	if (dp[y - 1][x] != NULL&&dp[y - 1][x]->down == 0) {
		set_dDown(x, y - 1, 7 - v);
	}
}

void set_dLeft(int x, int y, int v) {
	dp[y][x]->left = v;
	if (x >= 4) return;
	if (dp[y][x + 1] != NULL&&dp[y][x+1]->left == 0) {
		set_dLeft(x + 1, y, 7 - v);
	}
}