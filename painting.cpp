#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

static int t = 0;
static int c, k, a, b;
static map<int, int> m;
static map<int, int>::iterator mi, temp;

int getLevel(int i) {
	temp = m.upper_bound(i);
	temp--;
	return temp->second;
}

void mark(int i, int l) {
	//cout << "mark at " << i << " as " << l << endl;
	if (l > 6) return;
	if (m.find(i) != m.end())
		m.find(i)->second = l;
	else
		m.insert(pair<int, int>(i, l));
}

void select(int l) {
	int h, t;
	for (mi = m.begin(); mi != m.end(); mi++) {
		if (mi->second == l) {
			h = mi->first;
			temp = ++mi;
			t = temp->first - 1;
			cout << h << " " << t << endl;
		}
	}
}

void print() {
	cout << "====MAP====" << endl;
	for (mi = m.begin(); mi != m.end(); mi++)
		cout << setw(9) << mi->first << " " << mi->second << endl;
	cout << "===========" << endl;
}

void debug(int a, int b) {
	cout << "===DEBUG===" << endl;
	for (int i = a; i < b; i++)
		cout << setw(2) << i;
	cout << endl;
	for (int i = a; i < b; i++)
		cout << setw(2) << getLevel(i);
	cout << endl;
	cout << "===========" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		m.clear();
		cin >> c >> k;
		m.insert(m.begin(), pair<int, int>(0, 0));

		for (int i = 0; i < c; i++) {
			cin >> a >> b;
			mark(b + 1, getLevel(b + 1));
			mark(a, getLevel(a) + 1);
			for (mi = m.upper_bound(a); mi != m.lower_bound(b+1); mi++) {
				mark(mi->first, mi->second + 1);
			}
			for (mi = m.begin(); mi != m.end();) {
				temp = mi++;
				if (mi == m.end()) break;
				else if (temp->second == mi->second) {
					m.erase(mi--);
				}
			}
		//	debug(0, 16);
		//	print();
		}
		select(k);
	}
	return 0;
}