#include <stdio.h>
using namespace std;

int T, N, c, i, t; 
bool bl[50001];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &c);
		for (i = 0; i < N + 1; i++) {
			bl[i] = false;
		}
		for (i = 0; i < N - c; i++) {
			scanf("%d", &t);
			bl[t] = true;
		}
		for (i = 1; i < N+1; i++) {
			if (!bl[i]) printf("%d ", i);
		}
		printf("\n");
	}
	return 0;
}