#include <iostream>
#include <string.h>
#include <bitset>
using namespace std;

void set_route(int, int, int);
void print_r();
void unique();
bool get_bit(int, int);
bool check_block(int,int);

int T, W, H;
char map[10][10];
unsigned char route[10][10];
int x, y;
int dir_x[4] = { 0,1,0,-1 }, dir_y[4] = { 1,0,-1,0 };

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		memset(map, 0, sizeof(map));
		memset(route, 0xFF, sizeof(route));
		cin >> W >> H;
		char temp;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> temp;
				if		(temp == '?')	{ x = j; y = i; }
				else if (temp > '3')	temp = '7' - temp + 0x30;
				map[i][j] = temp;
				if		(temp != '?' && temp != '*')
					set_route(j, i, temp - 0x30);
			}
		}
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (map[i][j] == '*')
					route[i][j] = 0xFF;
			}
		}
	//	print_r();
		unique();
		int ac = 0;
		bool available[3] = { 0 };
		bool unable = false;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (check_block(j, i)) unable = true;
			}
		}
	//	print_r();
		if (!unable) {
			int get[4] = { 0 };
			for (int i = 0; i < 4; i++) {
				int tx = x + dir_x[i], ty = y + dir_y[i];
				get[i] = 0x0F;
				if (tx <W && tx>-1 && ty<H && ty>-1) {
					if (i % 2 == 1) get[i] = route[ty][tx] >> 4;
					else get[i] = route[ty][tx] & 0x0F;
				}
			}
			/*cout << "GET======================" << endl;
			for (int i = 0; i < 4; i++)
				cout << bitset<8>(get[i]) << " ";*/
				//cout << endl;
			for (int i = 0; i < 9; i++) {
				int j[2] = { i % 3, (i / 3) % 3 };
				if (j[0] == j[1]) continue;
				int b[4], r;
				for (int k = 0; k < 4; k++)
					b[k] = get_bit(get[k], j[k % 2]);
				r = b[0] * b[1] * b[2] * b[3];
				if (r) {
					//cout << j[0]+1 << " " << j[1]+1 << " " << endl;
					int top, body = j[0] + j[1];
					if (body == 1) top = 2;
					if (body == 2) top = 1;
					if (body == 3) top = 0;
					available[top] = true;
					ac++;
				}
			}
		}
		//check unable
	//	cout << unable << endl;
		if (ac == 0) cout << 0;
		for (int i = 0; i < 3; i++) {
			if (available[i]) cout << i + 1 << " ";
		}
		for (int i = 2; i >= 0; i--) {
			if (available[i])cout << 7 - i - 1 << " ";
		}
		cout << endl;
	}
}

bool check_block(int x, int y) {
	short r = route[y][x];
	bool flag = false;
//	cout << "check block: " << bitset<8>(r & 0xF0);
	if ((r & 0xF0) == 0x80) {
		if ((x + 1 < W && map[y][x + 1] != '*') ||
			(x - 1 > 0 && map[y][x - 1] != '*'))
			flag = true;
	}
	if ((r & 0x0F) == 0x08) {
		if ((y + 1 < H && map[y + 1][x] != '*') ||
			(y - 1 > 0 && map[y - 1][x] != '*'))
			flag = true;
	}
//	cout << " result: " << flag << endl;
	return flag;
}

bool get_bit(int v, int s) {
	return (v >> s) & 0x01;
}

void print_r() {
	cout << "====================pr" << endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << bitset<8>(route[i][j]) << ' ';
		}
		cout << endl;
	}
	cout << "pr=====================" << endl;
}

void set_route(int x, int y, int v) {
	short mask = 0b1;
	mask = mask << (v - 1);
	mask ^= 0xFF;
	for (int i = 0; i < H; i++) {
		int ty = y + i;
		if (ty >= H || map[ty][x] == '*') break;
		route[ty][x] &= mask;
	}
	for (int i = 0; i < H; i++) {
		int ty = y -i;
		if (ty <0 || map[ty][x] == '*') break;
		route[ty][x] &= mask;
	}
	mask = (mask << 4) | 0x0F;
	for (int i = 0; i < W; i++) {
		int tx = x + i;
		if (tx >= W || map[y][tx] == '*') break;
		route[y][tx] &= mask;
	}
	for (int i = 0; i < W; i++) {
		int tx = x- i;
		if (tx <0 || map[y][tx] == '*') break;
		route[y][tx] &= mask;
	}
}

void unique() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			short r = route[i][j];
			short temp = r & 0x0F;
			short mask;
			if (temp == 0x09 || temp == 0x0A || temp == 0x0C) {
				mask = (temp << 4) ^ 0x7F;
				for (int k = 0; k < H; k++) {
					if (i + k >= H || map[i + k][j] == '*') break;
					route[i + k][j] &= (temp << 4) ^ 0x7F;
				}
				for (int k = 0; k < H; k++) {
					if (i - k < 0 || map[i - k][j] == '*') break;
					route[i - k][j] &= (temp << 4) ^ 0x7F;
				}
			}
			temp = r >> 4;
			if (temp == 0x09 || temp == 0x0A || temp == 0x0C) {
				mask = temp ^ 0xF7;
				for (int k = -1; k < 2; k++) {
					if (j + k >= W || map[i][j + k] == '*') continue;
					route[i][j + k] &= temp ^ 0xF7;
				}
				for (int k = -1; k < 2; k++) {
					if (j - k < 0 || map[i][j - k] == '*') continue;
					route[i][j - k] &= temp ^ 0xF7;
				}
			}
		}
	}
}