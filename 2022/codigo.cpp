#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<i64> vl;
typedef vector<ii> vii;
 
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define REP(i, b) for (int i = 0; i < int(b); ++i)
#define RREP(i, b) for (int i = (b); i >= 0; --i)
#define FOR(i, a, b) for (int i = int(a); i <= int(b); ++i)
#define RFOR(i, a, b) for (int i = int(a); i >= int(b); --i)
 
#define MOD 1000000007
 
const char nl = '\n';

class DSU {
private:
	vector<int> parent, rank;
	int total;
public:
	DSU(int n): total(n) {
		rank.assign(n , 0);
		parent.resize(n);
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	int find(int i) {
		while (i != parent[i]) i = parent[i];
		return i;
	}
	bool isSame(int i, int j) { return find(i) == find(j); }
	void unionSet(int i, int j) {
		if (isSame(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
		total--;
	}
	int size() { return total; }
};

struct Point {
	double x, y, c;
	Point(double x, double y): x(x), y(y) {}
	Point(): x(0), y(0) {}
};

struct Circle {
	Point p;
	double r;
	Circle(Point p, double r): r(r), p(p) {}
	Circle(): p(Point()), r(0) {}
};

struct MinMax {
	double minX, minY, maxX, maxY;
	MinMax(): minX(10005), minY(10005), maxX(-1), maxY(-1) {}
	void update(Circle c) {
		minX = min(minX, c.p.x - c.r);
		minY = min(minY, c.p.y - c.r);
		maxY = max(maxY, c.p.y + c.r);
		maxX = max(maxX, c.p.x + c.r);
	}
};

bool intersec(Circle& a, Circle& b) {
	return hypot(a.p.x-b.p.x, a.p.y-b.p.y) <= a.r + b.r;
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<Circle> circles(n);
	for (int i = 0; i < k; i++) {
		double x, y, r;
		cin >> x >> y >> r;
		circles[i] = Circle(Point(x, y), r);
	}
	
	
	DSU dsu(n);
	
	for (int i = 0; i < k- 1; i++) {
		for (int j = i + 1; j < k; j++) {
			if (intersec(circles[i], circles[j])) {
				dsu.unionSet(i, j);
			}
		}
	}
	
	int dsusize = dsu.size();
	vector<MinMax> mnmx(dsusize);
	
	for (int i = 0; i < k; i++) {
		int f = dsu.find(i);
		mnmx[f].update(circles[i]);
	}
	
	for (int i = 0; i < dsusize; i++) {
		if ((mnmx[i].minX <= 0 && (mnmx[i].maxX >= n || mnmx[i].minY <= 0)) || (mnmx[i].maxY >= m && (mnmx[i].minY <= 0 || mnmx[i].maxX >= n))) {
			cout << "N" << nl;
			return 0;
		}
	}
	
	cout << "S" << nl;
	
	return 0;
}
