/*

Problem:	Hacking - w10_Hacking
Submitted:	02:41
Language:	C++
Time used:	3.2 second
Memory used:	61440 bytes

*/
#include <stdio.h>
using namespace std;

#define MAX_NUM		50000
#define MAX_MISS	3

int		T, N, c;
char	bl[MAX_NUM / 8];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &c);
		int ii = N / 8, bi = N % 8;
		for (int i = 0; i < ii+1; i++) bl[i] = 0xFF;
		bl[0] &= 0xFE;
		for (int i = 0; i < N - c; i++) {
			int t, it, of;
			scanf("%d", &t);
			it = t / 8; of = t % 8;
			char ct = 0x01;
			ct = (ct << of) ^ 0xFF;
			bl[it] &= ct;
		}
		for (int i = 0; i < ii+1; i++) {
			for (int j = 0; j < 8; j++) {
				if ((bl[i] >> j) & 0x01) {
					printf("%d ", i * 8 + j);
				}
				if (i == ii && j == bi) break;
			}
		}
		printf("\n");
	}
	return 0;
}