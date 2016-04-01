/*

Problem:	cleaner - w5_cleaner
Submitted:	22:39
Language:	C++
Time used:	1.49 second
Memory used:	131203072 bytes
Writed by PorcaM
*/


#include <iostream>
using namespace std;

int T, N, M;
int **map, **c;
int dirX[4] = { 0,1,0,-1 }, dirY[4] = { 1,0,-1,0 };
int c0, s;

bool isWall(int x, int y) {
	if (x < 0 || y < 0 || x >= N || y >= M) return true;
	else return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		bool success = true;
		c0 = 0;
		s = 0;
		map = new int*[M];
		c = new int*[M];
		for (int i = 0; i < M; i++) {
			map[i] = new int[N];
			c[i] = new int[N];
		}
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				c[i][j] = 0;
				if (map[i][j] == 0)c0++;
			}
		}
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 1) continue;
				int x, y, b = 0;
				for (int k = 0; k < 4; k++) {
					x = j + dirX[k];
					y = i + dirY[k];
					if (!isWall(x, y) && map[y][x] == 0)
						b++;
				}
				c[i][j] = b;
				s += b;
				if (b % 2 == 1) success = false;
			}
		}
		/*cout << "====C====" << endl;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cout << c[i][j] << " ";
			}
			cout << endl;
		}
		cout << "c0: " << c0 << ", s: " << s << endl;*/
		if (c0 > 4 && c0 * 2 >= s) success = false;
		if(success)
			cout << 1 << endl;
		else 
			cout << 0 << endl;
	}
}