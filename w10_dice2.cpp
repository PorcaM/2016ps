#include <iostream>
#include <bitset>
#include <string.h>
using namespace std;

// Direction coordination iterator
struct Dir {
	int x, y;
};
Dir dir[4] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };

// Global valuables
int T, W, H;
/*
Path array means available side by bits. 
1Byte = 8bits
3bits for horizontal path, 3bits for vertical path
MSB is must 1, then left 3 bits means is able 3, 2, 1
e.g. 11111111 means side able (3,2,1), (3,2,1)
e.g. 10011010 means side able (1), (2)
*/
char top[12][12], path[12][12]; 
int x, y;

// For debugging. 
void print_arr(char a[12][12], bool b) {
	cout << "===========PRINT ARR===========" << endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (b) 	cout << bitset<8>(a[i + 1][j + 1]) << " ";
			else 	cout << a[i + 1][j + 1] << " ";
		}
		cout << "\n";
	}
}

// Remove top member from side able list
short init(int x, int y) {
	char temp = top[y][x];
	if (temp == '*' || temp == '?') return 0xFF; 	// Do not remove */? dice
	int shift = top[y][x] - '1';					// N is top-1
	short ret = 0x01 << shift;						// Set Nth bit
	ret = (ret << 4) | ret;							// Same
	ret ^= 0xFF;									// Toggle, then only Nth bits is not setted
	return ret;
}

// This function change neighbor's path
void broadcast(int x, int y) {
	char temp = top[y][x];
	if (temp == '*' || temp == '?') return; 				// */? dice can not broadcast
	short mask[2] = { (path[y][x] & 0x0F) | 0xF0, 			// mask[0] is vertical mask. 
	(path[y][x] & 0xF0) | 0x0F };							// mask[1] is for horizontal
	for (int i = 0; i < 4; i++) {
		int tx = x + dir[i].x, ty = y + dir[i].y;
		char neighbor = top[ty][tx];
		if (neighbor == '*' || neighbor == '?') continue; 	// */? dice can not be changed
		else path[ty][tx] &= mask[i % 2]; 					// Block path of caster
	}
}

// Check myself, then validate
// If two sides able only one and same thing, then it means fail
int validate(int x, int y) {
	char temp = top[y][x];
	short bits = path[y][x];
	if ((bits & 0xF0) == 0x80 || (bits & 0x0F) == 0x08) return -1;
	if (temp == '*' || temp == '?') return 0;
	int offset[2] = { 0,4 };
	short tp[2] = { (path[y][x] >> 4) & 0x07, path[y][x] & 0x07 };
	for (int i = 0; i < 2; i++) {
		if (tp[i] == 0x01 || tp[i] == 0x02 || tp[i] == 0x04)
			path[y][x] &= (tp[i] << offset[i]) ^ 0xFF;
	}
	if (bits == path[y][x]) return 0;
	else return 1;
}

// get able top from path
void get_top(int x, int y) {
	short bits = path[y][x];
	bool able[3] = { 0 };
	if ((bits & 0xF0) == 0x80 || (bits & 0x0F) == 0x08)
		cout << 0;
	else {
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
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (able[i]) cout << i + 1 << " ";
	}
	for (int i = 2; i > -1; i--) {
		if (able[i]) cout << 6 - i << " ";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		// Init
		memset(top, '*', sizeof(top));
		memset(path, 0xFF, sizeof(top));
		// Input
		cin >> W >> H;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				char temp;
				cin >> temp;
				if ('3' < temp && temp < '7')
					temp = '7' - temp + '0';
				top[i + 1][j + 1] = temp;
				if (temp == '?') {
					y = i + 1; x = j + 1;
				}
			}
		}
		// path init
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				path[i + 1][j + 1] = init(j + 1, i + 1);
			}
		}
		// intercommunication
		bool next, fail = false;
		int sum_b, sum_a;
		do {
			next = false;
			sum_a = sum_b = 0;
			for (int i = 0; i < H; i++) {
				for (int j = 0; j < W; j++) {
					sum_b += path[i + 1][j + 1];
				}
			}
			for (int i = 0; i < H; i++) {
				for (int j = 0; j < W; j++) {
					broadcast(j + 1, i + 1);
					int ret = validate(j + 1, i + 1);
					if (ret < 0)
						fail = true;
					else if (ret > 0) {
						next = true;
						broadcast(j + 1, i + 1);
					}
				}
				if (fail) break;
			}
			if (fail) break;
			for (int i = 0; i < H; i++) {
				for (int j = 0; j < W; j++) {
					sum_a += path[i + 1][j + 1];
				}
			}
			// check is there any change
			if (sum_a != sum_b) next = true;
		} while (next);
		if (fail) {
			cout << 0 << endl; continue;
		}
		//print_arr(path, true);
		// setting ? dice
		short setter[2] = { 0xF0, 0x0F };
		for (int i = 0; i < 4; i++) {
			int tx = x + dir[i].x, ty = y + dir[i].y;
			path[y][x] &= (path[ty][tx] | setter[i % 2]);
		}
		top[y][x] = '0';	// for break condition at validate function
		validate(x, y);
		get_top(x, y);
	}
}