#include <iostream>
#include <list>
using namespace std;

class Group {
public:
	Group *parent;
	bool isTop;
	int size;
	Group(int a, int b) {
		size = a + b;
		parent = NULL;
		isTop = true;
	}
	void giveTop(Group *p) {
		isTop = false;
		parent = p;
	}
	Group *getTop() {
		if (isTop) return this;
		else return parent->getTop();
	}
};
int T, N, M;
typedef list<int> IntList;
typedef list<Group*> GroupList;
IntList *nakama[100000];
Group *g[100000];
GroupList tl;

bool noTop(Group *g) {
	return !(g->isTop);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			g[i] = new Group(1, 0);
		}
		for (int i = 0; i < M; i++) {
			int x, y, a, b;
			cin >> a >> b;
			a--; b--;
			Group *temp = new Group(g[a]->getTop()->size, g[b]->getTop()->size);
			g[a]->getTop()->giveTop(temp);
			g[b]->getTop()->giveTop(temp);
			tl.push_back(temp);
		}
		tl.remove_if(noTop);
		int max = 0;
		for (GroupList::iterator li = tl.begin();
		li != tl.end(); li++) {
			if (max < (*li)->size)
				max = (*li)->size;
		}
		cout << max << "\n";
	}
}