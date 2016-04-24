#include <iostream>
#include <string.h>
#include <bitset>
using namespace std;

struct Dice {
	bool is_instance;
	short path_bit;
	char top;
	int x, y;
};

struct Dir {
	int x, y;
};

void print_dm(int);
bool out_of_map(int, int);
bool is_dice(int, int);
void communicate(int, int);
void unique(int, int);
short dfs(int, int, int);
void get_set(short);

int T, W, H;
Dice dm[10][10], *target;
Dir dir[4] = { {0,1},{1,0},{0,-1},{-1,0} };

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> W >> H;
		// Initialize
		for (int i = 0; i < W*H; i++) {
			char temp;
			int x = i%W, y = i / W;
			Dice &d = dm[y][x];
			d.path_bit = 0xFF;
			d.y = y;
			d.x = x;
			cin >> temp;
			if (temp == '?') 	target = &d;
			else if (temp > '3') 	temp = '7' - temp + 0x30;
			d.top = temp;
			if (temp == '?' || temp == '*')
				d.is_instance = false;
			else
				d.is_instance = true;
		}
		// Communicate
		// Broadcast self information to neighbor
		// for (int i = 0; i < W*H; i++)
		// 	communicate(i%W, i / W);
		// for (int i = 0; i < W*H; i++)
		// 	unique(i%W, i/W);
		// print_dm(3);
		short p;
		p = dfs(target->x, target->y, 9);
		cout << "p: " << bitset<8>(p) << endl;
		get_set(p);
	}
}

void get_set(short bits) {
	bool able[3] = { 0 };
	int ac = 0;
	if (bits != 0x00) {
		for (int i = 0; i < 9; i++) {
			int bi[2] = { i % 3, (i / 3) % 3 }, b[2] = { 0 };
			if (bi[0] == bi[1]) continue;
			b[0] = (bits&(0x01 << (bi[0] + 4))) >> (bi[0] + 4);
			b[1] = (bits&(0x01 << bi[1])) >> bi[1];
			if (b[0] * b[1]) {
				int top, body = bi[0] + bi[1];
				if (body == 1) top = 2;
				if (body == 2) top = 1;
				if (body == 3) top = 0;
				able[top] = true;
				ac++;
			}
		}
	}
	if (ac == 0) cout << 0;
	for (int i = 0; i < 3; i++) {
		if (able[i]) cout << i + 1 << " ";
	}
	for (int i = 2; i > -1; i--) {
		if (able[i]) cout << 6 - i << " ";
	}
	cout << "\n";
}

void print_dm(int option) {
	cout << "==========PRINT DICE MAP=============" << endl;
	if (option & 0x01) {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << dm[i][j].top << " ";
			}
			cout << "\n";
		}
	}
	if (option & 0x02) {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << bitset<8>(dm[i][j].path_bit) << " ";
			}
			cout << "\n";
		}
	}
}

short dfs(int x, int y, int from) {
	Dice d = dm[y][x];
	short ret = 0x01, get[4] = { 0xFF };
	ret = ret << (d.top - 0x31);
	ret = (ret << 4) | ret;
	ret ^= 0xFF;
	bool is_any_dice = false;
	if (from > 1) 	from -= 2;
	else 			from += 2;
	for (int i = 0; i < 4; i++) {
		if (i == from) continue;
		int tx = x + dir[i].x, ty = y + dir[i].y;
		/*cout << 1 << " x: " << x << " y: " << y << endl;
		cout << 1 << " tx: " << tx << " ty: " << ty << endl;*/
		if (is_dice(tx, ty)) {
			is_any_dice = true;
			get[i] = dfs(tx, ty, i);
		}
	}
	// Terminal
	cout << "x: " << x << " y: " << y << " from: " << from << " ret: " << bitset<8>(ret) << endl;
	if (!is_any_dice) return ret;
	short h_pass = get[1] & get[3] & 0xF0;
	short v_pass = get[0] & get[2] & 0x0F;
	// No Pass (FAIL TO ALL DFS)
	if (h_pass == 0x80 || v_pass == 0x08) {
		cout << "x: " << x << " y: " << y << " from: " << from << " ret: " << bitset<8>(ret) << endl;
		return 0x00;
	}
	// ELSE
	if (h_pass == 0x90 || h_pass == 0xA0 || h_pass == 0xC0)
		v_pass &= (h_pass >> 4) ^ 0x0F;
	if (v_pass == 0x90 || v_pass == 0xA0 || v_pass == 0xC0)
		h_pass &= (v_pass << 4) ^ 0xF0;
	ret = ret&((h_pass << 4) | v_pass);
	cout << "x: " << x << " y: " << y << " from: " << from << " ret: " << bitset<8>(ret) << endl;
	return ret;
}

bool out_of_map(int x, int y) {
	bool ret = false;
	if (x < 0 || y < 0) 	ret = true;
	if (x >= W || y >= H) 	ret = true;
	return ret;
}

bool is_dice(int x, int y) {
	if (out_of_map(x, y) || dm[y][x].is_instance == false)
		return false;
	else	return true;
}

void communicate(int x, int y) {
	Dice d = dm[y][x];
	if (!d.is_instance) return;
	short mask = 0x01;
	mask = mask << (d.top - 0x31);
	mask ^= 0xFF;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < H; i++) {
			int ty = y + i;
			if (j == 1) ty = y - i;
			if (is_dice(x, ty)) break;
			dm[ty][x].path_bit &= mask;
		}
	}
	mask = (mask << 4) | 0x0F;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < W; i++) {
			int tx = x + i;
			if (j == 1) tx = x - i;
			if (is_dice(tx, y)) break;
			dm[tx][x].path_bit &= mask;
		}
	}
}

void unique(int x, int y) {
	Dice d = dm[y][x];
	short temp = d.path_bit;
	temp = temp & 0x0F;
}