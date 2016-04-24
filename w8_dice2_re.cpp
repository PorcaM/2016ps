#include <iostream>
#include <string.h>
#include <bitset>
using namespace std;

struct Dice{
	bool is_instance;
	short path_bit;
	char top;
	int x, y;
};

struct Dir{
	int x, y;
};

void print_dm(int);
bool out_of_range(int, int);
void communicate(int, int);

int T, W, H;
Dice dm[10][10], *target;
Dir dir[4] = {{0,1},{1,0},{0,-1},{-1,0}};

int main(){
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--){
		cin >> W >> H;
		// Initialize
		for(int i = 0; i < W*H; i++){
			char temp;
			int x = i%W, y = i/W;
			Dice &d = dm[y][x];
			d.path_bit = 0xFF;
			d.y = y;
			d.x = x;
			cin >> temp;
			if 		(temp == '?') 	target = &d;
			else if (temp > '3') 	temp = '7' - temp + 0x30;
			d.top = temp;
			if 		(temp == '?' || temp == '*') 
				d.is_instance = false;
			else 
				d.is_instance = true;
		}
		// Communicate
		// Broadcast self information to neighbor
		for(int i = 0; i < W*H; i++)
			communicate(i%W, i/W);
		print_dm(3);
	}
}

void print_dm(int option){
	cout << "==========PRINT DICE MAP=============" << endl;
	if(option&0x01){
		for(int i = 0; i < H; i++){
			for(int j = 0; j < W; j++){
				cout << dm[i][j].top << " ";
			}
			cout << "\n";
		}
	}
	if(option&0x02){
		for(int i = 0; i < H; i++){
			for(int j = 0; j < W; j++){
				cout << bitset<8>(dm[i][j].path_bit) << " ";
			}
			cout << "\n";
		}
	}
}

bool out_of_map(int x, int y){
	bool ret = false;
	if (x<0 || y<0) 	ret = true;
	if (x>=W || y>=H) 	ret = true;
	return ret;
}

void communicate(int x, int y){
	Dice d = dm[y][x];
	if (!d.is_instance) return;
	short mask = 0x01;
	mask = mask << (d.top - 0x31);
	mask ^= 0xFF;
	for(int j = 0; j < 2; j++){
		for (int i = 0; i < H; i++) {
			int ty = y+i;
			if (j == 1) ty = y-i;
			if (out_of_map(x,ty) || dm[ty][x].is_instance == false) break;
			dm[ty][x].path_bit &= mask;
		}
	}
	mask = (mask << 4) | 0x0F;
	for(int j = 0; j < 2; j++){
		for (int i = 0; i < H; i++) {
			int ty = y+i;
			if (j == 1) ty = y-i;
			if (out_of_map(x,ty) || dm[ty][x].is_instance == false) break;
			dm[ty][x].path_bit &= mask;
		}
	}
}